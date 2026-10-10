#include <windows.h>
#include <stdio.h>

HANDLE hComm;

int serial_port_configuration(const char *pcCommPort)
{
    DCB dcb;
    BOOL fSuccess;

    //  Open a handle to the specified com port.
    hComm = CreateFile(pcCommPort,
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);

    if (hComm == INVALID_HANDLE_VALUE)
    {
        //  Handle the error.
        printf("CreateFile failed with error %lu.\n", GetLastError());
        return 1;
    }

    // Initialize the DCB Structure
    memset(&dcb, 0, sizeof(dcb));
    dcb.DCBlength = sizeof(dcb);

    //  Build on the current configuration by first retrieving all current
    //  settings.
    fSuccess = GetCommState(hComm, &dcb);
    if (!fSuccess)
    {
        //  Handle the error.
        printf("GetCommState failed with error %lu.\n", GetLastError());
        return (2);
    }

    //  Fill in some DCB values and set the com state:
    //  11,5200 bps, 8 data bits, no parity, and 1 stop bit.
    dcb.BaudRate = CBR_115200; //  baud rate
    dcb.ByteSize = 8;          //  data size, xmit and rcv
    dcb.Parity = NOPARITY;     //  parity bit
    dcb.StopBits = ONESTOPBIT; //  stop bit

    fSuccess = SetCommState(hComm, &dcb);

    if (!fSuccess)
    {
        //  Handle the error.
        printf("Set DCB failed with error %lu.\n", GetLastError());
        return 1;
    }
    else
    {
        printf("\n ===============Setting the DCB Structure=================== \n");
        printf("Serial communication baud rate : %lu \n", dcb.BaudRate);
        printf("Serial communication byte size : %d \n", dcb.ByteSize);
        printf("Serial communication parity bits : %d \n", dcb.Parity);
        printf("Serial communication stop bits : %d \n", dcb.StopBits);
    }

    // Set the timeout related configuration
    COMMTIMEOUTS timeout_conf;

    timeout_conf.ReadIntervalTimeout = 50;
    timeout_conf.ReadTotalTimeoutConstant = 1000;
    timeout_conf.ReadTotalTimeoutMultiplier = 0;
    timeout_conf.WriteTotalTimeoutConstant = 1000;
    timeout_conf.WriteTotalTimeoutMultiplier = 0;

    if (SetCommTimeouts(hComm, &timeout_conf) == FALSE)
        printf("\n   Error! in Setting Time Outs");
    else
        printf("\n\n   Setting Serial Port Timeouts Successfull");

    if (SetCommMask(hComm, EV_RXCHAR) == FALSE) // Configure Windows to Monitor the serial device for Character Reception
        printf("\n\n   Error! in Setting CommMask");
    else
        printf("\n\n   Setting CommMask successfull");

    printf("Serial port %s successfully reconfigured \n", pcCommPort);

    return 0;
}

int read_data(UINT8 *data_read, UINT8 length)
{

    DWORD byte_read;

    BOOL ret = ReadFile(hComm,             // Handle to the serial port
                        (void *)data_read, // read data buffer
                        length,            // total no of bytes to read
                        &byte_read,        // total no of bytes it read
                        NULL);             // In synchronous we pass the null here

    // Check the status
    if (ret == FALSE)
    {
        printf("Read data failed with %lu \n", GetLastError());
        return 1;
    }
    else
    {
        printf("\n Read to the port succesfully happened \n");
        return 0;
    }
}

int write_data(UINT8 *data_write, UINT8 length)
{

    DWORD byte_written;

    BOOL ret = WriteFile(hComm,              // Handle to the serial port
                         (void *)data_write, // write data buffer
                         length,             // total no of bytes to write
                         &byte_written,      // total no of bytes it written
                         NULL);              // In synchronous we pass the null here

    // Check the status
    if (ret == FALSE)
    {
        printf("Write data failed with \n");    
        return 1;
    }
    else
    {

        printf("\n ==============Sending command======================== \n");
        for (UINT32 i = 0; i < byte_written; i++)
        {

            printf(" 0x%2.2x", data_write[i]);

            if (i % 8 == 0 && i != 0)
                printf("\n");
        }

        printf("\n");
        return 0;
    }
}

void close_serial_communication(void)
{

    // close the port connection
    CloseHandle(hComm);
    printf("Serial port handle closed.\n");
}
