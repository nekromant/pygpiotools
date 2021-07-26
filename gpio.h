#ifndef GPIO_H
#define GPIO_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))

struct GPIOController
{
    const char *name;
    PyObject *(*open)(PyObject *self, PyObject *args);
    PyObject *(*direction)(PyObject *self, PyObject *args);
    PyObject *(*read)(PyObject *self, PyObject *args);
    PyObject *(*write)(PyObject *self, PyObject *args);
    PyObject *(*close)(PyObject *self, PyObject *args);
};


#endif // !GPIO_H