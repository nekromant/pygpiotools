#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "gpio.h"

extern struct GPIOController pl2303_gpio;

struct GPIOController *gps[] = {
    &pl2303_gpio
};

static PyObject *pygpio_list(PyObject *self, PyObject *args)
{
     PyListObject *data = (PyListObject*) PyList_New(0);
     int i; 
     for (i=0; i<ARRAY_SIZE(gps); i++) {
        PyList_Append(data, PyUnicode_FromString(gps[i]->name));         
     }
     return data;
}

static PyObject *pygpio_open (PyObject *self, PyObject *args)
{
    return NULL;
}

static PyObject *pygpio_direction(PyObject *self, PyObject *args)
{
    return NULL;
}

static PyObject *pygpio_read(PyObject *self, PyObject *args)
{
    return NULL;
}

static PyObject *pygpio_write(PyObject *self, PyObject *args)
{
    return NULL;
}

static PyMethodDef PyGPIOMethods[] = {
    {"list",       pygpio_list,      METH_VARARGS, "Get a list of supported controllers"},
    {"open",       pygpio_open,      METH_VARARGS, "Open a controller (by it's comX:)"},
    {"direction",  pygpio_direction, METH_VARARGS, "Set direction (INPUT, OUTPUT)"},
    {"read",       pygpio_read,      METH_VARARGS, "Read pin"},
    {"write",      pygpio_write,     METH_VARARGS, "Write pin"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef pygpiomodule = {
    PyModuleDef_HEAD_INIT,
    "pygpiotools",   /* name of module */
    "WHATEVER", /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    PyGPIOMethods
};

PyMODINIT_FUNC
PyInit_pygpiotools(void)
{
    PyObject *m;

    m = PyModule_Create(&pygpiomodule);
    if (m == NULL)
        return NULL;

    return m;
}