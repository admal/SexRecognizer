#include "MyPythonWrapper.h"
#include "../SexRecognizer.Common/LoggerFactory.h"

using namespace OurPython;

void MyPythonWrapper::CheckPythonError(PyObject* pyObject)
{
	if (pyObject == NULL)
	{
		PyErr_Print();
		throw MyPythonException();
	}
}

PyObject* MyPythonWrapper::ExecuteFunction(string functionName, PyObject* args)
{
	// Create some Python objects that will later be assigned values.
	PyObject *pName, *pModule, *pDict, *pFunc;
	// Convert the file name to a Python string.
	pName = PyUnicode_FromString(filename.c_str());
	// Import the file as a Python module.
	pModule = PyImport_Import(pName);

	CheckPythonError(pModule);
	// Create a dictionary for the contents of the module.
	pDict = PyModule_GetDict(pModule);
	CheckPythonError(pDict);
	// Get the add method from the dictionary.
	pFunc = PyDict_GetItemString(pDict, functionName.c_str());
	
	CheckPythonError(pFunc);
	// Call the function with the arguments.
	PyObject* pResult = PyObject_CallObject(pFunc, args);
	
	CheckPythonError(pResult);

	result = pResult;
	return pResult;
}

int MyPythonWrapper::GetResultAsLong()
{
	if (result != nullptr)
	{
		return PyLong_AsLong(result);
	}
	throw MyPythonEmptyResultException();
}

MyPythonWrapper::MyPythonWrapper(string filename)
{
	this->filename = filename;
	// Initialize the Python interpreter.
	/*Py_Initialize();*/
}


MyPythonWrapper::~MyPythonWrapper()
{
	// Destroy the Python interpreter.
	Py_Finalize();
}
