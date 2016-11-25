#ifndef __CUDACC__  
#define __CUDACC__
#endif

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "../SexRecognizer.Common/DirectoryLoader.h"
#include "../SexRecognizer.Common/MatrixHelpers.h"
#include "SilhouetteExtractor.h"
#include "ImageResizer.h"
#include "BackgroundSubtractor.h"
///////////////////////////////////////////////////////////////

//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include "opencv2/core.hpp"
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>
#include <math.h>

#define MOG2_SUBTRACTION 0

using namespace cv;
using namespace std;
using namespace cv::cuda;
using namespace Extract;


void help();
void help()
{
	cout
		<< "--------------------------------------------------------------------------" << endl
		<< "This program will resize the and extract human from given images" << endl
		<< "using OpenCV. You can process only image sequences. The path should point to first img." << endl
		<< endl
		<< "Usage:" << endl
		<< "./bg_sub <image filename>" << endl
		<< "for example: ./bg_sub /data/images/1.png" << endl
		<< "--------------------------------------------------------------------------" << endl
		<< endl;
}
int main(int argc, char* argv[])
{
	//print help information
	help();
	//check for the input parameter correctness
	if (argc != 2) {
		cerr << "Incorret input list" << endl;
		cerr << "exiting..." << endl;
		return EXIT_FAILURE;
	}
	
	Common::DirectoryLoader dirLoader(argv[1]); // load directory
	std::vector<cv::Mat> frames = dirLoader.GetFrames();

	//EXTRACTING and getting resized images
	Extract::SilhouetteExtractor extractor(MOG2_SUBTRACTION);	
	std::vector<int> xs = extractor.extract(frames); //extract data
	std::vector<cv::Mat> resizedImages = extractor.getResizedFrames();

	return 0;
}