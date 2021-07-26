#include "gpio.h"

/* handle = open("pl2303", "com1:") */
static PyObject *pl2303_open(PyObject *self, PyObject *args)
{
    
};

/* direction(handle, pin, "INPUT/OUTPUT") */
static PyObject *pl2303_direction(PyObject *self, PyObject *args)
{
    
};

/* read(handle, pin) */
static PyObject *pl2303_read(PyObject *self, PyObject *args)
{
    
};

/* write(handle, pin) */
static PyObject *pl2303_write(PyObject *self, PyObject *args)
{
    
};

/* write(handle, pin) */
static PyObject *pl2303_close(PyObject *self, PyObject *args)
{
    
};

struct GPIOController pl2303_gpio = {
        .name      = "pl2303",
        .open      = pl2303_open,
        .direction = pl2303_direction,
        .read      = pl2303_read,
        .write     = pl2303_write,
        .close     = pl2303_close,
};
