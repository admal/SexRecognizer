#include "NeuralNetContext.h"
#include "../SexRecognizer.Common/LoggerFactory.h"
#include "opencv2/core/mat.hpp"
#include "Python.h"
#include "MyPythonWrapper.h"

using namespace std;
using namespace Context;
using namespace OurPython;

PyObject* GetOpticalFlowArray(vector<cv::Mat> frames)
{
	auto firstFrame = frames[0];

	PyObject *pyCrazyArray = PyTuple_New(frames.size());

	for (int i = 0; i < frames.size(); i++)
	{
		cv::Mat currMat = frames[i];
		PyObject *pyRows = PyTuple_New(currMat.rows);
		for (int j = 0; j < currMat.rows; j++)
		{
			PyObject *pyCols = PyTuple_New(currMat.cols);
			for (int k = 0; k < currMat.cols; k++)
			{
				PyObject *pyPixel = PyTuple_New(2);
				auto pixel = currMat.at<cv::Vec3b>(j, k);

				PyObject *x = PyLong_FromLong(pixel[1]);
				PyObject *y = PyLong_FromLong(pixel[2]);

				PyTuple_SetItem(pyPixel, 0, x);
				PyTuple_SetItem(pyPixel, 1, y);

				PyTuple_SetItem(pyCols, k, pyPixel);
			}
			PyTuple_SetItem(pyRows, j, pyCols);
		}
		PyTuple_SetItem(pyCrazyArray, i, pyRows);
	}

	return pyCrazyArray;
}

void NeuralNetContext::Execute(Common::IApplicationContext* context)
{
	const char filename[] = "evaluator"; //nazwa pliku bez .py
	const char methodName[] = "run";
	
	auto logger = Common::LoggerFactory::GetLogger();
	logger->Log("Neural network started");
	Py_Initialize();
	PyObject* list = GetOpticalFlowArray(context->optical_flow_frames()[0]);
	PyObject* path = PyUnicode_FromString("C:\\Users\\adam.malewski\\Downloads\\model\\my-model");;

	PyObject* params = PyTuple_New(2);
	PyTuple_SetItem(params, 0, list);
	PyTuple_SetItem(params, 1, path);

	MyPythonWrapper wrapper(filename);

	wrapper.ExecuteFunction(methodName, params);
	int result = wrapper.GetResultAsLong();

	if (result == 0)
	{
		logger->Log("Result: Male");
	}
	else
	{	
		logger->Log("Result: Female");
	}

	
	logger->Log("Neural network finished");
}

