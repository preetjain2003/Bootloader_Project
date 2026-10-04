#include "MxTypedef.h"
#include "MxBlcommands.h"
#include "MxWindows_serial_port.h"

UINT8 data_packed[MAX_COMMAND_LENGTH];

static int read_the_len_and_status(void);

void reply_processing(UINT8 command)
{

    INT status = NACK;
    switch (command)
    {

    default:
        printf("Invalid command for processing \n");
        break;

    case BL_GET_VER:

        /*Read the status and Length*/
        status = read_the_len_and_status();

        if (status > 0)
        {

            /*Read the data from the serial port*/
            if (read_data(data_packed, status) < 0)
            {
                printf("Read Failed ! \n");
            }

            else
            {
                printf("Data Read Succesfully \n");
                data_packed[status] = '\0'; // Null terminate the string
                printf("Version : %s \n", (char *)data_packed);
            }
        }

        else
        {
            printf("NACK Recieved with error code : %d \n", -1 * status);
        }

        break;

    case BL_GET_HELP:

        /*Read the status and Length*/
        status = read_the_len_and_status();

        if (status > 0)
        {

            /*Read the data from the serial port*/
            if (read_data(data_packed, status) < 0)
            {
                printf("Read Failed ! \n");
            }

            else
            {
                printf("Data Read Succesfully \n");

                printf("Supported Commands : ");
                for (int i = 0; i < status; i++)
                    printf("0x%x ", data_packed[i]);
            }
        }

        else
        {
            printf("NACK Recieved with error code : %d \n", -1 * status);
        }

        break;

    case BL_GET_CID:

        /*Read the status and Length*/
        status = read_the_len_and_status();

        if (status > 0)
        {

            /*Read the data from the serial port*/
            if (read_data(data_packed, status) < 0)
            {
                printf("Read Failed ! \n");
            }

                    else
                    {
                        printf("Data Read Succesfully \n");
                        UINT16 device_id = device_id = (data_packed[0]) | (data_packed[1] << 8);
                        printf("Device ID : 0x%x \n", device_id);
                    }
        }

            else
        {
            printf("NACK Recieved with error code : %d \n", -1 * status);
        }

        break;
    }
}

static INT read_the_len_and_status()
{
    /*Read the ACK/NACK and length*/
    UINT8 status_read[2];

    if (read_data(status_read, 2) < 0)
    {
        printf("Read Failed ! \n");
    }

    if (status_read[0] == NACK)
    {
        printf("NACK Recieved \n");
        return -1 * status_read[1];
    }

    else if (status_read[0] == ACK)
    {
        printf("ACK Recieved \n");

        // Return the length
        printf("Length to follow : %d \n", status_read[1]);
        return +1 * status_read[1];
    }

    return -1;
}