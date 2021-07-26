#ifndef GPIO_H
#define GPIO_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <windows.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))

enum pin_direction {
    MODE_OUTPUT,
    MODE_INPUT,
};

struct GPIOController
{
    const char *name;
    HANDLE (*open)(const char *driver, const char *port);
    int (*direction)(HANDLE hndl, int pin, enum pin_direction);
    int (*read)(HANDLE hndl, int pin);
    int (*write)(HANDLE hndl, int pin, int value);
    void (*close)(HANDLE hndl);
};


#endif // !GPIO_H