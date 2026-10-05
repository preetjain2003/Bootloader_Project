/*
 * MxBlReplyProcessing.h
 *
 *  Created on: Sep 27, 2026
 *      Author: ASUS
 */

#ifndef INC_MXBLREPLYPROCESSING_H_
#define INC_MXBLREPLYPROCESSING_H_

#include "MxTypedef.h"

#define ADDRESS_VALID 1
#define ADDRESS_INVALID 0

#define SRAM1_BASE 0x20000000
#define SRAM1_END 0x2001BFFF
#define SRAM2_BASE 0x2001C000
#define SRAM2_END 0x2001FFFF
#define FLASH_BASE 0x08000000
#define FLASH_END 0x081FFFFF


UINT8* Blcommandread(void);
void BLReplyProcessing(UINT8 *payload_data, UINT8 length);
void send_the_data(uint8_t status);
void send_the_array(uint8_t *data, UINT16 len);

#endif /* INC_MXBLREPLYPROCESSING_H_ */
