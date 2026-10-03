/*
 * MxTypedef.h
 *
 *  Created on: Sep 27, 2026
 *      Author: ASUS
 */

#ifndef INC_MXTYPEDEF_H_
#define INC_MXTYPEDEF_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "stm32f4xx_hal.h"


typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned long UINT32;
typedef unsigned char BOOL;
typedef signed int INT;


enum
{
    TRUE = 1,
    FALSE = 0
};


#endif /* INC_MXTYPEDEF_H_ */
