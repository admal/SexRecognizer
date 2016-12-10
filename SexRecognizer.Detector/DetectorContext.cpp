#include "DetectorContext.h"
#include "../SexRecognizer.Common/LoggerFactory.h"
#include "../SexRecognizer.Common/DirectoryLoader.h"
#include "SilhouetteExtractor.h"
#include <vector>
#include "../SexRecognizer.Common/IApplicationContext.h"
#include "../SexRecognizer.Common/MatrixHelpers.h"

using namespace std;
using namespace Common;
using namespace Common::Helpers;
using namespace cv;
using namespace cv::cuda;

void DetectorContext::Execute(IApplicationContext* context)
{
	string directory = context->video_path();
	auto logger = LoggerFactory::GetLogger();
	bool mirrorFlag = context->isMirrorFlag();
	
	if (mirrorFlag)	logger->Log("Detector module started for mirrored images");
	else logger->Log("Detector module started");

	DirectoryLoader* loader = new DirectoryLoader(directory);
	Extract::SilhouetteExtractor extractor(0);

	auto frames = loader->GetFrames();
	logger->Log("Extracting and resizing frames");
	std::vector<int> offsets;
	if (mirrorFlag){
		auto mirroredFrames = Common::Helpers::ImageHelper::mirrorImages(frames);
		offsets = extractor.extract(mirroredFrames);
	} else
	{
		offsets = extractor.extract(frames);
	}
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
