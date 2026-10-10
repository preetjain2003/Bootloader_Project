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
int command_code[] = {COMMAND};
#undef X

#define X(name, hex) #name,
char *command_name[] = {COMMAND};
#undef X

UINT8 current_command_processing = 0;

static void get_the_device_id(UINT8 *pData);
static UINT8 get_the_rdp_status(void);
static UINT8 verify_address(UINT32 *go_to_address);
static UINT8 get_the_rdp_status(void);
static UINT8 flash_erase_sector(UINT8 sectorNo, UINT8 noofsector);
static UINT8 write_into_flash(UINT8 *address, UINT8 *value, UINT8 size);
static void dummy_function(void);

UINT8 *Blcommandread(void)
{

	UINT8 *data_read = (UINT8 *)malloc(sizeof(UINT8) * 1);

	/*Read the command code and length */
	HAL_UART_Receive(DUART, &data_read[0], sizeof(UINT8), HAL_MAX_DELAY);

	UINT8 *data_read_payload = (UINT8 *)realloc(data_read, sizeof(UINT8) * data_read[0]);

	if (data_read_payload == NULL)
	{
		LOG_MESSAGE(CUART, "Realloc failed");
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

	UINT32 ret = 0;

	switch (payload_data[1])
	{

	case BL_GET_VER_CC:
		char *send_the_version = (char *)malloc(sizeof(char) * 10);
		LOG_MESSAGE_WITH_CC(CUART, "Bootleader Version processing");
		sprintf(send_the_version, "v%d.%d.%d", BOOTLOADER_MAJOR_VERSION, BOOTLOADER_MINOR_VERSION, BOOTLOADER_PATCH_VERSION);
		LOG_MESSAGE_WITH_CC(CUART, "Bootleader Version : %s", send_the_version);
		send_the_data(ACK);
		send_the_data((UINT8)strlen(send_the_version));
		send_the_array((UINT8 *)send_the_version, strlen(send_the_version));
		LOG_MESSAGE_WITH_CC(CUART, "Succesfully send the version : %s", send_the_version);
		free(send_the_version);
		break;

	case BL_GET_HELP_CC:
		LOG_MESSAGE_WITH_CC(CUART, "Bootloader help processing");
		send_the_data(ACK);
		send_the_data((UINT8)TOTAL_COMMAND_SUPPORTED);
		for (int i = 0; i < TOTAL_COMMAND_SUPPORTED; i++)
			send_the_data((UINT8)command_code[i]);
		LOG_MESSAGE_WITH_CC(CUART, "Succesfully send all the command code of bootloader");
		break;

	case BL_GET_CID_CC:
		LOG_MESSAGE_WITH_CC(CUART, "Bootloader CID processing started");
		send_the_data(ACK);
		send_the_data((UINT8)2);
		UINT8 *device_id = malloc(sizeof(UINT8) * 2);
		get_the_device_id(device_id);
		send_the_array(device_id, 2);
		free(device_id);
		LOG_MESSAGE_WITH_CC(CUART, "Succesfully send the device id code");
		break;

	case BL_GET_RDP_STATUS_CC:
		LOG_MESSAGE_WITH_CC(CUART, "Bootloader RDP processing started");
		send_the_data(ACK);
		send_the_data((UINT8)1);
		send_the_data(get_the_rdp_status());
		LOG_MESSAGE_WITH_CC(CUART, "Succesfully send the RDP status");
		break;

	case BL_GO_TO_ADDR_CC:
		LOG_MESSAGE_WITH_CC(CUART, "Bootloader GO TO ADDR processing started");
		send_the_data(ACK);
		send_the_data((UINT8)1);
		UINT32 *go_to_address = (UINT32 *)((payload_data[2] | payload_data[3] << 8 | payload_data[4] << 16 | payload_data[5] << 24 | 1));
		if (verify_address(go_to_address) == ADDRESS_INVALID)
		{
			LOG_MESSAGE_WITH_CC(CUART, "Address is invalid so we send NACK");
			send_the_data(NACK);
			send_the_data((UINT8)1);
			send_the_data(DATA_IMPROPER);
			break;
		}
		else
		{
			LOG_MESSAGE_WITH_CC(CUART, "Address is valid so we send ACK");
			send_the_data(ACK);
			send_the_data((UINT8)1);
			send_the_data(ADDRESS_VALID);
		}
		void (*jump_to_address)(void) = (void (*)(void))(go_to_address);
		jump_to_address();
		break;

	case BL_FLASH_ERASE_CC:
		LOG_MESSAGE_WITH_CC(CUART, "Flash erase processing started");
		send_the_data(ACK);
		send_the_data((UINT8)1);
		if((ret = flash_erase_sector(payload_data[2],payload_data[3])) != 0){
			LOG_MESSAGE_WITH_CC(CUART,"Flash erase on this sector [%d] fail ",ret);
			send_the_data(INVALID);
		}
		LOG_MESSAGE_WITH_CC(CUART,"Flash erase happen succesfully");
		send_the_data(VALID);
		break;

	case BL_MEM_WRITE_CC:
		LOG_MESSAGE_WITH_CC(CUART,"Memory write processing started");
		send_the_data(ACK);
		send_the_data((UINT8)1);

		UINT32 *address = (payload_data[2] | payload_data[3] << 8 | payload_data[4] << 16 | payload_data[5] << 24);
		LOG_MESSAGE_WITH_CC(CUART,"Address where we have to write : 0x%x",address);

		/*Here we  pass the initial address where we have to put and then address and total no of elemenets*/
		if(write_into_flash(address,&payload_data[7],payload_data[6]) != 0){
			LOG_MESSAGE_WITH_CC(CUART,"Memory write fail");
			send_the_data(INVALID);	
		}
		LOG_MESSAGE_WITH_CC(CUART,"Succesfully write to memory");
		send_the_data(VALID);

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

static void get_the_device_id(UINT8 *pData)
{
	UINT32 *ptr = (UINT32 *)0xE0042000;
	pData[0] = *ptr & 0xFF;
	pData[1] = (*ptr >> 8) & 0x0F;

	LOG_MESSAGE_WITH_CC(CUART, "Calculated CID is 0x%x%x", pData[1], pData[0]);
	return;
}

static UINT8 get_the_rdp_status(void)
{
	UINT32 *ptr = (UINT32 *)0x1FFFC000;

	UINT8 rdp_status = (*ptr & 0x0000FF00) >> 8;

	LOG_MESSAGE_WITH_CC(CUART, "Calculated RDP status is 0x%x", rdp_status);

	return rdp_status;
}

static UINT8 flash_erase(UINT8 sector)
{
	if (sector < 0 || sector > 8)
	{
		LOG_MESSAGE_WITH_CC(CUART, "Incorrect sector : %d are their", sector);
		return 1;
	}

	FLASH_INTERFACE *pflashinterface = (FLASH_INTERFACE *)0x40023C00;

	/*Unlock the flash interface register*/
    if(pflashinterface -> FLASH_CR & (1 << 31)){
	pflashinterface -> FLASH_KEYR = 0x45670123;
	pflashinterface -> FLASH_KEYR = 0xCDEF89AB;
    }
	// pflashinterface -> FLASH_OPTKEYR = 0x45670123;
	// pflashinterface -> FLASH_OPTKEYR = 0xCDEF89AB;

	/*Wait for the busy bit to cleared*/
	while (pflashinterface->FLASH_SR & (1 << 16));

	/*Individual sector we have to remove*/
	if (sector != 8)
	{
		LOG_MESSAGE_WITH_CC(CUART, "Erase this sector : %d only", sector);
		/*Select the SER bit and sector no of that*/
		pflashinterface->FLASH_CR |= (1 << 1);
		pflashinterface->FLASH_CR |= (sector << 3);
	}
	else
	{ /*Complete Flash we have to erase*/
		LOG_MESSAGE_WITH_CC(CUART, "Erase all the sector");
		pflashinterface->FLASH_CR |= (1 << 2);
	}

	/*Start*/
	pflashinterface->FLASH_CR |= (1 << 16);

	/*Wait for the busy bit to cleared*/
	while (pflashinterface->FLASH_SR & (1 << 16));

	LOG_MESSAGE_WITH_CC(CUART, "Sector : %d are succefully cleared", sector);

	return 0;
}

static UINT8 flash_erase_sector(UINT8 sectorNo, UINT8 noofsector){
	/*We have to erase all sector of flash then we pass 8*/
	if(sectorNo == 0 && noofsector == 7) return flash_erase(noofsector + 1);

	/*Else we have to traver each sector an erase*/
	for(UINT8 i=sectorNo;i<(sectorNo + noofsector);i++){
		if(flash_erase(i)) return 1;
	}
	/*return success*/
	return 0;
}

static UINT8 write_into_flash(UINT8 *address, UINT8 *value, UINT8 size)
{

	/*Verify the address*/
	if (verify_address(address) == ADDRESS_INVALID)
		return INVALID;

	FLASH_INTERFACE *pflashinterface = (FLASH_INTERFACE *)0x40023C00;

	for (UINT8 i = 0; i < size; i++)
	{

		/*Unlock if FLASH_CR is lock*/
		if (pflashinterface->FLASH_CR & (1 << 31))
		{
			pflashinterface->FLASH_KEYR = 0x45670123;
			pflashinterface->FLASH_KEYR = 0xCDEF89AB;
		}

		/*Wait for the busy bit to cleared*/
		while (pflashinterface->FLASH_SR & (1 << 16))
			;

		/*Set the programming bit*/
		pflashinterface->FLASH_CR |= (1 << 0);

		/*Programm the correspondig address*/
		address[i] = value[i];

		/*Wait for the busy bit to cleared*/
		while (pflashinterface->FLASH_SR & (1 << 16))
			;
	}
	/*return success*/
	return 0;
}

static UINT8 verify_address(UINT32 *go_to_address)
{

	LOG_MESSAGE_WITH_CC(CUART, "Verifying the address : 0x%x", go_to_address);
	if (go_to_address >= (UINT32 *)SRAM1_BASE && go_to_address <= (UINT32 *)SRAM1_END)
		return ADDRESS_VALID;
	else if (go_to_address >= (UINT32 *)SRAM2_BASE && go_to_address <= (UINT32 *)SRAM2_END)
		return ADDRESS_VALID;
	else if (go_to_address >= (UINT32 *)FLASH_BASE && go_to_address <= (UINT32 *)FLASH_END)
		return ADDRESS_VALID;
	else
		return ADDRESS_INVALID;
}

__attribute__((section(".my_function"))) static void dummy_function(void)
{
	LOG_MESSAGE_WITH_CC(CUART, "Dummy function is called");
	return;
}
