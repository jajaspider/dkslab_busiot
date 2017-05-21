#pragma warning(disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utilForPacket.h"
#include "codes.h"
#include "paths.h"


int32_t GetSensorDataPacketSize (SensorDataPacket *sensorDataPacket) {
	int32_t size = 0;

	size += sizeof(sensorDataPacket->control_stx);
	size += sizeof(sensorDataPacket->serialId);
	size += sizeof(sensorDataPacket->terminalId);
	size += sizeof(sensorDataPacket->responseCode);
	size += sizeof(sensorDataPacket->errorCode);
	size += sizeof(sensorDataPacket->commandCode);
	size += sizeof(sensorDataPacket->seqNo);

	size += sizeof(sensorDataPacket->length);

	size += sizeof(sensorDataPacket->gpsTime);
	size += sizeof(sensorDataPacket->gpsX);
	size += sizeof(sensorDataPacket->gpsY);
	size += sizeof(sensorDataPacket->gpsSatelliteCount);

	size += sizeof(sensorDataPacket->thermometerTime);
	size += sizeof(sensorDataPacket->thermometerTemperature);

	size += sizeof(sensorDataPacket->coolerTime);
	size += sizeof(sensorDataPacket->coolerTemperature);

	size += sizeof(sensorDataPacket->usersTime);
	size += sizeof(sensorDataPacket->usersCount);
	size += sizeof(sensorDataPacket->oldUsersCount);

	size += sizeof(sensorDataPacket->hygrometerTime);
	size += sizeof(sensorDataPacket->hygrometerHumidity);

	size += sizeof(sensorDataPacket->panicButtonTime);
	size += sizeof(sensorDataPacket->panicButtonIsPushed);

	size += sizeof(sensorDataPacket->disabledPersonReservedTime);
	size += sizeof(sensorDataPacket->disabledPersonIsReserved);
	size += sizeof(sensorDataPacket->disabledPersonReservedStationId);
	size += sizeof(sensorDataPacket->disabledPersonPhon);

	size += sizeof(sensorDataPacket->wildDrivingTime);
	size += sizeof(sensorDataPacket->isWildDriving);

	size += sizeof(sensorDataPacket->gSensorX);
	size += sizeof(sensorDataPacket->gSensorY);
	size += sizeof(sensorDataPacket->gSensorZ);

	size += sizeof(sensorDataPacket->busSpeed);
	size += sizeof(sensorDataPacket->absoluteBarometricPressure);
	size += sizeof(sensorDataPacket->fuelTankLevelInput);
	size += sizeof(sensorDataPacket->engineOilTemperature);
	size += sizeof(sensorDataPacket->busInnerOxygen);
	size += sizeof(sensorDataPacket->runTimeToEngineStart);
	size += sizeof(sensorDataPacket->engineRPM);

	size += sizeof(sensorDataPacket->beaconTime);
	size += sizeof(sensorDataPacket->beaconUuid);
	size += sizeof(sensorDataPacket->beaconMajor);
	size += sizeof(sensorDataPacket->beaconMinor);

	size += sizeof(sensorDataPacket->speakerTime);
	size += sizeof(sensorDataPacket->speakerStationId);

	size += sizeof(sensorDataPacket->ioTime);
	size += sizeof(sensorDataPacket->ioInput);

	size += sizeof(sensorDataPacket->imageSize);
	size += sensorDataPacket->imageSize;//sizeof(*sensorDataPacket->imageData);

	size += sizeof(sensorDataPacket->errorCheck);
	size += sizeof(sensorDataPacket->control_etx);

	return size;
}


void InitSensorDataPacket (SensorDataPacket *sensorDataPacket) {
	memset(sensorDataPacket, '\0', sizeof(SensorDataPacket));
}

int32_t UpdateSensorDataPacket (SensorDataPacket *sensorDataPacket, int32_t takeAPicture) {
	int i;

	sensorDataPacket->control_stx[0]					=	CONTROL_STX;

	for (i = 0; i < 5; i++)
		sensorDataPacket->serialId[i] = g_serialId[i];
	for (i = 0; i < 4; i++)
		sensorDataPacket->terminalId[i] = g_terminalId[i];
	sensorDataPacket->responseCode[0]					=	RESPONSE_CODE_ACK;
	sensorDataPacket->errorCode[0]						=	ERROR_CODE_SUCCESS;
	sensorDataPacket->commandCode[0]					=	COMMAND_CODE_SEND_SENSOR_DATA;
	sensorDataPacket->seqNo[0]							=	SEQ_NO_FROM;

	//At last
	//sensorDataPacket->length							=	GetSensorDataPacketSizesensorDataPacket);

	GetGpsData_sensor2packet						(sensorDataPacket);
	GetThermometerData_sensor2packet				(sensorDataPacket);
	GetCoolerData_sensor2packet						(sensorDataPacket);
	GetUsersData_sensor2packet						(sensorDataPacket);
	GetHygrometerData_sensor2packet					(sensorDataPacket);
	GetPanicButtonData_sensor2packet				(sensorDataPacket);
	GetDisabledPersonReservationData_sensor2packet	(sensorDataPacket);
	GetWildDrivingData_sensor2packet				(sensorDataPacket);
	GetGSensorData_sensor2packet					(sensorDataPacket);
	GetOBD2Data_sensor2packet						(sensorDataPacket);
	GetBeaconData_sensor2packet						(sensorDataPacket);
	GetSpeakerData_sensor2packet					(sensorDataPacket);
	GetIoData_sensor2packet							(sensorDataPacket);

	if(takeAPicture)
		sensorDataPacket->imageSize						= TakeAPicture	(CAMERA_IMAGE_PATH, CAMERA_IMAGE_WIDTH, CAMERA_IMAGE_HEIGHT);

	GetImageData_sonsor2packet						(CAMERA_IMAGE_PATH, sensorDataPacket);

	sensorDataPacket->errorCheck[0]						=	ERROR_CHECK_STX;
	sensorDataPacket->control_etx[0]					=	CONTROL_ETX;

	sensorDataPacket->length	=	GetSensorDataPacketSize(sensorDataPacket);

	return 1;
}

void ClearSendBuff () {
	memset(g_sendBuff, '\0', SEND_BUFF_MAX_LENGTH);
	g_sendBuffInsertionLocation = 0;
}

void ClearSensorDataPacket (SensorDataPacket *sensorDataPacket) {
	memset(sensorDataPacket, '\0', SEND_BUFF_MAX_LENGTH);
}

int32_t GetOccurrenceTime () {
	int32_t time	= 235959999;
	int32_t power	= 5<<29;

	return	time | power;
}



int32_t AddDataToSendBuff_int (int32_t data) {
	int32_t i;
	BYTE *_data = (BYTE*)&data;

	if(g_sendBuffInsertionLocation + 4 > SEND_BUFF_MAX_LENGTH)
		return 0;

	for (i = 0; i < 4; i++)
		g_sendBuff[g_sendBuffInsertionLocation++] = _data[i];

	return 1;
}

int32_t AddDataToSendBuff_data (BYTE *data, int32_t dataLength) {
	int32_t i;

	if(g_sendBuffInsertionLocation + dataLength > SEND_BUFF_MAX_LENGTH)
		return 0;

	for (i = 0; i < dataLength; i++)
		g_sendBuff[g_sendBuffInsertionLocation++] = data[i];

	return 1;
}

int32_t AddDataToSendBuff_packet (SensorDataPacket *sensorDataPacket) {

	AddDataToSendBuff_data(sensorDataPacket->control_stx,						1);

	AddDataToSendBuff_data(sensorDataPacket->serialId,							5);
	AddDataToSendBuff_data(sensorDataPacket->terminalId,						4);
	AddDataToSendBuff_data(sensorDataPacket->responseCode,						1);
	AddDataToSendBuff_data(sensorDataPacket->errorCode,							1);
	AddDataToSendBuff_data(sensorDataPacket->commandCode,						1);
	AddDataToSendBuff_data(sensorDataPacket->seqNo,								1);

	AddDataToSendBuff_int(sensorDataPacket->length);

	AddDataToSendBuff_data(sensorDataPacket->gpsTime,							3);
	AddDataToSendBuff_data(sensorDataPacket->gpsX,								4);
	AddDataToSendBuff_data(sensorDataPacket->gpsY,								4);
	AddDataToSendBuff_data(sensorDataPacket->gpsSatelliteCount,					1);

	AddDataToSendBuff_data(sensorDataPacket->thermometerTime,					4);
	AddDataToSendBuff_data(sensorDataPacket->thermometerTemperature,			1);

	AddDataToSendBuff_data(sensorDataPacket->coolerTime,						4);
	AddDataToSendBuff_data(sensorDataPacket->coolerTemperature,					1);

	AddDataToSendBuff_data(sensorDataPacket->usersTime,							4);
	AddDataToSendBuff_data(sensorDataPacket->usersCount,						1);
	AddDataToSendBuff_data(sensorDataPacket->oldUsersCount,						1);

	AddDataToSendBuff_data(sensorDataPacket->hygrometerTime,					4);
	AddDataToSendBuff_data(sensorDataPacket->hygrometerHumidity,				1);

	AddDataToSendBuff_data(sensorDataPacket->panicButtonTime,					4);
	AddDataToSendBuff_data(sensorDataPacket->panicButtonIsPushed,				1);

	AddDataToSendBuff_data(sensorDataPacket->disabledPersonReservedTime,		4);
	AddDataToSendBuff_data(sensorDataPacket->disabledPersonIsReserved,			1);
	AddDataToSendBuff_int(sensorDataPacket->disabledPersonReservedStationId);
	AddDataToSendBuff_int(sensorDataPacket->disabledPersonPhon);

	AddDataToSendBuff_data(sensorDataPacket->wildDrivingTime,					4);
	AddDataToSendBuff_data(sensorDataPacket->isWildDriving,						1);

	AddDataToSendBuff_data(sensorDataPacket->gSensorX,							2);
	AddDataToSendBuff_data(sensorDataPacket->gSensorY,							2);
	AddDataToSendBuff_data(sensorDataPacket->gSensorZ,							2);

	AddDataToSendBuff_data(sensorDataPacket->busSpeed,							1);
	AddDataToSendBuff_data(sensorDataPacket->absoluteBarometricPressure,		1);
	AddDataToSendBuff_data(sensorDataPacket->fuelTankLevelInput,				1);
	AddDataToSendBuff_data(sensorDataPacket->engineOilTemperature,				1);
	AddDataToSendBuff_data((BYTE*)sensorDataPacket->busInnerOxygen,				2);
	AddDataToSendBuff_data(sensorDataPacket->runTimeToEngineStart,				2);
	AddDataToSendBuff_data(sensorDataPacket->engineRPM,							2);

	AddDataToSendBuff_data(sensorDataPacket->beaconTime,						4);
	AddDataToSendBuff_data(sensorDataPacket->beaconUuid,						16);
	AddDataToSendBuff_data(sensorDataPacket->beaconMajor,						2);
	AddDataToSendBuff_data(sensorDataPacket->beaconMinor,						2);

	AddDataToSendBuff_data(sensorDataPacket->speakerTime,						4);
	AddDataToSendBuff_int(sensorDataPacket->speakerStationId);

	AddDataToSendBuff_data(sensorDataPacket->ioTime,							4);
	AddDataToSendBuff_data(sensorDataPacket->ioInput,							1);

	AddDataToSendBuff_int(sensorDataPacket->imageSize);
	AddDataToSendBuff_data(sensorDataPacket->imageData,							sensorDataPacket->imageSize);

	AddDataToSendBuff_data(sensorDataPacket->errorCheck,						1);
	AddDataToSendBuff_data(sensorDataPacket->control_etx,						1);

	return 1;
}

int32_t GetGpsData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	_output_sensorDataPacket->gpsTime[0] = (unsigned char)122;
	_output_sensorDataPacket->gpsTime[1] = (unsigned char)5;
	_output_sensorDataPacket->gpsTime[2] = (unsigned char)3;

	_output_sensorDataPacket->gpsX[0] = 0x6F;
	_output_sensorDataPacket->gpsX[1] = 0xFF;
	_output_sensorDataPacket->gpsX[2] = 0xFF;
	_output_sensorDataPacket->gpsX[3] = 0xFF;

	_output_sensorDataPacket->gpsY[0] = 0xDE;
	_output_sensorDataPacket->gpsY[1] = 0x21;
	_output_sensorDataPacket->gpsY[2] = 0xE8;
	_output_sensorDataPacket->gpsY[3] = 0x8E;

	_output_sensorDataPacket->gpsSatelliteCount[0] = 0x0F;

	return 1;
}

int32_t GetThermometerData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->thermometerTime[0] = resultTime[0];
	_output_sensorDataPacket->thermometerTime[1] = resultTime[1];
	_output_sensorDataPacket->thermometerTime[2] = resultTime[2];
	_output_sensorDataPacket->thermometerTime[3] = resultTime[3];

	_output_sensorDataPacket->thermometerTemperature[0] = 0xFF;

	return 1;
}

int32_t GetCoolerData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->coolerTime[0] = resultTime[0];
	_output_sensorDataPacket->coolerTime[1] = resultTime[1];
	_output_sensorDataPacket->coolerTime[2] = resultTime[2];
	_output_sensorDataPacket->coolerTime[3] = resultTime[3];

	_output_sensorDataPacket->coolerTemperature[0] = 0xFF;

	return 1;
}


int32_t GetUsersData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->usersTime[0] = resultTime[0];
	_output_sensorDataPacket->usersTime[1] = resultTime[1];
	_output_sensorDataPacket->usersTime[2] = resultTime[2];
	_output_sensorDataPacket->usersTime[3] = resultTime[3];

	_output_sensorDataPacket->usersCount[0] = 0x32;

	_output_sensorDataPacket->oldUsersCount[0] = 0x00;

	return 1;
}


int32_t GetHygrometerData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->hygrometerTime[0] = resultTime[0];
	_output_sensorDataPacket->hygrometerTime[1] = resultTime[1];
	_output_sensorDataPacket->hygrometerTime[2] = resultTime[2];
	_output_sensorDataPacket->hygrometerTime[3] = resultTime[3];

	_output_sensorDataPacket->hygrometerHumidity[0] = 0x64;

	return 1;
}

int32_t GetPanicButtonData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->panicButtonTime[0] = resultTime[0];
	_output_sensorDataPacket->panicButtonTime[1] = resultTime[1];
	_output_sensorDataPacket->panicButtonTime[2] = resultTime[2];
	_output_sensorDataPacket->panicButtonTime[3] = resultTime[3];

	_output_sensorDataPacket->panicButtonIsPushed[0] = 0x00;

	return 1;
}

int32_t GetDisabledPersonReservationData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->disabledPersonReservedTime[0] = resultTime[0];
	_output_sensorDataPacket->disabledPersonReservedTime[1] = resultTime[1];
	_output_sensorDataPacket->disabledPersonReservedTime[2] = resultTime[2];
	_output_sensorDataPacket->disabledPersonReservedTime[3] = resultTime[3];

	_output_sensorDataPacket->disabledPersonIsReserved[0] = 0;

	_output_sensorDataPacket->disabledPersonReservedStationId = 05060;

	_output_sensorDataPacket->disabledPersonPhon = 1012345678;

	return 1;
}

int32_t GetWildDrivingData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->wildDrivingTime[0] = resultTime[0];
	_output_sensorDataPacket->wildDrivingTime[1] = resultTime[1];
	_output_sensorDataPacket->wildDrivingTime[2] = resultTime[2];
	_output_sensorDataPacket->wildDrivingTime[3] = resultTime[3];

	_output_sensorDataPacket->isWildDriving[0] = 0;

	return 1;
}

int32_t GetGSensorData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	_output_sensorDataPacket->gSensorX[0] = 0x00;
	_output_sensorDataPacket->gSensorX[1] = 0x00;

	_output_sensorDataPacket->gSensorY[0] = 0x00;
	_output_sensorDataPacket->gSensorY[1] = 0x00;

	_output_sensorDataPacket->gSensorZ[0] = 0x00;
	_output_sensorDataPacket->gSensorZ[1] = 0x00;

	return 1;
}

int32_t GetOBD2Data_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	_output_sensorDataPacket->busSpeed[0] = 0x28;

	_output_sensorDataPacket->absoluteBarometricPressure[0] = 0x65;

	_output_sensorDataPacket->fuelTankLevelInput[0] = 0x32;

	_output_sensorDataPacket->engineOilTemperature[0] = 0x62;

	_output_sensorDataPacket->busInnerOxygen[0] = 0xFF;
	_output_sensorDataPacket->busInnerOxygen[1] = 0xFF;

	_output_sensorDataPacket->runTimeToEngineStart[0] = 0xE4;
	_output_sensorDataPacket->runTimeToEngineStart[1] = 0x9C;

	_output_sensorDataPacket->engineRPM[0] = 0xFF;
	_output_sensorDataPacket->engineRPM[1] = 0x0F;

	return 1;
}

int32_t GetBeaconData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int i;

	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->beaconTime[0] = resultTime[0];
	_output_sensorDataPacket->beaconTime[1] = resultTime[1];
	_output_sensorDataPacket->beaconTime[2] = resultTime[2];
	_output_sensorDataPacket->beaconTime[3] = resultTime[3];

	for (i = 0; i < 16; i++)
		_output_sensorDataPacket->beaconUuid[i] = 'A';

	_output_sensorDataPacket->beaconMajor[0] = 'B';
	_output_sensorDataPacket->beaconMajor[1] = 'B';

	_output_sensorDataPacket->beaconMinor[0] = 'C';
	_output_sensorDataPacket->beaconMinor[1] = 'C';

	return 1;
}

int32_t GetSpeakerData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->speakerTime[0] = resultTime[0];
	_output_sensorDataPacket->speakerTime[1] = resultTime[1];
	_output_sensorDataPacket->speakerTime[2] = resultTime[2];
	_output_sensorDataPacket->speakerTime[3] = resultTime[3];

	((int32_t*)&_output_sensorDataPacket->speakerStationId)[0] = 0x05;
	((int32_t*)&_output_sensorDataPacket->speakerStationId)[1] = 0x00;
	((int32_t*)&_output_sensorDataPacket->speakerStationId)[2] = 0x60;

	return 1;
}

int32_t GetIoData_sensor2packet (SensorDataPacket *_output_sensorDataPacket) {
	int32_t	currentTime	= GetOccurrenceTime();
	char	*resultTime	= (char*)&currentTime;

	_output_sensorDataPacket->ioTime[0] = resultTime[0];
	_output_sensorDataPacket->ioTime[1] = resultTime[1];
	_output_sensorDataPacket->ioTime[2] = resultTime[2];
	_output_sensorDataPacket->ioTime[3] = resultTime[3];

	_output_sensorDataPacket->ioInput[0] = 0x00;

	return 1;
}

int32_t GetImageData_sonsor2packet (char *filePath,
									SensorDataPacket *_output_sensorDataPacket) {
	FILE *fp;

	fp = fopen(filePath, "rb");
	if(fp == NULL) {
		printf("ERROR:: file open fail.\n");
		return 0;
	}

	fread(_output_sensorDataPacket->imageData, 1, _output_sensorDataPacket->imageSize, fp);
	fclose(fp);

	return 1;
}

int32_t TakeAPicture (char *filePath, int32_t width, int32_t height) {
	char 	buf[256];
	FILE	*fp;
	int	fileSize;

	memset(buf, '\0', 256);
	sprintf(buf, "raspistill -o %s -w %d -h %d", filePath, width, height);
	system(buf);


	fp = fopen(filePath, "rb");
	if (fp == NULL) {
		printf("ERROR:: file open fail.\n");
		return 0;
	}
	fseek(fp, 0L, SEEK_END);
	fileSize = ftell(fp);
	fclose(fp);

	return fileSize;
}








int32_t GetTime2Buff (BYTE buff[SEND_BUFF_MAX_LENGTH], double *_output_time) {
	int i = 0;
	char	temp[16] = {0, };

	BYTE	buff_time[4] = {0, };
	int		buff2int= 0;
	int		power	= 0;
	double	time	= 0.0;

	buff_time[0] = buff[g_recvBuffInsertionLocation++];
	buff_time[1] = buff[g_recvBuffInsertionLocation++];
	buff_time[2] = buff[g_recvBuffInsertionLocation++];
	buff_time[3] = buff[g_recvBuffInsertionLocation++];

	buff2int = *(int*)buff_time;
	time = buff2int & 0x1FFFFFFF;



	/*
	power = sprintf(temp, "%d", buff2int) - 1;
	for (i = 0; i < power; i++)
		time *= 0.1;


	power = buff_time[0] & 0xE0;
	for (int i = 0; i < power; i++)
		time *= 10;
	*/

	power = sprintf(temp, "%d", (int)time) - ((buff2int & 0xE0000000)>>29) - 1;
	for (i = 0; i < power; i++)
		time *= 0.1;



	*_output_time = time;


	return 1;
}



int32_t GetGpsData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	char	temp[16] = {0, };
	int		i;

	int		power = 0;
	BYTE	buff_time[4] = {0, 0, 0, 0};
	int		buff2int = 0;
	double	buff2double = 0.0;

	_output_sensorDataValue->gpsTime[0] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->gpsTime[1] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->gpsTime[2] = buff[g_recvBuffInsertionLocation++];





	_output_sensorDataValue->gpsX = buff[g_recvBuffInsertionLocation++];
	buff_time[1] = buff[g_recvBuffInsertionLocation++];
	buff_time[2] = buff[g_recvBuffInsertionLocation++];
	buff_time[3] = buff[g_recvBuffInsertionLocation++];
	buff2int = *(int*)buff_time;
	buff2double = buff2int;
	power = sprintf(temp, "%d", buff2int);

	for (i = 0; i < power; i++)
		buff2double *= 0.1;

	_output_sensorDataValue->gpsX += buff2double;





	_output_sensorDataValue->gpsY = buff[g_recvBuffInsertionLocation++];
	buff[1] = buff[g_recvBuffInsertionLocation++];
	buff[2] = buff[g_recvBuffInsertionLocation++];
	buff[3] = buff[g_recvBuffInsertionLocation++];
	buff2int = *(int*)buff;
	buff2double = buff2int;
	power = sprintf(temp, "%d", buff2int);

	for (i = 0; i < power; i++)
		buff2double *= 0.1;

	_output_sensorDataValue->gpsY += buff2double;





	_output_sensorDataValue->gpsSatelliteCount = buff[g_recvBuffInsertionLocation++];




	return 1;
}

int32_t GetThermometerData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {

	GetTime2Buff (buff, &_output_sensorDataValue->thermometerTime);
	_output_sensorDataValue->thermometerTemperature = buff[g_recvBuffInsertionLocation++] - 40;

	return 1;
}

int32_t GetCoolerData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	GetTime2Buff (buff, &_output_sensorDataValue->coolerTime);
	_output_sensorDataValue->coolerTemperature = buff[g_recvBuffInsertionLocation++] - 40;

	return 1;
}

int32_t GetUsersData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	GetTime2Buff (buff, &_output_sensorDataValue->usersTime);
	_output_sensorDataValue->usersCount = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->oldUsersCount = buff[g_recvBuffInsertionLocation++];

	return 1;
}

int32_t GetHygrometerData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	GetTime2Buff (buff, &_output_sensorDataValue->hygrometerTime);
	_output_sensorDataValue->hygrometerHumidity = buff[g_recvBuffInsertionLocation++];

	return 1;
}

int32_t GetPanicButtonData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	GetTime2Buff (buff, &_output_sensorDataValue->panicButtonTime);
	_output_sensorDataValue->panicButtonIsPushed = buff[g_recvBuffInsertionLocation++];

	return 1;
}

int32_t GetDisabledPersonReservationData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	BYTE	buff2id[4] = {0, };

	GetTime2Buff (buff, &_output_sensorDataValue->disabledPersonReservedTime);

	_output_sensorDataValue->disabledPersonIsReserved = buff[g_recvBuffInsertionLocation++];

	buff2id[0] = buff[g_recvBuffInsertionLocation++];
	buff2id[1] = buff[g_recvBuffInsertionLocation++];
	buff2id[2] = buff[g_recvBuffInsertionLocation++];
	buff2id[3] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->disabledPersonReservedStationId = *(int*)buff2id;

	buff2id[0] = buff[g_recvBuffInsertionLocation++];
	buff2id[1] = buff[g_recvBuffInsertionLocation++];
	buff2id[2] = buff[g_recvBuffInsertionLocation++];
	buff2id[3] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->disabledPersonPhon = *(int*)buff2id;


	return 1;
}

int32_t GetWildDrivingData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	GetTime2Buff (buff, &_output_sensorDataValue->wildDrivingTime);
	_output_sensorDataValue->isWildDriving = buff[g_recvBuffInsertionLocation++];

	return 1;
}

int32_t GetGSensorData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	_output_sensorDataValue->gSensorX[0] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->gSensorX[1] = buff[g_recvBuffInsertionLocation++];

	_output_sensorDataValue->gSensorY[0] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->gSensorY[1] = buff[g_recvBuffInsertionLocation++];

	_output_sensorDataValue->gSensorZ[0] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->gSensorZ[1] = buff[g_recvBuffInsertionLocation++];

	return 1;
}

int32_t GetOBD2Data_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
char	temp[16] = {0, };
	BYTE	buff2int[4] = {0, };

	_output_sensorDataValue->busSpeed = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->absoluteBarometricPressure = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->fuelTankLevelInput = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->engineOilTemperature = buff[g_recvBuffInsertionLocation++] - 40;


	g_recvBuffInsertionLocation++;
	_output_sensorDataValue->busInnerOxygen = 100.0f/128.0f * buff[g_recvBuffInsertionLocation++] - 100;


	buff2int[2] = buff[g_recvBuffInsertionLocation++];
	buff2int[3] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->runTimeToEngineStart = (buff2int[2]<<8) + buff2int[3];//*(int*)buff2int;

	buff2int[2] = buff[g_recvBuffInsertionLocation++];
	buff2int[3] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->engineRPM = /*(*(int*)buff2int)*/(buff2int[2]*256 + buff2int[3])/4.0f;

	return 1;
}

int32_t GetBeaconData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	int i;

	GetTime2Buff(buff, &_output_sensorDataValue->beaconTime);

	for (i = 0; i < 16; i++)
		_output_sensorDataValue->beaconUuid[i] = buff[g_recvBuffInsertionLocation++];

	_output_sensorDataValue->beaconMajor[0] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->beaconMajor[1] = buff[g_recvBuffInsertionLocation++];

	_output_sensorDataValue->beaconMinor[0] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->beaconMinor[1] = buff[g_recvBuffInsertionLocation++];

	return 1;
}

int32_t GetSpeakerData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	BYTE buff2int[4] = {0, };

	GetTime2Buff(buff, &_output_sensorDataValue->speakerTime);

	buff2int[0] = buff[g_recvBuffInsertionLocation++];
	buff2int[1] = buff[g_recvBuffInsertionLocation++];
	buff2int[2] = buff[g_recvBuffInsertionLocation++];
	buff2int[3] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->speakerStationId = *(int*)buff2int;

	return 1;
}

int32_t GetIoData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	GetTime2Buff(buff, &_output_sensorDataValue->ioTime);
	_output_sensorDataValue->ioInput = buff[g_recvBuffInsertionLocation++];

	return 1;
}

int32_t GetImageData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue) {
	int i;
	BYTE buff2int[4] = {0, };

	buff2int[0] = buff[g_recvBuffInsertionLocation++];
	buff2int[1] = buff[g_recvBuffInsertionLocation++];
	buff2int[2] = buff[g_recvBuffInsertionLocation++];
	buff2int[3] = buff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->imageSize = *(int*)buff2int;

	for (i = 0; i < _output_sensorDataValue->imageSize; i++)
		_output_sensorDataValue->imageData[i] = buff[g_recvBuffInsertionLocation++];

	return 1;
}



int32_t GetDataFromRecvBuff (SensorDataValue *_output_sensorDataValue) {
	static int isAwake = 1;BYTE buff2int[4] = {0, };
	g_recvBuffInsertionLocation = 0;

	if ( !isAwake ){
		isAwake = 0;
		return 0;
	}

	memset(_output_sensorDataValue, '\0', sizeof(_output_sensorDataValue));


	_output_sensorDataValue->control_stx[0] = g_recvBuff[g_recvBuffInsertionLocation++];

	_output_sensorDataValue->serialId[0] = g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->serialId[1] = g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->serialId[2] = g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->serialId[3] = g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->serialId[4] = g_recvBuff[g_recvBuffInsertionLocation++];

	_output_sensorDataValue->terminalId[0] = g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->terminalId[1] = g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->terminalId[2] = g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->terminalId[3] = g_recvBuff[g_recvBuffInsertionLocation++];

	_output_sensorDataValue->responseCode[0]= g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->errorCode[0]	= g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->commandCode[0] = g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->seqNo[0]		= g_recvBuff[g_recvBuffInsertionLocation++];

	buff2int[0] = g_recvBuff[g_recvBuffInsertionLocation++];
	buff2int[1] = g_recvBuff[g_recvBuffInsertionLocation++];
	buff2int[2] = g_recvBuff[g_recvBuffInsertionLocation++];
	buff2int[3] = g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->length = *(int*)buff2int;

	GetGpsData_buff2value						(g_recvBuff, _output_sensorDataValue);
	GetThermometerData_buff2value				(g_recvBuff, _output_sensorDataValue);
	GetCoolerData_buff2value					(g_recvBuff, _output_sensorDataValue);
	GetUsersData_buff2value						(g_recvBuff, _output_sensorDataValue);
	GetHygrometerData_buff2value				(g_recvBuff, _output_sensorDataValue);
	GetPanicButtonData_buff2value				(g_recvBuff, _output_sensorDataValue);
	GetDisabledPersonReservationData_buff2value	(g_recvBuff, _output_sensorDataValue);
	GetWildDrivingData_buff2value				(g_recvBuff, _output_sensorDataValue);
	GetGSensorData_buff2value					(g_recvBuff, _output_sensorDataValue);
	GetOBD2Data_buff2value						(g_recvBuff, _output_sensorDataValue);
	GetBeaconData_buff2value					(g_recvBuff, _output_sensorDataValue);
	GetSpeakerData_buff2value					(g_recvBuff, _output_sensorDataValue);
	GetIoData_buff2value						(g_recvBuff, _output_sensorDataValue);
	GetImageData_buff2value						(g_recvBuff, _output_sensorDataValue);

	_output_sensorDataValue->errorCheck[0]	= g_recvBuff[g_recvBuffInsertionLocation++];
	_output_sensorDataValue->control_etx[0]	= g_recvBuff[g_recvBuffInsertionLocation++];

	return g_recvBuffInsertionLocation;
}


void PrintSensorDataValue (SensorDataValue *sensorDataValue) {

	int i;

	printf("control_stx:: %x\n", *sensorDataValue->control_stx);
	printf("\n");

	printf("serialId:: %c%c%c%c%c\n", sensorDataValue->serialId[0], sensorDataValue->serialId[1], sensorDataValue->serialId[2], sensorDataValue->serialId[3], sensorDataValue->serialId[4]);
	printf("terminalId:: %c%c%c%c\n", sensorDataValue->terminalId[0], sensorDataValue->terminalId[1], sensorDataValue->terminalId[2], sensorDataValue->terminalId[3]);
	printf("responseCode:: %x\n", *sensorDataValue->responseCode);
	printf("errorCode:: %x\n", *sensorDataValue->errorCode);
	printf("commandCode:: %x\n", *sensorDataValue->commandCode);
	printf("seqNo:: %x\n", *sensorDataValue->seqNo);
	printf("\n");

	printf("length:: %d\n", sensorDataValue->length);
	printf("\n");

	printf("gpsTime:: %d시 %d분 %d초\n", sensorDataValue->gpsTime[0], sensorDataValue->gpsTime[1], sensorDataValue->gpsTime[2]);
	printf("gpsX:: %.3f\n", sensorDataValue->gpsX);
	printf("gpsY:: %.3f\n", sensorDataValue->gpsY);
	printf("gpsSatelliteCount:: %d\n", sensorDataValue->gpsSatelliteCount);
	printf("\n");

	printf("thermometerTime:: %.3f\n", sensorDataValue->thermometerTime);
	printf("thermometerTemperature:: %d\n", sensorDataValue->thermometerTemperature);
	printf("\n");

	printf("coolerTime:: %.3f\n", sensorDataValue->coolerTime);
	printf("coolerTemperature:: %d\n", sensorDataValue->coolerTemperature);
	printf("\n");

	printf("usersTime:: %.3f\n", sensorDataValue->usersTime);
	printf("usersCount:: %d\n", sensorDataValue->usersCount);
	printf("oldUsersCount:: %d\n", sensorDataValue->oldUsersCount);
	printf("\n");

	printf("hygrometerTime:: %.3f\n", sensorDataValue->hygrometerTime);
	printf("hygrometerHumidity:: %d\n", sensorDataValue->hygrometerHumidity);
	printf("\n");

	printf("panicButtonTime:: %.3f\n", sensorDataValue->panicButtonTime);
	printf("panicButtonIsPushed:: %d\n", sensorDataValue->panicButtonIsPushed);
	printf("\n");

	printf("disabledPersonReservedTime:: %.3f\n", sensorDataValue->disabledPersonReservedTime);
	printf("disabledPersonIsReserved:: %d\n", sensorDataValue->disabledPersonIsReserved);
	printf("disabledPersonReservedStationId:: %d\n", sensorDataValue->disabledPersonReservedStationId);
	printf("disabledPersonPhon:: %d\n", sensorDataValue->disabledPersonPhon);
	printf("\n");

	printf("wildDrivingTime:: %.3f\n", sensorDataValue->wildDrivingTime);
	printf("isWildDriving:: %d\n", sensorDataValue->isWildDriving);
	printf("\n");

	printf("gSensorX:: %d, %d\n", sensorDataValue->gSensorX[0], sensorDataValue->gSensorX[1]);
	printf("gSensorY:: %d, %d\n", sensorDataValue->gSensorY[0], sensorDataValue->gSensorY[1]);
	printf("gSensorZ:: %d, %d\n", sensorDataValue->gSensorZ[0], sensorDataValue->gSensorZ[1]);
	printf("\n");

	printf("busSpeed:: %d\n", sensorDataValue->busSpeed);
	printf("absoluteBarometricPressure:: %d\n", sensorDataValue->absoluteBarometricPressure);
	printf("fuelTankLevelInput:: %d\n", sensorDataValue->fuelTankLevelInput);
	printf("engineOilTemperature:: %d\n", sensorDataValue->engineOilTemperature);
	printf("busInnerOxygen:: %.3f\n", sensorDataValue->busInnerOxygen);
	printf("runTimeToEngineStart:: %d\n", sensorDataValue->runTimeToEngineStart);
	printf("engineRPM:: %.3f\n", sensorDataValue->engineRPM);
	printf("\n");

	printf("beaconTime:: %.3f\n", sensorDataValue->beaconTime);
	printf("beaconUuid:: ");
	for (i = 0; i < 16; i++)
		printf("%c", sensorDataValue->beaconUuid[i]);
	printf("\n");
	printf("beaconMajor:: %c, %c\n", sensorDataValue->beaconMajor[0], sensorDataValue->beaconMajor[1]);
	printf("beaconMinor:: %c, %c\n", sensorDataValue->beaconMinor[0], sensorDataValue->beaconMinor[1]);
	printf("\n");

	printf("speakerTime:: %.3f\n", sensorDataValue->speakerTime);
	printf("speakerStationId:: %d\n", sensorDataValue->speakerStationId);
	printf("\n");

	printf("ioTime:: %.3f\n", sensorDataValue->ioTime);
	printf("ioInput:: %x\n", sensorDataValue->ioInput);
	printf("\n");

	printf("imageSize:: %d\n", sensorDataValue->imageSize);
	printf("imageData:: skip...\n");
	printf("\n");

	printf("errorCheck:: %x\n", *sensorDataValue->errorCheck);
	printf("control_etx:: %x\n", *sensorDataValue->control_etx);
	printf("\n");
}
