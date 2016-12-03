#include "DetectorContext.h"
#include "../SexRecognizer.Common/LoggerFactory.h"
#include "../SexRecognizer.Common/DirectoryLoader.h"
#include "SilhouetteExtractor.h"
#include <vector>
#include "../SexRecognizer.Common/IApplicationContext.h"

using namespace std;
using namespace Common;

void DetectorContext::Execute(IApplicationContext* context)
{
	string directory = context->video_path();
	auto logger = LoggerFactory::GetLogger();
	logger->Log("Detecotr module started");

	DirectoryLoader* loader = new DirectoryLoader(directory);
	auto frames = loader->GetFrames();

	Extract::SilhouetteExtractor extractor(0);
	
	logger->Log("Extracting and resizing frames");

	std::vector<int> offsets = extractor.extract(frames);
	std::vector<cv::Mat> resizedFrames = extractor.getResizedFrames();	

	context->set_resized_frames(resizedFrames);
	context->set_offsets(offsets);

	logger->Log("Detector module finished");
}

DetectorContext::DetectorContext()
{
}


DetectorContext::~DetectorContext()
{
}
