#include "MxTypedef.h"
#include "MxBlcommands.h"
#include "MxWindows_serial_port.h"

UINT8 data_packed[MAX_COMMAND_LENGTH];
extern UINT32 address;

static int read_the_len_and_status(void);

void reply_processing(UINT8 command)
{

    INT status = NACK;
    UINT16 device_id;
    UINT8 RDP_status;
    UINT8 status_command;


    if (command >= TOTAL_COMMAND_SUPPORTED)
    {
        printf("Invalid command for processing: %d \n",command);
        return;
    }

    /*Read the status and Length*/
    status = read_the_len_and_status();

    /*Check the status*/
    if (status > 0)
    {

        /*Read the data from the serial port*/
        if (read_data(data_packed, status) < 0)
        {
            printf("Read Failed ! \n");
            return;
        }
        else
        {
            printf("Data Read Succesfully \n");
        }
    }

    else
    {
        printf("NACK Recieved with error code : %d \n", -1 * status);
        return;
    }

    /*Process the command*/
    switch (command)
    {

    case BL_GET_VER:
        data_packed[status] = '\0'; // Null terminate the string
        printf("Version : %s \n", (char *)data_packed);
        break;

    case BL_GET_HELP:
        printf("Supported Commands : ");
        for (int i = 0; i < status; i++)
            printf("0x%x ", data_packed[i]);
        break;

    case BL_GET_CID:
        device_id = (data_packed[0]) | (data_packed[1] << 8);
        printf("Device ID : 0x%x \n", device_id);
        break;

    case BL_GET_RDP_STATUS:
        RDP_status = data_packed[0];
        printf("RDP Status is : 0x%x \n", RDP_status);

        if (RDP_status == 0xAA)
            printf("RDP Status is : No Protection \n");
        else if (RDP_status == 0xCC)
            printf("RDP Status is :  chip protection (debug and boot from RAM features disabled) \n");
        else
            printf(" read protection of memories (debug features limited) \n");
        break;
    
    case BL_GO_TO_ADDR:
        status_command = data_packed[0];

        if(status_command != 1) printf("Address is Invalid \n");
        else printf("Address is Valid \n");
        break;
    
    case BL_FLASH_ERASE:
        status_command = data_packed[0];

        if(status_command != 1) printf("Flash erase not happen \n");
        else printf("flash erase happen succesfully \n");
        break;

    case BL_MEM_WRITE:
        status_command = data_packed[0];
        
        if(status_command != 1) printf("Memory write not happen \n");
        else printf("Memory write happen succesfully \n");
        break;

    case BL_MEM_READ:
        status_command = data_packed[0];

        /*This status command is denote that it initially it 
        send the length so how much length is send*/
        if(status_command == 0) printf("Memory read not happen because address is incorrect\n");
        else{
            printf("Memory read happen succesfully and length is %d \n", status_command);
            /*First read the length and then read the value*/
            UINT8 len;
            read_data(&len,1);
            printf("Length to read is %d \n", len);
            UINT8 data_buffer[len];
            read_data(data_buffer,len);
            printf("=====================Memory table=================================");
            for(int i=0; i<=len; i++)
            {   
                if(i%16 == 0) printf("\n[0x%lx]",address+i);
                printf(" 0x%x",data_buffer[i]);                
            }
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

    printf("Status recived from bootloader : %d \n",status_read[0]);

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