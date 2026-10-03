/*
 * MxLogger.c
 *
 *  Created on: Sep 27, 2026
 *      Author: ASUS
 */

#include <MxTypedef.h>

#define MAX_LENGTH_TO_PRINT 200



static char* file_name_parse(char *file){
	char *ptr = strchr(file,'/');

	while(ptr != NULL){
		file = ++ptr;
		ptr = strchr(file,'/');
	}

	return file;
}


void PRINT(UART_HandleTypeDef uart_type, char *file, const char *function, int line, const char *format, ...)
{

	char data_send[MAX_LENGTH_TO_PRINT];
	char complete_data[2*MAX_LENGTH_TO_PRINT];
	va_list ap;

	va_start(ap, format);

	vsprintf(data_send, format, ap);

	sprintf(complete_data, "%s:%s:%d:%s\r\n", file_name_parse(file), function, line, data_send);
	HAL_UART_Transmit(&uart_type, (UINT8*)complete_data, (UINT16)strlen(complete_data), HAL_MAX_DELAY);
}


