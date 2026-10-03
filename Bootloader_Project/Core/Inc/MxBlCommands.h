/*
 * MxBlCommands.h
 *
 *  Created on: Sep 28, 2026
 *      Author: ASUS
 */

#ifndef INC_MXBLCOMMANDS_H_
#define INC_MXBLCOMMANDS_H_

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


typedef enum{

    CHECKSUM_FAILED,
    COMMAND_CODE_INCORECT,
    DATA_IMPROPER
}reason_for_nack;

#endif /* INC_MXBLCOMMANDS_H_ */
