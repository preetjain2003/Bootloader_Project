/*
 * MxBlCommands.h
 *
 *  Created on: Sep 28, 2026
 *      Author: ASUS
 */

#ifndef INC_MXBLCOMMANDS_H_
#define INC_MXBLCOMMANDS_H_


#define TOTAL_COMMAND_SUPPORTED 12

/*X-Macros implementation*/

#define COMMAND \
    X(BL_GET_VER, 0x51) \
    X(BL_GET_HELP, 0x52) \
    X(BL_GET_CID, 0x53) \
    X(BL_GET_RDP_STATUS, 0x54) \
    X(BL_GO_TO_ADDR, 0x55) \
    X(BL_FLASH_ERASE, 0x56) \
    X(BL_MEM_WRITE, 0x57) \
    X(BL_EN_R_W_PROTECT, 0x58) \
    X(BL_MEM_READ, 0x59) \
    X(BL_READ_SECTOR_STATUS, 0x5A) \
    X(BL_OTP_READ, 0x5B) \
    X(BL_DIS_R_W_PROTECT, 0x5C)


#define X(name, hex) name##_CC = hex,
enum command_code_macro { COMMAND };
#undef X

typedef enum{

    CHECKSUM_FAILED,
    COMMAND_CODE_INCORECT,
    DATA_IMPROPER
}reason_for_nack;

#endif /* INC_MXBLCOMMANDS_H_ */
