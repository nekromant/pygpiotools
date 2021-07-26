#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <windows.h>
#include "gpio.h"

extern struct GPIOController pl2303_gpio;
static PyObject * __this_module = NULL;


struct GPIOController *gps[] = {
    &pl2303_gpio
};

struct GPIOController *getCtrlForHandle(HANDLE hndl)
{
    PyObject *mdict    = PyModule_GetDict(__this_module);
    PyObject *registry = PyDict_GetItem(mdict, PyUnicode_FromString("__registry"));
    PyObject *ctrl = PyDict_GetItem(registry, PyLong_FromVoidPtr(hndl));
    return (struct GPIOController *) PyLong_AsVoidPtr(ctrl);
}

void setCtrlForHandle(HANDLE hndl, struct GPIOController *ctl)
{
    PyObject *mdict    = PyModule_GetDict(__this_module);
    PyObject *registry = PyDict_GetItem(mdict, PyUnicode_FromString("__registry"));
    PyDict_SetItem(registry, PyLong_FromVoidPtr(hndl), PyLong_FromVoidPtr(ctl));
}

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
    const char *driver;
    const char *port;
    struct GPIOController *ctl = NULL;
    HANDLE *hnd; 

    int i;
    int sts;
    if (!PyArg_ParseTuple(args, "ss", &driver, &port))
        return NULL;

    for (i=0; i<ARRAY_SIZE(gps); i++) {
        if (strcmp(gps[i]->name, driver) == 0) {
            ctl = gps[i];
        }
    }

    if (!ctl) {
        return NULL;
    }
    HANDLE hndl = ctl->open(driver, port);
    if (hndl) {
        setCtrlForHandle(hndl, ctl);
    }
    return PyLong_FromVoidPtr((void *) hndl);
}

static PyObject *pygpio_direction(PyObject *self, PyObject *args)
{
    HANDLE hndl;
    int pin; 
    const char *direction;
    enum pin_direction dir; 

    PyObject *tmp;
    if (!PyArg_ParseTuple(args, "Ois", &tmp, &pin, &direction))
        return NULL;
    hndl = PyLong_AsVoidPtr(tmp);
    struct GPIOController *ctl = getCtrlForHandle(hndl);
    if (strcmp(direction, "OUTPUT") == 0) {
        dir = MODE_OUTPUT;
    } else {
        dir = MODE_INPUT;
    }
    ctl->direction(hndl, pin, dir);
    return Py_None;
}

static PyObject *pygpio_read(PyObject *self, PyObject *args)
{
    return NULL;
}

static PyObject *pygpio_write(PyObject *self, PyObject *args)
{
    HANDLE hndl;
    int pin, value; 

    PyObject *tmp;
    if (!PyArg_ParseTuple(args, "Oii", &tmp, &pin, &value))
        return NULL;

    hndl = PyLong_AsVoidPtr(tmp);
    struct GPIOController *ctl = getCtrlForHandle(hndl);
    ctl->write(hndl, pin, value);
    return Py_None;
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
    if (__this_module) {
        fprintf(stderr, "FATAL: This extension can be loaded only once\n");
    }
    __this_module = m;
    PyObject *mdict    = PyModule_GetDict(__this_module);
    PyObject *registry = PyDict_New();
    PyDict_SetItem(mdict, PyUnicode_FromString("__registry"), registry);
    return m;
}