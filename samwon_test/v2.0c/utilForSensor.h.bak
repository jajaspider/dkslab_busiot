#pragma once
#include "codes.h"
#include "utilForPacket.h"
#include <stdint.h>
#include <stdarg.h>

#define BYTE						unsigned char
//#define SENSOR_WORKING
#define DevAddr 0x53 //device address

#define	PCF	120
#define	PIN_GAS 5
#define GAS_LEVEL_BORDER	170

typedef struct acc_dat {
	int x;
	int y;
	int z;
}acc_dat;

acc_dat adxl345_read_xyz (int fd);
acc_dat adxl345_read_xyz_0to1 (int fd,
																BYTE *_x0, BYTE *_x1,
																BYTE *_y0, BYTE *_y1,
																BYTE *_z0, BYTE *_z1);
																
void adxl345_init (int fd);
void Read_dht11_data (int32_t dht11_data[5]);

int read_pcf8591_for_gas (int *isDanger);