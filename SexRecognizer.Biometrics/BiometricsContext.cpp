#include "BiometricsContext.h"
#include "OpticalFlowSolver.h"
#include "../SexRecognizer.Common/FileManager.h"
using namespace Context;

#define RECT_WIDTH 40
#define RECT_HEIGHT 60

void BiometricsContext::Execute(IApplicationContext* context)
{
	auto logger = LoggerFactory::GetLogger();
	logger->Log("Biometrics module started");

	auto offsets = context->offsets();
	auto frames = Helpers::MatrixHelpers::GetGrayscaleImages(context->resized_frames()[1]);
	string output = context->output_path();
	auto alg = context->optical_flow_alg();

	OpticalFlowSolver solver(offsets[1], frames, alg);
	logger->Log("Solver started");
	auto framesOpticalFlow = solver.DoCompute(RECT_WIDTH, RECT_HEIGHT);

	context->set_optical_flow_frames(framesOpticalFlow); //save result

	//to trzeba chyba przenieœæ
	IO::FileManager*  fileManager = new IO::FileManager();

	fileManager->SaveOuptut(output, framesOpticalFlow);
	logger->Log("Output saved");


	delete fileManager;
}
