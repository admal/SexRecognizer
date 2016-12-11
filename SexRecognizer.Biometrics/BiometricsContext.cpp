#include "BiometricsContext.h"
#include "OpticalFlowSolver.h"
#include "../SexRecognizer.Common/FileManager.h"

#include <string>
using namespace Context;

#define RECT_WIDTH 40
#define RECT_HEIGHT 60

void BiometricsContext::Execute(IApplicationContext* context)
{
	auto logger = LoggerFactory::GetLogger();
	logger->Log("Biometrics module started");

	auto offsets = context->offsets();
	auto resizedFrames = context->resized_frames();

	std::vector<std::vector<cv::Mat>> framesOpticalFlow;

	//to trzeba chyba przenieœæ
	IO::FileManager*  fileManager = new IO::FileManager();

	for (int i = 0; i < resizedFrames.size(); i++)
	{
		auto frames = Helpers::MatrixHelpers::GetGrayscaleImages(context->resized_frames()[i]);
		string output = context->output_path();
		auto alg = context->optical_flow_alg();

		OpticalFlowSolver solver(offsets[i], frames, alg);

		logger->Log("Solver started");
		framesOpticalFlow.push_back(solver.DoCompute(RECT_WIDTH, RECT_HEIGHT));

		if (i == 0)
		{

			fileManager->SaveOuptut(output, framesOpticalFlow[i]); //for first video put it by default in output directory
		}
		else
		{
			//for rest frames generate directories as: output_i
			string directory(output);
			if (output.back() == '\\')
			{
				string tmp(output.begin(), output.end() - 1); //create string without '\\'
				directory = tmp;
			}
			directory.append("_");
			directory.append(to_string(i));
			IO::FileManager::MakeDirectory(directory);

			fileManager->SaveOuptut(directory, framesOpticalFlow[i]);
		}
	}


	context->set_optical_flow_frames(framesOpticalFlow); //save result



	logger->Log("Output saved");


	delete fileManager;
}
