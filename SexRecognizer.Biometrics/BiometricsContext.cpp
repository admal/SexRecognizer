#include "BiometricsContext.h"
#include "OpticalFlowSolver.h"
#include "../SexRecognizer.Common/FileManager.h"
using namespace Context;

void BiometricsContext::Execute(IApplicationContext* context)
{
	auto logger = LoggerFactory::GetLogger();
	logger->Log("Biometrics module started");

	auto offsets = context->offsets();
	auto frames = Helpers::MatrixHelpers::GetGrayscaleImages(context->resized_frames());
	string output = context->output_path();
	auto alg = context->optical_flow_alg();

	OpticalFlowSolver solver(offsets, frames, alg);
	logger->Log("Solver started");
	auto framesOpticalFlow = solver.DoCompute(60);

	context->set_optical_flow_frames(framesOpticalFlow); //save result

	//to trzeba chyba przenieœæ
	IO::FileManager*  fileManager = new IO::FileManager();

	fileManager->SaveOuptut(output, framesOpticalFlow);
	logger->Log("Output saved");


	delete fileManager;
}
