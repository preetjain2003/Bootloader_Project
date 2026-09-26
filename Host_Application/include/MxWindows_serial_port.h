#ifndef MX_WINDOWS_SERIAL_PORT_H
#define MX_WINDOWS_SERIAL_PORT_H

#include "MxTypedef.h"

void serial_port_configuration(const char *pcCommPort);
int read_data(UINT8 *data_read, UINT8 length);
int write_data(UINT8 *data_write, UINT8 length);
int close_serial_communication();


#endif //MX_WINDOWS_SERIAL_PORT_H