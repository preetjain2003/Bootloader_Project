#ifndef MX_BL_COMMANDS_H
#define MX_BL_COMMANDS_H

/*Command*/

enum{
    BL_GET_VER,
    BL_GET_HELP,
    BL_GET_CID,
    BL_GET_RDP_STATUS,
    BL_GO_TO_ADDR,
    BL_FLASH_ERASE,
    BL_MEM_WRITE,
    BL_EN_R_W_PROTECT,
    BL_MEM_READ,
    BL_READ_SECTOR_STATUS,
    BL_OTP_READ,
    BL_DIS_R_W_PROTECT
};

/*Command Code*/
#define BL_GET_VER_CC 0x51
#define BL_GET_HELP_CC 0x52
#define BL_GET_CID_CC 0x53
#define BL_GET_RDP_STATUS_CC 0x54
#define BL_GO_TO_ADDR_CC 0x55
#define BL_FLASH_ERASE_CC 0x56
#define BL_MEM_WRITE_CC 0x57
#define BL_EN_R_W_PROTECT_CC 0x58
#define BL_MEM_READ_CC 0x59
#define BL_READ_SECTOR_STATUS_CC 0x5A
#define BL_OTP_READ_CC 0x5B
#define BL_DIS_R_W_PROTECT_CC 0x5C

/*Total Command Length*/
#define BL_GET_VER_LEN 6
#define BL_GET_HELP_LEN 6
#define BL_GET_CID_LEN 6
#define BL_GET_RDP_STATUS_LEN 6
#define BL_GO_TO_ADDR_LEN 10
#define BL_FLASH_ERASE_LEN 8
#define BL_MEM_WRITE_LEN 11
#define BL_EN_R_W_PROTECT_LEN 8
#define BL_MEM_READ_LEN 11
#define BL_READ_SECTOR_STATUS_LEN 6
#define BL_OTP_READ_LEN 6
#define BL_DIS_R_W_PROTECT_LEN 6


/*Max command lenght*/
#define MAX_COMMAND_LENGTH  255


/*Total Command Supported*/
#define TOTAL_COMMAND_SUPPORTED 12

/*Base of command*/
#define BASE_OF_COMMAND 0x51

/*ACK and NACK*/
#define ACK 1
#define NACK 0

/*Total byte we write in memory write at once*/
#define TOTAL_MEM_WRITE (50 - BL_MEM_READ_LEN + 1)


void processing_the_command(UINT32 command);

#endif // MX_BL_COMMANDS_H
