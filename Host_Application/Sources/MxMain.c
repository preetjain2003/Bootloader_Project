#include<MxTypedef.h>
#include<MxWindows_serial_port.h>
#include<MxBlcommands.h>


#define COMM_PORT "\\\\.\\COM20"
int main()
{
    UINT32 command;

    serial_port_configuration(COMM_PORT);

    while(1){
        printf("\n\n +====================Bootloader Commands========================\n");
        printf("\n BL_GET_VER -> 1 \n");
        printf("\n BL_GET_HELP -> 2 \n");
        printf("\n BL_GET_CID -> 3 \n");
        printf("\n BL_GET_RDP_STATUS -> 4 \n");
        printf("\n BL_GO_TO_ADDR -> 5 \n");
        printf("\n BL_FLASH_ERASE -> 6 \n");
        printf("\n BL_MEM_WRITE -> 7 \n");
        printf("\n BL_EN_R_W_PROTECT -> 8 \n");
        printf("\n BL_MEM_READ -> 9 \n");
        printf("\n BL_READ_SECTOR_STATUS -> 10 \n");
        printf("\n BL_OTP_READ -> 11 \n");
        printf("\n BL_DIS_R_W_PROTECT -> 12 \n");
        printf("\n Exit -> 13 \n");

        printf("\n Enter the commands : ");
        scanf("%lu",&command);

        if(command == 13){
            printf("Exit from the host \n");
            exit(1);
        }

        printf("Processing the command : %lu \n",command);
        processing_the_command(command);

    }
}