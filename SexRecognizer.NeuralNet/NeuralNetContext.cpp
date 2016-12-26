#include "NeuralNetContext.h"
#include "../SexRecognizer.Common/LoggerFactory.h"
#include "opencv2/core/mat.hpp"
#include "Python.h"


void NeuralNetContext::Execute(Common::IApplicationContext* context)
{
	const char filename[] = "Sample"; //nazwa pliku bez .py
	const char methodName[] = "add";

	auto logger = Common::LoggerFactory::GetLogger();
	logger->Log("Neural network started");

	//in this case we just need the first set of frames (there is no more 
	//frames, moire frames are generated only in learning mode)
	auto frames = context->optical_flow_frames()[0];
	auto firstFrame = frames[0];
	double**** crazyArray = new double***[frames.size()];

	// Initialize the Python interpreter.
	Py_Initialize();

	PyObject *pyCrazyArray = PyTuple_New(frames.size());

	for (int i = 0; i < frames.size(); i++)
	{
		cv::Mat currMat = frames[i];
		PyObject *pyRows = PyTuple_New(currMat.rows);
		//crazyArray[i] = new double**[currMat.rows];
		for (int j = 0; j < currMat.rows; j++)
		{
			PyObject *pyCols = PyTuple_New(currMat.cols);
			//crazyArray[i][j] = new double*[currMat.cols];
			for (int k = 0; k < currMat.cols; k++)
			{
				//crazyArray[i][j][k] = new double[2];

				PyObject *pyPixel = PyTuple_New(2);
				auto pixel = currMat.at<cv::Vec3b>(j, k);

				PyObject *x = PyLong_FromLong(pixel[1]);
				PyObject *y = PyLong_FromLong(pixel[2]);

				PyTuple_SetItem(pyPixel, 0, x);
				PyTuple_SetItem(pyPixel, 1, y);

				PyTuple_SetItem(pyCols, k, pyPixel);
				/*crazyArray[i][j][k][0] = pixel[1];
				crazyArray[i][j][k][1] = pixel[2];*/
			}
			PyTuple_SetItem(pyRows, j, pyCols);
		}
		PyTuple_SetItem(pyCrazyArray, i, pyRows);
	}


	// Create some Python objects that will later be assigned values.
	PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;
	// Convert the file name to a Python string.
	pName = PyUnicode_FromString(filename);
	// Import the file as a Python module.
	pModule = PyImport_Import(pName);
	
	if (pModule == nullptr)
	{
		PyErr_Print();
		std::exit(1);
	}
	// Create a dictionary for the contents of the module.
	pDict = PyModule_GetDict(pModule);
	// Get the add method from the dictionary.
	pFunc = PyDict_GetItemString(pDict, methodName);
	// Create a Python tuple to hold the arguments to the method.
	pArgs = PyTuple_New(1);

	//pValue = PyArray_FromArray(crazyArray);
	// Set the Python int as the first and second arguments to the method.
	PyTuple_SetItem(pArgs, 0, pyCrazyArray);
	// Call the function with the arguments.
	PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
	// Print a message if calling the method failed.
	if (pResult == NULL){
		logger->Error("Calling the add method failed.\n");
		PyErr_Print();
	}
	// Convert the result to a long from a Python object.
	long result = PyLong_AsLong( pResult);
	// Destroy the Python interpreter.
	Py_Finalize();
	// Print the result
	logger->Log(2, "The result is ", std::to_string(result));


	//w³órz tu rzeczy Piotrze
	logger->Log("Neural network finished");
}
