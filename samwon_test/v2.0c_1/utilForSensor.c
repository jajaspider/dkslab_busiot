#include "utilForSensor.h"

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <wiringPi.h>
#include <pcf8591.h>

void adxl345_init (int fd) {
	
	#ifdef SENSOR_WORKING
	wiringPiI2CWriteReg8 (fd, 0x31, 0x0b);
	wiringPiI2CWriteReg8 (fd, 0x2d, 0x08);
	//wiringPiI2CWriteReg8 (fd, 0x2e, 0x00);
	wiringPiI2CWriteReg8 (fd, 0x1e, 0x00);
	wiringPiI2CWriteReg8 (fd, 0x1f, 0x00);
	wiringPiI2CWriteReg8 (fd, 0x20, 0x00);

	wiringPiI2CWriteReg8 (fd, 0x21, 0x00);
	wiringPiI2CWriteReg8 (fd, 0x22, 0x00);
	wiringPiI2CWriteReg8 (fd, 0x23, 0x00);

	wiringPiI2CWriteReg8 (fd, 0x24, 0x01);
	wiringPiI2CWriteReg8 (fd, 0x25, 0x0f);
	wiringPiI2CWriteReg8 (fd, 0x26, 0x2b);
	wiringPiI2CWriteReg8 (fd, 0x27, 0x00);

	wiringPiI2CWriteReg8 (fd, 0x28, 0x09);
	wiringPiI2CWriteReg8 (fd, 0x29, 0xff);
	wiringPiI2CWriteReg8 (fd, 0x2a, 0x80);
	wiringPiI2CWriteReg8 (fd, 0x2c, 0x0a);
	wiringPiI2CWriteReg8 (fd, 0x2f, 0x00);
	wiringPiI2CWriteReg8 (fd, 0x38, 0x9f);
	#endif
}

acc_dat adxl345_read_xyz (int fd) {
	
	char x0, y0, z0, x1, y1, z1;
	acc_dat acc_xyz;
	acc_xyz.x = acc_xyz.y = acc_xyz.z = 0;
	
	#ifdef SENSOR_WORKING
	x0 = 0xff - wiringPiI2CReadReg8(fd, 0x32);
	x1 = 0xff - wiringPiI2CReadReg8(fd, 0x33);
	y0 = 0xff - wiringPiI2CReadReg8(fd, 0x34);
	y1 = 0xff - wiringPiI2CReadReg8(fd, 0x35);
	z0 = 0xff - wiringPiI2CReadReg8(fd, 0x36);
	z1 = 0xff - wiringPiI2CReadReg8(fd, 0x37);

	acc_xyz.x =  (int)x0 - (int)x1;
	acc_xyz.y = -(int)y0 + (int)y1;
	acc_xyz.z =  (int)z0 - (int)z1;
	#endif

	return acc_xyz;
}

acc_dat adxl345_read_xyz_0to1 (int fd,
																BYTE *_x0, BYTE *_x1,
																BYTE *_y0, BYTE *_y1,
																BYTE *_z0, BYTE *_z1) {
	
	char x0, y0, z0, x1, y1, z1;
	acc_dat acc_xyz;
	acc_xyz.x = acc_xyz.y = acc_xyz.z = 0;
	
	#ifdef SENSOR_WORKING
	*_x0 = x0 = 0xff - wiringPiI2CReadReg8(fd, 0x32);
	*_x1 = x1 = 0xff - wiringPiI2CReadReg8(fd, 0x33);
	*_y0 = y0 = 0xff - wiringPiI2CReadReg8(fd, 0x34);
	*_y1 = y1 = 0xff - wiringPiI2CReadReg8(fd, 0x35);
	*_z0 = z0 = 0xff - wiringPiI2CReadReg8(fd, 0x36);
	*_z1 = z1 = 0xff - wiringPiI2CReadReg8(fd, 0x37);

	acc_xyz.x =  (int)x0 - (int)x1;
	acc_xyz.y = -(int)y0 + (int)y1;
	acc_xyz.z =  (int)z0 - (int)z1;
	#endif

	return acc_xyz;
}

void Read_dht11_data (int32_t dht11_data[5]) {
	int32_t tmp_dht11_data[5];
	uint8_t	lastState	= HIGH;
	uint8_t	counter		= 0;
	uint8_t	j = 0, i;
	uint8_t	flag		= HIGH;
	uint8_t	state		= 0;
	//float	f;

	#ifndef SENSOR_WORKING
	dht11_data[0] = dht11_data[1] = dht11_data[2] = dht11_data[3] = dht11_data[4] = 0;
	#endif

	tmp_dht11_data[0] = tmp_dht11_data[1] = tmp_dht11_data[2] = tmp_dht11_data[3] = tmp_dht11_data[4] = 0;
	
	#ifdef SENSOR_WORKING
	pinMode(DHTPIN, OUTPUT);
	digitalWrite(DHTPIN, LOW);
	delay(18);

	digitalWrite(DHTPIN, HIGH);
	delayMicroseconds(30);
	pinMode(DHTPIN, INPUT);

	for(i = 0; i < MAXTIMINGS; i++) {
		counter = 0;

		while(digitalRead(DHTPIN) == lastState) {
			counter++;
			delayMicroseconds(1);

			if(counter == 200) break;
		}

		lastState = digitalRead(DHTPIN);

		if(counter == 200) break;
		if(i >= 4 && (i%2==0)) {
			tmp_dht11_data[j/8] <<= 1;

			if(counter > 25)
				tmp_dht11_data[j/8] |= 1;

			j++;
		}
	}

	if(j>= 40 && (tmp_dht11_data[4] == ((tmp_dht11_data[0] + tmp_dht11_data[1] + tmp_dht11_data[2] + tmp_dht11_data[3]) & 0xff))) {
		;//printf("			humidity = %d.%d %% Temperature = %d.%d *C \n", dht11_data[0], dht11_data[1], dht11_data[2], dht11_data[3]);
		dht11_data[0] = tmp_dht11_data[0];
		dht11_data[1] = tmp_dht11_data[1];
		dht11_data[2] = tmp_dht11_data[2];
		dht11_data[3] = tmp_dht11_data[3];
		dht11_data[4] = tmp_dht11_data[4];
	}
	else {
		//printf("			Data get failed\n");
		
		/*
		dht11_data[0] = 123456;
		dht11_data[1] = 123456;
		dht11_data[2] = 123456;
		dht11_data[3] = 123456;
		*/
	}
	#endif
}

int read_pcf8591_for_gas (int *isDanger) {
	int gasLevel = 128;
	
	#ifdef SENSOR_WORKING
	gasLevel = analogRead(PCF + 0);
	
	if (gasLevel > GAS_LEVEL_BORDER)
		*isDanger = 1; //danger
	else
		*isDanger = 0; //safe
	#endif
	
	return gasLevel;
}