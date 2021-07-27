#include "gpio.h"
#include <windows.h>
#include <winioctl.h>

#define USB2SER_IOCTL_INDEX	0x0800

// For GP0
#define GP0_OUTPUT_ENABLE	CTL_CODE(FILE_DEVICE_UNKNOWN,\
				         USB2SER_IOCTL_INDEX+20,\
				         METHOD_BUFFERED, \
				         FILE_ANY_ACCESS)					

#define GP1_OUTPUT_ENABLE	CTL_CODE(FILE_DEVICE_UNKNOWN,\
				         USB2SER_IOCTL_INDEX+21,\
				         METHOD_BUFFERED,\
				         FILE_ANY_ACCESS)

#define GP0_SET_VALUE		CTL_CODE(FILE_DEVICE_UNKNOWN,\
				         USB2SER_IOCTL_INDEX+22,\
				         METHOD_BUFFERED,\
				         FILE_ANY_ACCESS)

// For GP1
#define GP1_SET_VALUE		CTL_CODE(FILE_DEVICE_UNKNOWN,\
				         USB2SER_IOCTL_INDEX+23,\
				         METHOD_BUFFERED,\
				         FILE_ANY_ACCESS)

#define GP0_GET_VALUE		CTL_CODE(FILE_DEVICE_UNKNOWN,\
				         USB2SER_IOCTL_INDEX+24,\
				         METHOD_BUFFERED,\
				         FILE_ANY_ACCESS)

#define GP1_GET_VALUE		CTL_CODE(FILE_DEVICE_UNKNOWN,\
				         USB2SER_IOCTL_INDEX+25,\
				         METHOD_BUFFERED,\
				         FILE_ANY_ACCESS)

// For GP23
#define GP23_SET_CONFIG          CTL_CODE(FILE_DEVICE_UNKNOWN, \
                                          USB2SER_IOCTL_INDEX+35, \
                                          METHOD_BUFFERED,  \
                                          FILE_ANY_ACCESS)

#define GP23_GET_CONFIG          CTL_CODE(FILE_DEVICE_UNKNOWN, \
                                          USB2SER_IOCTL_INDEX + 36, \
                                          METHOD_BUFFERED, \
                                          FILE_ANY_ACCESS)
                                          
#define GP23_SET_DATA            CTL_CODE(FILE_DEVICE_UNKNOWN, \
                                          USB2SER_IOCTL_INDEX + 37, \
                                          METHOD_BUFFERED, \
                                          FILE_ANY_ACCESS)
#define GP23_GET_DATA            CTL_CODE(FILE_DEVICE_UNKNOWN, \
                                          USB2SER_IOCTL_INDEX + 38, \
                                          METHOD_BUFFERED, \
                                          FILE_ANY_ACCESS)
#define SEND_ENCAP				CTL_CODE(FILE_DEVICE_UNKNOWN,		\
										USB2SER_IOCTL_INDEX+3,	\
										METHOD_BUFFERED,				\
										FILE_ANY_ACCESS)

BOOL PL2303_GP0_Enable(HANDLE hDrv, BOOL enable)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP0_OUTPUT_ENABLE,
			&enable, sizeof(BYTE), NULL, 0, &nBytes, NULL);
	
	return bSuccess;
}

BOOL PL2303_GP0_GetValue(HANDLE hDrv, BYTE *val)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP0_GET_VALUE,
			NULL, 0, val, sizeof(BYTE), &nBytes, NULL);

	return bSuccess;
}

BOOL PL2303_GP0_SetValue(HANDLE hDrv, BYTE val)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP0_SET_VALUE,
			&val, sizeof(BYTE), NULL, 0, &nBytes, NULL);

	return bSuccess;
}

// For GP1
BOOL PL2303_GP1_Enable(HANDLE hDrv, BOOL enable)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP1_OUTPUT_ENABLE,
			&enable, sizeof(BYTE), NULL, 0, &nBytes, NULL);
	
	return bSuccess;
}

BOOL PL2303_GP1_GetValue(HANDLE hDrv, BYTE *val)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP1_GET_VALUE,
			NULL, 0, val, sizeof(BYTE), &nBytes, NULL);

	return bSuccess;
}

BOOL PL2303_GP1_SetValue(HANDLE hDrv, BYTE val)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP1_SET_VALUE,
			&val, sizeof(BYTE), NULL, 0, &nBytes, NULL);

	return bSuccess;
}

#define BLEN 256
/* handle = open("pl2303", "com1:") */
HANDLE pl2303_open(const char *driver, const char *port)
{
        HANDLE hndl = NULL;
        void *shit = (void *) 0x123;
        char tmp[BLEN];
        sprintf(tmp, "\\\\.\\%s", port);
        char *ps = strchr(tmp, ":");
        if (ps) { // Dumb way to get rid of ":"
                *ps = 0x0; 
        }
	hndl = CreateFile(tmp, 0,
		FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 
                NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
        return hndl;
};

/* direction(handle, pin, "INPUT/OUTPUT") */
int pl2303_direction(HANDLE hndl, int pin, enum pin_direction dir)
{
        if (pin == 0) {
                PL2303_GP0_Enable(hndl, dir == MODE_OUTPUT);
        } else if (pin == 1) {
                PL2303_GP1_Enable(hndl, dir == MODE_OUTPUT);
        } else {
                return 1;
        }
        return 0;
};

/* write(handle, pin) */
int pl2303_write(HANDLE hndl, int pin, int value)
{
        if (pin == 0) {
                PL2303_GP0_SetValue(hndl, value);
        } else if (pin == 1) {
                PL2303_GP1_SetValue(hndl, value);
        } else {
                return 1;
        }
        return 0;
};

/* read(handle, pin) */
int pl2303_read(HANDLE hndl, int pin)
{
        BYTE tmp; 
        BOOL result = 0;
        int ret = -1;
        if (pin == 0) {
                result = PL2303_GP0_GetValue(hndl, &tmp);
        } else if (pin == 1) {
                result = PL2303_GP1_GetValue(hndl, &tmp);
        }
        return result ? tmp : -1;
};


/* write(handle, pin) */
void pl2303_close(HANDLE hndl)
{
    CloseHandle(hndl);
};

struct GPIOController pl2303_gpio = {
        .name      = "pl2303",
        .open      = pl2303_open,
        .direction = pl2303_direction,
        .read      = pl2303_read,
        .write     = pl2303_write,
        .close     = pl2303_close,
};
