#pragma once
#include <string>
#include <vector>
#include "opencv2/core/mat.hpp"
#include "Python.h"

using namespace std;

class PythonWrapper
{
private:
	/*
	* without .py extension
	*/
	string filename;

	PyObject* GetOpticalFlowArray(vector<cv::Mat> frames);

	PyObject* result = nullptr;

	void CheckPythonError(PyObject* pyObject);
public:
	PyObject* ExecuteFunction(string functionName, PyObject* args);
	int GetResultAsLong();

	PythonWrapper(string filename);
	~PythonWrapper();
};

class PythonEmptyResultException : exception
{
public:
	const char* what() const override
	{
		return "The result was not computed yet";
	}
};

class PythonException : exception
{
public:
	const char* what() const override
	{
		return "Calling function from python error ended wit error";
	}
};

