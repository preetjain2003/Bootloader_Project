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
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Write the valide address to the device: ");
        UINT32 address = 0;
        scanf("0x%lx", &address);
        printf("Address entered is : 0x%lx \n", address);
        /* Assign the value to the data_packed */
        data_packed[0] = BL_GO_TO_ADDR_LEN - 1;
        data_packed[1] = BL_GO_TO_ADDR_CC;

        /*Convert the address to byte*/
        for(int i=0;i<4;i++) data_packed[2+i] = convet_word_to_byte(address,i);

        /*Calculate the CRC of that */
        crc = crc_calculate(data_packed, 6);
        printf("Calculated the CRC : 0x%x \n", (unsigned int)crc);

        /* Know crc is 32 bytes so we have split into 4 chunks of 8 byte
          it should folow little endian */
        for(int i=0;i<4;i++) data_packed[6+i] = convet_word_to_byte(crc,i);
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