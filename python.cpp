#include <iostream>
#include <C:\\Python310\\include\\Python.h>
// #include <Python.h>

using namespace std;

int main(){
    PyObject *pName, *pModule, *pFunc, *pValue;
    Py_Initialize();
    pName = PyUnicode_FromString("camera.py");
    pModule = PyImport_Import(pName);
    pFunc = PyObject_GetAttrString(pModule, "main");
    pValue = PyObject_CallObject(pFunc, NULL);
    Py_Finalize();

    return 0;
}


