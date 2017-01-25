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
	DirectoryLoader* loader = new DirectoryLoader(directory);
	auto logger = LoggerFactory::GetLogger();
	bool mirrorFlag = context->isMirrorFlag();
	Extract::SilhouetteExtractor *extractor = new Extract::SilhouetteExtractor();
	auto frames = loader->GetFrames();
	std::vector<std::vector<int>> offsets;
	std::vector<std::vector<cv::Mat>> resizedFrames;

	logger->Log("Detector module started");
	logger->Log("Extracting and resizing frames");
	
	offsets.push_back(extractor->extract(frames));
	resizedFrames.push_back(extractor->getResizedFrames()); // push vector of resized frames

	if (mirrorFlag){
		auto mirroredFrames = Common::Helpers::ImageHelper::mirrorImages(frames);
		offsets.push_back(extractor->extract(mirroredFrames));
		mirroredFrames = extractor->getResizedFrames();
		resizedFrames.push_back(mirroredFrames);
	} 

	context->set_offsets(offsets);
	context->set_resized_frames(resizedFrames);

	logger->Log("Detector module finished");
}

DetectorContext::DetectorContext()
{
}


DetectorContext::~DetectorContext()
{
}
