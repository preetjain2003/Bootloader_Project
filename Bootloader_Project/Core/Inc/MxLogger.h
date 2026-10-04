/*
 * MxLogger.h
 *
 *  Created on: Sep 26, 2026
 *      Author: ASUS
 */

#ifndef INC_MXLOGGER_H_
#define INC_MXLOGGER_H_

#include "MxTypedef.h"


#define LOG_MESSAGE(type, format, ...) \
	PRINT(type, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)

/* log message with command code */
#define LOG_MESSAGE_WITH_CC(type, format, ...) \
	PRINT_WITH_CC(command_name[current_command_processing],type,__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)

void PRINT(UART_HandleTypeDef uart_type, char *file, const char *function, int line, const char *format, ...);
void PRINT_WITH_CC(char *command_name, UART_HandleTypeDef uart_type, char *file, const char *function, int line, const char *format, ...);
#endif /* INC_MXLOGGER_H_ */
