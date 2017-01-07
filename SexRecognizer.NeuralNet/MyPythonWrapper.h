#pragma once
#include <string>
#include <vector>
#include "opencv2/core/mat.hpp"
#include "Python.h"

using namespace std;

/*
*	All namespaces, classes, methods, etc. that are Python oriented starts with
*	'Our' or 'My' prefixes because Python C++ API encourages not to create own
*	entities that starts with 'Py' because of future possible conflicts.
*/
namespace OurPython
{
	class MyPythonWrapper
	{
	private:
		/*
		* without .py extension
		*/
		string filename;
		PyObject* result = nullptr;

		void CheckPythonError(PyObject* pyObject);
	public:
		PyObject* ExecuteFunction(string functionName, PyObject* args);
		int GetResultAsLong();

		MyPythonWrapper(string filename);
		~MyPythonWrapper();
	};

	class MyPythonEmptyResultException : exception
	{
	public:
		const char* what() const override
		{
			return "The result was not computed yet";
		}
	};

	class MyPythonException : exception
	{
	public:
		const char* what() const override
		{
			return "Calling function from python error ended wit error";
		}
	};
}
