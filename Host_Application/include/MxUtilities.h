#ifndef MX_UTILITIES_H
#define MX_UTILITIES_H  

#include "MxTypedef.h"

#define MAX_BIN_SIZE 65535

UINT8 convet_word_to_byte(UINT32 data, UINT8 index);
UINT32 crc_calculate(UINT8 *input_data, UINT32 len);
UINT32 crc_accumulate(UINT32 input_data, UINT32 initial_crc);
long bin_to_array(UINT8 *value);

#endif // MX_UTILITIES_H