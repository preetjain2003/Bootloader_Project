#ifndef MX_TYPEDEF_H
#define MX_TYPEDEF_H

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

typedef enum
{
    NACK,
    ACK
}status_t;

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

#define CUART huart2
#define DUART &huart3 /*Here we cannot use the log message just above so thats why 
every place use &DUART instead we write here*/

#endif // MX_TYPEDEF_H
