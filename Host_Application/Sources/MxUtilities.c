#include "MxTypedef.h"

#define GENERATED_POLYNOMIAL 0x4C11DB7
#define INITIAL_CRC_VALUE    0xFFFFFFFF
#define MSB_MASK             0x80000000


UINT8 convet_word_to_byte(UINT32 data, UINT8 index){
    UINT8 byte_data = (data >> (index*8)) & 0xFF;
    return byte_data;   
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
        
        crc = crc_accumulate(input_data[i],crc);
    }

    return crc;
}

