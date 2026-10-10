#include "MxTypedef.h"

#define GENERATED_POLYNOMIAL 0x4C11DB7
#define INITIAL_CRC_VALUE    0xFFFFFFFF
#define MSB_MASK             0x80000000


UINT8 convet_word_to_byte(UINT32 data, UINT8 index){
    UINT8 byte_data = (data >> (index*8)) & 0xFF;
    return byte_data;   
}

long bin_to_array(UINT8 *value){

    UINT32 size;

    FILE *fptr = fopen("D:\\Bootloader Project\\Host_Application\\bin\\firmware.bin", "rb");

    if (fptr == NULL)
    {
        printf("Error : could not open file \n");
        return -1;
    }

    if (fseek(fptr, 0, SEEK_END) != 0)
    {
        printf("Error : fseek end failed \n");
        fclose(fptr);
        return -1;
    }

    size = ftell(fptr);

    /*Move again to initial position*/
    if (fseek(fptr, 0, SEEK_SET) != 0)
    {
        printf("Error : fseek set failed \n");
        fclose(fptr);
        return -1;
    }

    fread(value,sizeof(UINT8),size,fptr);

    fclose(fptr);

    return size;
}

UINT32 crc_accumulate(UINT32 input_data, UINT32 initial_crc){

    UINT32 bindex = 0;
    UINT32 crc = initial_crc ^ input_data;

    while(bindex < sizeof(input_data)*8){

        if(crc & MSB_MASK){

            crc = (crc << 1)^GENERATED_POLYNOMIAL;
        }
        else{
             crc = (crc << 1);
        }

        bindex++;
    }

    return crc;
}


UINT32 crc_calculate(UINT8 *input_data, UINT32 len){

    UINT32 crc = INITIAL_CRC_VALUE;

    for(UINT32 i = 0; i<len; i++){
        
        UINT32 data = input_data[i];
        crc = crc_accumulate(data,crc);
    }

    return crc;
}

