#include <MxTypedef.h>
#include <MxBlcommands.h>
#include <MxWindows_serial_port.h>
#include <MxUtilities.h>
#include <MxBlreplyprocessing.h>


UINT8 data_packed[MAX_COMMAND_LENGTH];
UINT32 crc;

void processing_the_command(UINT32 command)
{
    __attribute__((unused)) char c;
    unsigned int sector_number = 0, number_of_sectors = 0;
    UINT32 address = 0;
    UINT8 size = 0;
    long size_of_bin = 0;
    UINT8 data_buffer[MAX_BIN_SIZE] = {0};
    UINT8 total_iteration = 0;

    // Decrment by 1 because we compare with all value which
    // start form 0 indexing
    command--;

    switch (command)
    {

    default:
        printf("Commands doesn't exist \n");
        return;

    case BL_GET_VER:

        /* Assign the value to the data_packed */
        data_packed[0] = BL_GET_VER_LEN - 1;
        data_packed[1] = BL_GET_VER_CC;

        printf("Assigned the length and command code \n");

        /*Calculate the CRC*/
        crc = crc_calculate(data_packed, 2);
        printf("Calculated the CRC : 0x%x \n", (unsigned int)crc);

        /* Know crc is 32 bytes so we have split into 4 chunks of 8 byte
          it should folow little endian */
        data_packed[2] = convet_word_to_byte(crc, 0);
        data_packed[3] = convet_word_to_byte(crc, 1);
        data_packed[4] = convet_word_to_byte(crc, 2);
        data_packed[5] = convet_word_to_byte(crc, 3);
        printf("Added the CRC to the data packed \n");

        /*Send the data packed to serial port*/
        if (!write_data(data_packed, BL_GET_VER_LEN))
        {
            printf("Succesfully sending the command \n");
        }

        else
        {
            printf("Failed to send the command \n");
            return;
        }

        printf("Waiting for the reply from the device \n");
        reply_processing(BL_GET_VER);
        break;

    case BL_GET_HELP:

        /* Assign the value to the data_packed */
        data_packed[0] = BL_GET_HELP_LEN - 1;
        data_packed[1] = BL_GET_HELP_CC;

        printf("Assigned the length and command code \n");

        /*Calculate the CRC*/
        crc = crc_calculate(data_packed, 2);
        printf("Calculated the CRC : 0x%x \n", (unsigned int)crc);

        /* Know crc is 32 bytes so we have split into 4 chunks of 8 byte
          it should folow little endian */
        data_packed[2] = convet_word_to_byte(crc, 0);
        data_packed[3] = convet_word_to_byte(crc, 1);
        data_packed[4] = convet_word_to_byte(crc, 2);
        data_packed[5] = convet_word_to_byte(crc, 3);
        printf("Added the CRC to the data packed \n");

        /*Send the data packed to serial port*/
        if (!write_data(data_packed, BL_GET_HELP_LEN))
        {
            printf("Succesfully sending the command \n");
        }

        else
        {
            printf("Failed to send the command \n");
            return;
        }

        printf("Waiting for the reply from the device \n");
        reply_processing(BL_GET_HELP);
        break;

    case BL_GET_CID:

        /* Assign the value to the data_packed */
        data_packed[0] = BL_GET_CID_LEN - 1;
        data_packed[1] = BL_GET_CID_CC;

        printf("Assigned the length and command code \n");

        /*Calculate the CRC*/
        crc = crc_calculate(data_packed, 2);
        printf("Calculated the CRC : 0x%x \n", (unsigned int)crc);

        /* Know crc is 32 bytes so we have split into 4 chunks of 8 byte
          it should folow little endian */
        data_packed[2] = convet_word_to_byte(crc, 0);
        data_packed[3] = convet_word_to_byte(crc, 1);
        data_packed[4] = convet_word_to_byte(crc, 2);
        data_packed[5] = convet_word_to_byte(crc, 3);
        printf("Added the CRC to the data packed \n");

        /*Send the data packed to serial port*/
        if (!write_data(data_packed, BL_GET_CID_LEN))
        {
            printf("Succesfully sending the command \n");
        }

        else
        {
            printf("Failed to send the command \n");
            return;
        }

        printf("Waiting for the reply from the device \n");
        reply_processing(BL_GET_CID);

        break;

    case BL_GET_RDP_STATUS:

        /* Assign the value to the data_packed */
        data_packed[0] = BL_GET_RDP_STATUS_LEN - 1;
        data_packed[1] = BL_GET_RDP_STATUS_CC;

        printf("Assigned the length and command code \n");

        /*Calculate the CRC*/
        crc = crc_calculate(data_packed, 2);
        printf("Calculated the CRC : 0x%x \n", (unsigned int)crc);

        /* Know crc is 32 bytes so we have split into 4 chunks of 8 byte
          it should folow little endian */
        data_packed[2] = convet_word_to_byte(crc, 0);
        data_packed[3] = convet_word_to_byte(crc, 1);
        data_packed[4] = convet_word_to_byte(crc, 2);
        data_packed[5] = convet_word_to_byte(crc, 3);
        printf("Added the CRC to the data packed \n");

        /*Send the data packed to serial port*/
        if (!write_data(data_packed, BL_GET_RDP_STATUS_LEN))
        {
            printf("Succesfully sending the command \n");
        }

        else
        {
            printf("Failed to send the command \n");
            return;
        }

        printf("Waiting for the reply from the device \n");
        reply_processing(BL_GET_RDP_STATUS);

        break;

    case BL_GO_TO_ADDR:
        while ((c = getchar()) != '\n' && c != EOF) ;
        printf("Write the valid address to the device: ");
        scanf("0x%lx", &address);
        printf("Address entered is : 0x%lx \n", address);
        /* Assign the value to the data_packed */
        data_packed[0] = BL_GO_TO_ADDR_LEN - 1;
        data_packed[1] = BL_GO_TO_ADDR_CC;

        /*Convert the address to byte*/
        for (int i = 0; i < 4; i++)
            data_packed[2 + i] = convet_word_to_byte(address, i);

        /*Calculate the CRC of that */
        crc = crc_calculate(data_packed, 6);
        printf("Calculated the CRC : 0x%x \n", (unsigned int)crc);

        /* Know crc is 32 bytes so we have split into 4 chunks of 8 byte
          it should folow little endian */
        for (int i = 0; i < 4; i++)
            data_packed[6 + i] = convet_word_to_byte(crc, i);
        printf("Added the CRC to the data packed \n");

        /*Send the data packed to serial port*/
        if (!write_data(data_packed, BL_GO_TO_ADDR_LEN))
        {
            printf("Succesfully sending the command \n");
        }

        else
        {
            printf("Failed to send the command \n");
            return;
        }

        printf("Waiting for the reply from the device \n");
        reply_processing(BL_GO_TO_ADDR);
        break;

    case BL_FLASH_ERASE:

        /*Read the sector no and no of sectors*/
        printf("Enter the initial sector number to erase : ");
        scanf("%u", &sector_number);
        printf("Enter the number of sectors to erase : ");
        scanf("%u", &number_of_sectors);

        /* Assign the value to the data_packed */
        data_packed[0] = BL_FLASH_ERASE_LEN - 1;
        data_packed[1] = BL_FLASH_ERASE_CC;
        data_packed[2] = sector_number;
        data_packed[3] = number_of_sectors;

        /*Calculate the crc of that*/
        crc = crc_calculate(data_packed, 4);

        /*Convert word to byte and put in the data_packed*/
        for (int i = 0; i < 4; i++)
            data_packed[4 + i] = convet_word_to_byte(crc, i);
        printf("Added the CRC to the data packed \n");

        /*Send the data packed to serial port*/
        if (!write_data(data_packed, BL_FLASH_ERASE_LEN))
        {
            printf("Succesfully sending the command \n");
        }

        else
        {
            printf("Failed to send the command \n");
            return;
        }

        printf("Waiting for the reply from the device \n");
        reply_processing(BL_FLASH_ERASE);

        break;

    case BL_MEM_WRITE:
        while ((c = getchar()) != '\n' && c != EOF) ;
        
        address = 0x08008000; // Default address for writing, can be modified as needed

        printf("Memory address entered is : 0x%lx \n", address);

        /*Read the Memory address and all other thing  we can take from the firmware bin file*/
        if ((size_of_bin = bin_to_array(&data_buffer[0])) == -1)
        {
            printf("Error in fetching the details from the binary \n");
            return;
        }

        printf("Calcualte the binary size and size : %ld \n", size_of_bin);

        /*When size of bin > TOTAL_MEM_WRITE*/
        total_iteration = (size_of_bin / TOTAL_MEM_WRITE) + 1;
        printf("Total iteration : %d \n",total_iteration);
        for(int j=0; j<total_iteration && size_of_bin != 0; j++){

        /*Calcuate the size to send*/
        size = (size_of_bin > TOTAL_MEM_WRITE)?TOTAL_MEM_WRITE:size_of_bin;
        size_of_bin -= size;
        printf("Iteration : %d Size of payload : %d \n",j,size);

        /* Assign the value to the data_packed */
        data_packed[0] = BL_MEM_WRITE_LEN + size - 1;
        data_packed[1] = BL_MEM_WRITE_CC;

        /*Convert the address to byte*/
        for (int i = 0; i < 4; i++) data_packed[2 + i] = convet_word_to_byte(address, i);

        /*Assign the size to that*/
        data_packed[6] = size;

        /*Assign the value to the payload*/
        for (int i=0; i<size; i++) data_packed[7+i] = data_buffer[j*TOTAL_MEM_WRITE + i];

        /*Calculate the crc of that*/
        /*We use -3 because already the data_packed[0] length are 1 byte small*/
        crc = crc_calculate(data_packed, data_packed[0] - 3);

        /*Assign the crc value to the data packed*/
        for (int i = 3; i >= 0; i--) data_packed[data_packed[0] - i] = convet_word_to_byte(crc, 3 - i);
        printf("Added the CRC to the data packed \n");

        /*Send the data packed to serial port*/
        if (!write_data(data_packed, data_packed[0] + 1))
        {
            printf("Iteration : %d  Sucessfully send the command \n",j);
        }

        else
        {
            printf("Failed to send the command \n");
            return;
        }
        
        printf("Waiting for the reply from the device \n");
        reply_processing(BL_MEM_WRITE);

        /*Increment the address*/
        address += size;


        /*Delay*/
        sleep(2);
        
    }
    }
}

// static void send_the_length_and_CC(UINT8 Length_to_follow, UINT8 Command_code){

//     /*Send the Length to follow
//      (Total Length - 1(Exclude the length to follow length)) */

//      UINT8 send_data[2] = {Length_to_follow - 1, Command_code};

//      if(!write_data(send_data,2)){
//         printf("Succesfully sending the Length to follow and Command code \n");
//      }

//      else{
//         printf("Failed to send the Length and Command Code \n");
//      }

// }