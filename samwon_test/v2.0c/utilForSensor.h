#pragma once
#include "codes.h"
#include <stdint.h>
#include <stdarg.h>

//#define SENSOR_WORKING


typedef struct acc_dat {
	int x;
	int y;
	int z;
}acc_dat;

acc_dat adxl345_read_xyz (int fd); //
void adxl345_init (int fd);
void Read_dht11_data (int32_t dht11_data[5]); //