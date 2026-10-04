/*
 * MxBlReplyProcessing.c
 *
 *  Created on: Sep 27, 2026
 *      Author: ASUS
 */
#include "MxBlReplyProcessing.h"
#include "MxBlCommands.h"
#include "MxTypedef.h"
#include "MxLogger.h"
#include "main.h"

#define X(name, hex) hex,
int command_code[] = { COMMAND };
#undef X

#define X(name, hex) #name,
char* command_name[] = { COMMAND };
#undef X

UINT8 current_command_processing = 0;

static void get_the_device_id(UINT8 *pData);
static UINT8 get_the_rdp_status(void);

UINT8 *Blcommandread(void)
{

	UINT8 *data_read = (UINT8 *)malloc(sizeof(UINT8) * 1);

	/*Read the command code and length */
	HAL_UART_Receive(DUART, &data_read[0], sizeof(UINT8), HAL_MAX_DELAY);

	UINT8 *data_read_payload = (UINT8 *)realloc(data_read, sizeof(UINT8) * data_read[0]);

	if(data_read_payload == NULL){
		LOG_MESSAGE(CUART,"Realloc failed");
		return NULL;
	}

	for (UINT8 i = 1; i <= data_read_payload[0]; i++)
	{
		HAL_UART_Receive(DUART, &data_read_payload[i], sizeof(UINT8), HAL_MAX_DELAY);
	}

	return data_read_payload;
}

void BLReplyProcessing(UINT8 *payload_data, UINT8 length)
{
	/*Set the command to this variable */
	current_command_processing = payload_data[1];
	
	/* Value start from the 0x51 for 0 indexing */
	current_command_processing -= 0x51;

	switch (payload_data[1])
	{

	case BL_GET_VER_CC:
		char *send_the_version = (char *)malloc(sizeof(char) * 10);
		LOG_MESSAGE_WITH_CC(CUART,"Bootleader Version processing");
		sprintf(send_the_version, "v%d.%d.%d", BOOTLOADER_MAJOR_VERSION, BOOTLOADER_MINOR_VERSION, BOOTLOADER_PATCH_VERSION);
		LOG_MESSAGE_WITH_CC(CUART,"Bootleader Version : %s",send_the_version);
		send_the_data(ACK);
		send_the_data((UINT8)strlen(send_the_version));
		send_the_array((UINT8 *)send_the_version, strlen(send_the_version));
		LOG_MESSAGE_WITH_CC(CUART,"Succesfully send the version : %s",send_the_version);
		free(send_the_version);
		break;

	case BL_GET_HELP_CC:
		LOG_MESSAGE_WITH_CC(CUART,"Bootloader help processing");
		send_the_data(ACK);
		send_the_data((UINT8)TOTAL_COMMAND_SUPPORTED);
		for(int i=0;i<TOTAL_COMMAND_SUPPORTED;i++) send_the_data((UINT8)command_code[i]);
		LOG_MESSAGE_WITH_CC(CUART,"Succesfully send all the command code of bootloader");
		break;

	case BL_GET_CID_CC:
		LOG_MESSAGE_WITH_CC(CUART,"Bootloader CID processing started");
		send_the_data(ACK);
		send_the_data((UINT8)2);
		UINT8 *device_id = malloc(sizeof(UINT8)*2);
		get_the_device_id(device_id);
		send_the_array(device_id,2);
		free(device_id);
		LOG_MESSAGE_WITH_CC(CUART,"Succesfully send the device id code");
		break;
	
	case BL_GET_RDP_STATUS_CC:
		LOG_MESSAGE_WITH_CC(CUART,"Bootloader RDP processing started");
		send_the_data(ACK);
		send_the_data((UINT8)1);
		send_the_data(get_the_rdp_status());
		LOG_MESSAGE_WITH_CC(CUART,"Succesfully send the RDP status");
		break;
		
	default:
		LOG_MESSAGE(CUART, "Command code is incorrect so we send NACK");
		send_the_data(NACK);
		send_the_data(COMMAND_CODE_INCORECT);
		break;
	}

	return;
}

void send_the_data(uint8_t status)
{
	HAL_UART_Transmit(DUART, &status, sizeof(UINT8), HAL_MAX_DELAY);
}

void send_the_array(uint8_t *data, UINT16 len)
{
	HAL_UART_Transmit(DUART, data, len, HAL_MAX_DELAY);
}

static void get_the_device_id(UINT8 *pData){
	UINT32 *ptr = (UINT32*)0xE0042000;
	pData[0] = *ptr & 0xFF;
	pData[1] = (*ptr >> 8) & 0x0F;

	LOG_MESSAGE_WITH_CC(CUART,"Calculated CID is 0x%x%x",pData[1],pData[0]);
	return;
}

static UINT8 get_the_rdp_status(void){
	UINT32 *ptr = (UINT32 *)0x1FFFC000;

	UINT8 rdp_status = (*ptr & 0x0000FF00) >> 8;

	LOG_MESSAGE_WITH_CC(CUART,"Calculated RDP status is 0x%x",rdp_status);

	return rdp_status;
}
