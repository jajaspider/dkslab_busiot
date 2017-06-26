#pragma warning(disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//#include <WinSock2.h>
#include <netinet/in.h>

#include "utilForPacket.h"
#include "codes.h"
#include "paths.h"

#define _100_DIV_128_ 0.78125f


void SensorDataValueCpoy (SensorDataValue *dst, SensorDataValue *src) {
								dst->control_stx        = src->control_stx;

								memcpy((char*)dst->serialId,     (char*)src->serialId, 5);
								memcpy((char*)dst->terminalId,     (char*)src->terminalId, 4);
								dst->responseCode          = src->responseCode;
								dst->errorCode           = src->errorCode;
								dst->commandCode          = src->commandCode;
								dst->seqNo            = src->seqNo;

								dst->length          = src->length;





								dst->gpsTime           = src->gpsTime;
								dst->gpsX            = src->gpsX;
								dst->gpsY            = src->gpsY;
								dst->gpsCnt            = src->gpsCnt;
								dst->gpsSpeed           = src->gpsSpeed;
								dst->gpsHeading           = src->gpsHeading;
								memcpy((char*)dst->gpsReserved,     (char*)src->gpsReserved, 10);

//OBD-II
								dst->obdTime           = src->obdTime;
								dst->busSpeed           = src->busSpeed;
								dst->busInnerOxygen[0]         = src->busInnerOxygen[0];
								dst->busInnerOxygen[1]         = src->busInnerOxygen[1];
								dst->runTimeToEngineStart      = src->runTimeToEngineStart;
								dst->absoluteBarometricPressure       = src->absoluteBarometricPressure;
								dst->fuelTankLevelInput         = src->fuelTankLevelInput;
								dst->engineRPM           = src->engineRPM;
								dst->engineOilTemperature        = src->engineOilTemperature;
								dst->engineCoolantTemperature       = src->engineCoolantTemperature;
								memcpy((char*)dst->obdReserved,     (char*)src->obdReserved, 10);
//OBD-II end

								dst->usrCntTime           = src->usrCntTime;
								dst->usrCnt            = src->usrCnt;
								dst->oldUsrCnt           = src->oldUsrCnt;
								memcpy((char*)dst->usrCntReserved,    (char*)src->usrCntReserved, 10);

								dst->wildDrivingTime         = src->wildDrivingTime;
								dst->isWildDriving          = src->isWildDriving;
								dst->gSensorX[0]          = src->gSensorX[0];
								dst->gSensorX[1]          = src->gSensorX[1];
								dst->gSensorY[0]          = src->gSensorY[0];
								dst->gSensorY[1]          = src->gSensorY[1];
								dst->gSensorZ[0]          = src->gSensorZ[0];
								dst->gSensorZ[1]          = src->gSensorZ[1];
								memcpy((char*)dst->wildDrivingReserved,   (char*)src->wildDrivingReserved, 10);

								dst->beaconTime           = src->beaconTime;
								memcpy((char*)dst->beaconUuid,     (char*)src->beaconUuid, 16);
								memcpy((char*)dst->beaconMajor,     (char*)src->beaconMajor, 2);
								memcpy((char*)dst->beaconMinor,     (char*)src->beaconMinor, 2);
								memcpy((char*)dst->beaconReserved,    (char*)src->beaconReserved, 10);

								dst->thermometerTime       = src->thermometerTime;
								dst->thermometerTemperature        = src->thermometerTemperature;
								dst->hygrometerTime          = src->hygrometerTime;
								dst->hygrometerHumidity         = src->hygrometerHumidity;
								memcpy((char*)dst->hygrothermalReserved,  (char*)src->hygrothermalReserved, 10);

								dst->panicButtonTime         = src->panicButtonTime;
								dst->panicButtonIsPushed        = src->panicButtonIsPushed;
								memcpy((char*)dst->panicButtonReserved,   (char*)src->panicButtonReserved, 10);

								dst->imageTime           = src->imageTime;
								memcpy((char*)dst->imageName,     (char*)src->imageName, 30);
								memcpy((char*)dst->imageReserved,    (char*)src->imageReserved, 10);

								dst->speakerTime          = src->speakerTime;
								memcpy((char*)dst->speakerStationId,   (char*)src->speakerStationId, 4);
								memcpy((char*)dst->speakerReserved,    (char*)src->speakerReserved, 10);

								dst->ioTime          = src->ioTime;
								dst->ioInput[0]           = src->ioInput[0];
								dst->ioInput[1]           = src->ioInput[1];
								memcpy((char*)dst->ioReserved,     (char*)src->ioReserved, 10);

								dst->disabledPersonResvTime      = src->disabledPersonResvTime;
								memcpy((char*)dst->busNo,      (char*)src->busNo, 10);
								memcpy((char*)dst->busLicenseNo,    (char*)src->busLicenseNo, 12);
								dst->resvUsrGpsX        = src->resvUsrGpsX;
								dst->resvUsrGpsY        = src->resvUsrGpsY;
								dst->isResvSuccess        = src->isResvSuccess;
								memcpy((char*)dst->resvBusStopId,    (char*)src->resvBusStopId, 10);
								memcpy((char*)dst->resvPhone,     (char*)src->resvPhone, 12);
								memcpy((char*)dst->disabledPersonResvReserved, (char*)src->disabledPersonResvReserved, 10);

								dst->errorCheck         = src->errorCheck;
								dst->control_etx        = src->control_etx;
}

void initReservedValue (BYTE *reserved, int length) {
								memset(reserved, '\0', length);
}










//sensor2value
int32_t MoveData_sensor2value (SensorDataValue *_output_sensorDataValue, BYTE *serialId, BYTE *terminalId) {
								memset(_output_sensorDataValue, '\0', sizeof(SensorDataValue));

								_output_sensorDataValue->control_stx = CONTROL_STX;

								memcpy((char*)_output_sensorDataValue->serialId, serialId, 5);
								memcpy((char*)_output_sensorDataValue->terminalId, terminalId, 4);
								_output_sensorDataValue->responseCode = 0x00;
								_output_sensorDataValue->errorCode  = 0x00;
								_output_sensorDataValue->commandCode = 0x00;
								_output_sensorDataValue->seqNo   = 0x00;

								_output_sensorDataValue->length   = 0x00;

								MoveGpsData_sensor2value       (_output_sensorDataValue);
								MoveOBD2Data_sensor2value       (_output_sensorDataValue);
								MoveUsrCntData_sensor2value       (_output_sensorDataValue);
								MoveWildDrivingData_sensor2value     (_output_sensorDataValue);
								MoveBeaconData_sensor2value       (_output_sensorDataValue);
								MoveHygrothermalData_sensor2value     (_output_sensorDataValue);
								MovePanicButtonData_sensor2value     (_output_sensorDataValue);
								MoveImageData_sensor2value       (_output_sensorDataValue);
								MoveSpeakerData_sensor2value      (_output_sensorDataValue);
								MoveIoData_sensor2value        (_output_sensorDataValue);
								MoveDisabledPersonResvData_sensor2value (_output_sensorDataValue);

								_output_sensorDataValue->errorCheck = ERROR_CHECK_STX;
								_output_sensorDataValue->control_etx = CONTROL_ETX;

								return 1;
}

int32_t MoveGpsData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								_output_sensorDataValue->gpsTime = (int32_t)time(NULL);

								_output_sensorDataValue->gpsX = 127.123456f;
								_output_sensorDataValue->gpsY = 127.456789f;

								_output_sensorDataValue->gpsCnt  = 16;
								_output_sensorDataValue->gpsSpeed = 40.5211f;
								_output_sensorDataValue->gpsHeading = 120;

								initReservedValue(_output_sensorDataValue->gpsReserved, 10);

								return 1;
}

int32_t MoveOBD2Data_sensor2value (SensorDataValue *_output_sensorDataValue) {
								_output_sensorDataValue->obdTime = (int32_t)time(NULL);

								_output_sensorDataValue->busSpeed = 40;

								_output_sensorDataValue->busInnerOxygen[0] = 0xFF * 0.005f;
								_output_sensorDataValue->busInnerOxygen[1] = 0xFF * _100_DIV_128_ - 100;

								_output_sensorDataValue->runTimeToEngineStart  = 0xFFFF;

								_output_sensorDataValue->absoluteBarometricPressure = 101;

								_output_sensorDataValue->fuelTankLevelInput   = 50;

								_output_sensorDataValue->engineRPM     = 16108.5f;

								_output_sensorDataValue->engineOilTemperature  = 98;

								_output_sensorDataValue->engineCoolantTemperature = 98;

								initReservedValue(_output_sensorDataValue->obdReserved, 10);

								return 1;
}

int32_t MoveUsrCntData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								_output_sensorDataValue->usrCntTime = (int32_t)time(NULL);

								_output_sensorDataValue->usrCnt  = 50;

								_output_sensorDataValue->oldUsrCnt = 1;

								initReservedValue(_output_sensorDataValue->usrCntReserved, 10);

								return 1;
}

int32_t MoveWildDrivingData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								_output_sensorDataValue->wildDrivingTime = (int32_t)time(NULL);

								_output_sensorDataValue->isWildDriving = 0;

								_output_sensorDataValue->gSensorX[0] = 0x00;
								_output_sensorDataValue->gSensorX[1] = 0x00;

								_output_sensorDataValue->gSensorY[0] = 0x00;
								_output_sensorDataValue->gSensorY[1] = 0x00;

								_output_sensorDataValue->gSensorZ[0] = 0x00;
								_output_sensorDataValue->gSensorZ[1] = 0x00;

								initReservedValue(_output_sensorDataValue->wildDrivingReserved, 10);

								return 1;
}

int32_t MoveBeaconData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								int i;

								_output_sensorDataValue->beaconTime = (int32_t)time(NULL);

								for (i = 0; i < 16; i++)
																_output_sensorDataValue->beaconUuid[i] = 'A';

								_output_sensorDataValue->beaconMajor[0] = 'B';
								_output_sensorDataValue->beaconMajor[1] = 'B';

								_output_sensorDataValue->beaconMinor[0] = 'C';
								_output_sensorDataValue->beaconMinor[1] = 'C';

								initReservedValue(_output_sensorDataValue->beaconReserved, 10);

								return 1;
}

int32_t MoveHygrothermalData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								_output_sensorDataValue->thermometerTime = (int32_t)time(NULL);
								_output_sensorDataValue->thermometerTemperature = 20;


								_output_sensorDataValue->hygrometerTime = (int32_t)time(NULL);
								_output_sensorDataValue->hygrometerHumidity = 100;

								initReservedValue(_output_sensorDataValue->hygrothermalReserved, 10);

								return 1;
}

int32_t MovePanicButtonData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								_output_sensorDataValue->panicButtonTime = (int32_t)time(NULL);
								_output_sensorDataValue->panicButtonIsPushed = 0;
								initReservedValue(_output_sensorDataValue->panicButtonReserved, 10);

								return 1;
}

int32_t MoveImageData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								struct tm *timeInfo;
								BYTE buff[30];
								memset(buff, '\0', 30);



								_output_sensorDataValue->imageTime = (int32_t)time(NULL);
								timeInfo = localtime((time_t*)&_output_sensorDataValue->imageTime);

								sprintf(
																(char*)buff,
																"%04d-%02d-%02d-%02d-%02d-%02d-%s.jpg",
																timeInfo->tm_year + 1900,
																timeInfo->tm_mon + 1,
																timeInfo->tm_mday,
																timeInfo->tm_hour,
																timeInfo->tm_min,
																timeInfo->tm_sec,
																"F0"
																);

								memcpy((char*)_output_sensorDataValue->imageName, (char*)buff, 30);

								initReservedValue(_output_sensorDataValue->imageReserved, 10);

								return 1;
}

int32_t MoveSpeakerData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								_output_sensorDataValue->speakerTime = (int32_t)time(NULL);

								_output_sensorDataValue->speakerStationId[0] = 0x05;
								_output_sensorDataValue->speakerStationId[1] = 0x00;
								_output_sensorDataValue->speakerStationId[2] = 0x60;
								_output_sensorDataValue->speakerStationId[3] = 0x2F;

								initReservedValue(_output_sensorDataValue->speakerReserved, 10);

								return 1;
}

int32_t MoveIoData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								_output_sensorDataValue->ioTime = (int32_t)time(NULL);

								_output_sensorDataValue->ioInput[0] = 0x00;
								_output_sensorDataValue->ioInput[1] = 0x00;

								initReservedValue(_output_sensorDataValue->ioReserved, 10);

								return 1;
}

int32_t MoveDisabledPersonResvData_sensor2value (SensorDataValue *_output_sensorDataValue) {
								_output_sensorDataValue->disabledPersonResvTime = (int32_t)time(NULL);

								memset(_output_sensorDataValue->busNo,   '\0', 10);
								memset(_output_sensorDataValue->busLicenseNo, '\0', 12);

								_output_sensorDataValue->resvUsrGpsX = 0x00;
								_output_sensorDataValue->resvUsrGpsY = 0x00;
								_output_sensorDataValue->isResvSuccess = (int32_t)NULL;


								memset(_output_sensorDataValue->resvBusStopId, '\0', 12);
								memset(_output_sensorDataValue->resvPhone,  '\0', 10);

								initReservedValue(_output_sensorDataValue->disabledPersonResvReserved, 10);

								return 1;
}
//sensor2value end

















//value2packet
int32_t MoveData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;

								memset(_output_sensorDataPacket, '\0', sizeof(SensorDataPacket));


								_output_sensorDataPacket->control_stx[0] = sensorDataValue->control_stx;
								movedDataSize++;
								memcpy((char*)_output_sensorDataPacket->serialId,      (char*)sensorDataValue->serialId,  5);
								movedDataSize += 5;
								memcpy((char*)_output_sensorDataPacket->terminalId,     (char*)sensorDataValue->terminalId, 4);
								movedDataSize += 4;

								_output_sensorDataPacket->responseCode[0] = sensorDataValue->responseCode;
								movedDataSize++;
								_output_sensorDataPacket->commandCode[0] = sensorDataValue->commandCode;
								movedDataSize++;
								_output_sensorDataPacket->seqNo[0]   = sensorDataValue->seqNo;
								movedDataSize++;

								//At last
								//_output_sensorDataPacket->length
								movedDataSize++;
								movedDataSize++;


								movedDataSize += MoveGpsData_value2packet     (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MoveOBD2Data_value2packet     (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MoveUsrCntData_value2packet    (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MoveWildDrivingData_value2packet   (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MoveBeaconData_value2packet    (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MoveHygrothermalData_value2packet   (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MovePanicButtonData_value2packet   (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MoveImageData_value2packet     (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MoveSpeakerData_value2packet    (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MoveIoData_value2packet     (sensorDataValue, _output_sensorDataPacket);
								movedDataSize += MoveDisabledPersonResvData_value2packet (sensorDataValue, _output_sensorDataPacket);

								_output_sensorDataPacket->errorCheck[0]  = sensorDataValue->errorCheck;
								movedDataSize++;
								_output_sensorDataPacket->control_etx[0] = sensorDataValue->control_etx;
								movedDataSize++;





								movedDataSize++;
								_output_sensorDataPacket->length = (int16_t)movedDataSize;
								_output_sensorDataPacket->length = htons(_output_sensorDataPacket->length);

								return movedDataSize;
}

int32_t MoveGpsData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->gpsTime = sensorDataValue->gpsTime;
								_output_sensorDataPacket->gpsTime = htonl(_output_sensorDataPacket->gpsTime);

								_output_sensorDataPacket->gpsX  = (int32_t)(sensorDataValue->gpsX * 1000000);
								_output_sensorDataPacket->gpsX = htonl(_output_sensorDataPacket->gpsX);
								_output_sensorDataPacket->gpsY  = (int32_t)(sensorDataValue->gpsY * 1000000);
								_output_sensorDataPacket->gpsY = htonl(_output_sensorDataPacket->gpsY);

								_output_sensorDataPacket->gpsCnt[0] = sensorDataValue->gpsCnt;

								_output_sensorDataPacket->gpsSpeed = sensorDataValue->gpsSpeed;
								_output_sensorDataPacket->gpsSpeed = (float)htonl(_output_sensorDataPacket->gpsSpeed);

								sprintf((char*)_output_sensorDataPacket->gpsHeading,     "%03d", sensorDataValue->gpsHeading);

								memcpy((char*)_output_sensorDataPacket->gpsReserved,     (char*)_output_sensorDataPacket->gpsReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->gpsTime)
																								+ sizeof (_output_sensorDataPacket->gpsX)
																								+ sizeof (_output_sensorDataPacket->gpsY)
																								+ sizeof (_output_sensorDataPacket->gpsCnt)
																								+ sizeof (_output_sensorDataPacket->gpsSpeed)
																								+ sizeof (_output_sensorDataPacket->gpsHeading)
																								+ sizeof (_output_sensorDataPacket->gpsReserved);
								return movedDataSize;
}

int32_t MoveOBD2Data_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->obdTime = sensorDataValue->obdTime;
								_output_sensorDataPacket->obdTime = htonl(_output_sensorDataPacket->obdTime);

								sprintf((char*)_output_sensorDataPacket->busSpeed,      "%03d", sensorDataValue->busSpeed);

								_output_sensorDataPacket->busInnerOxygen[0]    = (BYTE)(sensorDataValue->busInnerOxygen[0] * 200);
								_output_sensorDataPacket->busInnerOxygen[1]    = (BYTE)((sensorDataValue->busInnerOxygen[1] + 100) * 1.28f);

								_output_sensorDataPacket->runTimeToEngineStart[1]  = ((BYTE*)&sensorDataValue->runTimeToEngineStart)[0];
								_output_sensorDataPacket->runTimeToEngineStart[0]  = ((BYTE*)&sensorDataValue->runTimeToEngineStart)[1];

								sprintf((char*)_output_sensorDataPacket->absoluteBarometricPressure, "%03d", sensorDataValue->absoluteBarometricPressure);
								sprintf((char*)_output_sensorDataPacket->fuelTankLevelInput,   "%03d", sensorDataValue->fuelTankLevelInput);

								_output_sensorDataPacket->engineRPM[0]     = (BYTE)(sensorDataValue->engineRPM * 4 * DIV256);
								_output_sensorDataPacket->engineRPM[1]     = (BYTE)(sensorDataValue->engineRPM * 4 - _output_sensorDataPacket->engineRPM[0] * 256);

								_output_sensorDataPacket->engineOilTemperature[0]  = sensorDataValue->engineOilTemperature + 40;
								_output_sensorDataPacket->engineCoolantTemperature[0] = sensorDataValue->engineCoolantTemperature + 40;

								memcpy((char*)_output_sensorDataPacket->obdReserved,     (char*)_output_sensorDataPacket->obdReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->obdTime)
																								+ sizeof (_output_sensorDataPacket->busSpeed)
																								+ sizeof (_output_sensorDataPacket->busInnerOxygen)
																								+ sizeof (_output_sensorDataPacket->runTimeToEngineStart)
																								+ sizeof (_output_sensorDataPacket->absoluteBarometricPressure)
																								+ sizeof (_output_sensorDataPacket->fuelTankLevelInput)
																								+ sizeof (_output_sensorDataPacket->engineRPM)
																								+ sizeof (_output_sensorDataPacket->engineOilTemperature)
																								+ sizeof (_output_sensorDataPacket->engineCoolantTemperature)
																								+ sizeof (_output_sensorDataPacket->obdReserved);
								return movedDataSize;
}

int32_t MoveUsrCntData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->usrCntTime     = sensorDataValue->usrCntTime;
								_output_sensorDataPacket->usrCntTime = htonl(_output_sensorDataPacket->usrCntTime);
								sprintf((char*)_output_sensorDataPacket->usrCnt,     "%03d", sensorDataValue->usrCnt);
								sprintf((char*)_output_sensorDataPacket->oldUsrCnt,     "%03d", sensorDataValue->oldUsrCnt);

								memcpy((char*)_output_sensorDataPacket->usrCntReserved,    (char*)_output_sensorDataPacket->usrCntReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->usrCntTime)
																								+ sizeof (_output_sensorDataPacket->usrCnt)
																								+ sizeof (_output_sensorDataPacket->oldUsrCnt)
																								+ sizeof (_output_sensorDataPacket->usrCntReserved);
								return movedDataSize;
}

int32_t MoveWildDrivingData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->wildDrivingTime    = sensorDataValue->wildDrivingTime;
								_output_sensorDataPacket->wildDrivingTime = htonl(_output_sensorDataPacket->wildDrivingTime);
								_output_sensorDataPacket->isWildDriving[0]    = sensorDataValue->isWildDriving;

								_output_sensorDataPacket->gSensorX[0]     = sensorDataValue->gSensorX[0];
								_output_sensorDataPacket->gSensorX[1]     = sensorDataValue->gSensorX[1];

								_output_sensorDataPacket->gSensorY[0]     = sensorDataValue->gSensorY[0];
								_output_sensorDataPacket->gSensorY[1]     = sensorDataValue->gSensorY[1];

								_output_sensorDataPacket->gSensorZ[0]     = sensorDataValue->gSensorZ[0];
								_output_sensorDataPacket->gSensorZ[1]     = sensorDataValue->gSensorZ[1];

								memcpy((char*)_output_sensorDataPacket->wildDrivingReserved,   (char*)_output_sensorDataPacket->wildDrivingReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->wildDrivingTime)
																								+ sizeof (_output_sensorDataPacket->isWildDriving)
																								+ sizeof (_output_sensorDataPacket->gSensorX)
																								+ sizeof (_output_sensorDataPacket->gSensorY)
																								+ sizeof (_output_sensorDataPacket->gSensorZ)
																								+ sizeof (_output_sensorDataPacket->wildDrivingReserved);
								return movedDataSize;
}

int32_t MoveBeaconData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->beaconTime     = sensorDataValue->beaconTime;
								_output_sensorDataPacket->beaconTime = htonl(_output_sensorDataPacket->beaconTime);

								memcpy((char*)_output_sensorDataPacket->beaconUuid,      (char*)sensorDataValue->beaconUuid,  16);
								memcpy((char*)_output_sensorDataPacket->beaconMajor,     (char*)sensorDataValue->beaconMajor,  2);
								memcpy((char*)_output_sensorDataPacket->beaconMinor,     (char*)sensorDataValue->beaconMinor,  2);

								memcpy((char*)_output_sensorDataPacket->beaconReserved,     (char*)sensorDataValue->beaconReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->beaconTime)
																								+ sizeof (_output_sensorDataPacket->beaconUuid)
																								+ sizeof (_output_sensorDataPacket->beaconMajor)
																								+ sizeof (_output_sensorDataPacket->beaconMinor)
																								+ sizeof (_output_sensorDataPacket->beaconReserved);
								return movedDataSize;
}

int32_t MoveHygrothermalData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->thermometerTime    = sensorDataValue->thermometerTime;
								_output_sensorDataPacket->thermometerTime = htonl(_output_sensorDataPacket->thermometerTime);
								_output_sensorDataPacket->thermometerTemperature[0]  = sensorDataValue->thermometerTemperature + 40;

								_output_sensorDataPacket->hygrometerTime    = sensorDataValue->hygrometerTime;
								_output_sensorDataPacket->hygrometerTime = htonl(_output_sensorDataPacket->hygrometerTime);
								sprintf((char*)_output_sensorDataPacket->hygrometerHumidity,   "%03d", sensorDataValue->hygrometerHumidity);

								memcpy((char*)_output_sensorDataPacket->hygrothermalReserved,   (char*)_output_sensorDataPacket->hygrothermalReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->thermometerTime)
																								+ sizeof (_output_sensorDataPacket->thermometerTemperature)
																								+ sizeof (_output_sensorDataPacket->hygrometerTime)
																								+ sizeof (_output_sensorDataPacket->hygrometerHumidity)
																								+ sizeof (_output_sensorDataPacket->hygrothermalReserved);
								return movedDataSize;
}

int32_t MovePanicButtonData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->panicButtonTime    = sensorDataValue->panicButtonTime;
								_output_sensorDataPacket->panicButtonTime = htonl(_output_sensorDataPacket->panicButtonTime);

								_output_sensorDataPacket->panicButtonIsPushed[0]  = sensorDataValue->panicButtonIsPushed;
								memcpy((char*)_output_sensorDataPacket->panicButtonReserved,   (char*)_output_sensorDataPacket->panicButtonReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->panicButtonTime)
																								+ sizeof (_output_sensorDataPacket->panicButtonIsPushed)
																								+ sizeof (_output_sensorDataPacket->panicButtonReserved);
								return movedDataSize;
}

int32_t MoveImageData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->imageTime      = sensorDataValue->imageTime;
								_output_sensorDataPacket->imageTime = htonl(_output_sensorDataPacket->imageTime);

								memcpy((char*)_output_sensorDataPacket->imageName,      (char*)sensorDataValue->imageName, 30);
								memcpy((char*)_output_sensorDataPacket->imageReserved,     (char*)sensorDataValue->imageReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->imageTime)
																								+ sizeof (_output_sensorDataPacket->imageName)
																								+ sizeof (_output_sensorDataPacket->imageReserved);
								return movedDataSize;
}

int32_t MoveSpeakerData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->speakerTime     = sensorDataValue->speakerTime;
								_output_sensorDataPacket->speakerTime = htonl(_output_sensorDataPacket->speakerTime);

								memcpy((char*)_output_sensorDataPacket->speakerStationId,    (char*)sensorDataValue->speakerStationId, 4);
								memcpy((char*)_output_sensorDataPacket->speakerReserved,    (char*)sensorDataValue->speakerReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->speakerTime)
																								+ sizeof (_output_sensorDataPacket->speakerStationId)
																								+ sizeof (_output_sensorDataPacket->speakerReserved);
								return movedDataSize;
}

int32_t MoveIoData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->ioTime      = sensorDataValue->ioTime;
								_output_sensorDataPacket->ioTime = htonl(_output_sensorDataPacket->ioTime);

								memcpy((char*)_output_sensorDataPacket->ioInput,      (char*)sensorDataValue->ioInput, 2);
								memcpy((char*)_output_sensorDataPacket->ioReserved,     (char*)sensorDataValue->ioReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->ioTime)
																								+ sizeof (_output_sensorDataPacket->ioInput)
																								+ sizeof (_output_sensorDataPacket->ioReserved);
								return movedDataSize;
}

int32_t MoveDisabledPersonResvData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket) {
								int32_t movedDataSize = 0;


								_output_sensorDataPacket->disabledPersonResvTime  = sensorDataValue->disabledPersonResvTime;
								_output_sensorDataPacket->disabledPersonResvTime  = htonl(_output_sensorDataPacket->disabledPersonResvTime);

								memcpy((char*)_output_sensorDataPacket->busNo,       (char*)sensorDataValue->busNo,   10);
								memcpy((char*)_output_sensorDataPacket->busLicenseNo,     (char*)sensorDataValue->busLicenseNo, 12);

								_output_sensorDataPacket->resvUsrGpsX     = (int32_t)(sensorDataValue->resvUsrGpsX * 1000000);
								_output_sensorDataPacket->resvUsrGpsX     = htonl(_output_sensorDataPacket->resvUsrGpsX);
								_output_sensorDataPacket->resvUsrGpsY     = (int32_t)(sensorDataValue->resvUsrGpsY * 1000000);
								_output_sensorDataPacket->resvUsrGpsY     = htonl(_output_sensorDataPacket->resvUsrGpsY);
								_output_sensorDataPacket->isResvSuccess[0]    = sensorDataValue->isResvSuccess;

								memcpy((char*)_output_sensorDataPacket->resvBusStopId,     (char*)sensorDataValue->resvBusStopId, 10);
								memcpy((char*)_output_sensorDataPacket->resvPhone,      (char*)sensorDataValue->resvPhone, 12);

								memcpy((char*)_output_sensorDataPacket->disabledPersonResvReserved, (char*)sensorDataValue->disabledPersonResvReserved, 10);


								movedDataSize = sizeof (_output_sensorDataPacket->disabledPersonResvTime)
																								+ sizeof (_output_sensorDataPacket->busNo)
																								+ sizeof (_output_sensorDataPacket->busLicenseNo)
																								+ sizeof (_output_sensorDataPacket->resvUsrGpsX)
																								+ sizeof (_output_sensorDataPacket->resvUsrGpsY)
																								+ sizeof (_output_sensorDataPacket->isResvSuccess)
																								+ sizeof (_output_sensorDataPacket->resvBusStopId)
																								+ sizeof (_output_sensorDataPacket->resvPhone)
																								+ sizeof (_output_sensorDataPacket->disabledPersonResvReserved);
								return movedDataSize;
}
//value2packet end












//packet2buff
int32_t MoveData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff) {
								int32_t insertionLocation = 0;
								int32_t movedDataSize = 0;
								memset(_output_buff, '\0', SEND_BUFF_MAX_LENGTH);


								MoveData_byte2buff (sensorDataPacket->control_stx, 1, _output_buff, &insertionLocation);
								movedDataSize++;
								MoveData_byte2buff (sensorDataPacket->serialId,  5, _output_buff, &insertionLocation);
								movedDataSize += 5;
								MoveData_byte2buff (sensorDataPacket->terminalId, 4, _output_buff, &insertionLocation);
								movedDataSize += 4;

								MoveData_byte2buff (sensorDataPacket->responseCode, 1, _output_buff, &insertionLocation);
								movedDataSize++;
								MoveData_byte2buff (sensorDataPacket->errorCode, 1, _output_buff, &insertionLocation);
								movedDataSize++;
								MoveData_byte2buff (sensorDataPacket->commandCode, 1, _output_buff, &insertionLocation);
								movedDataSize++;
								MoveData_byte2buff (sensorDataPacket->seqNo,  1, _output_buff, &insertionLocation);
								movedDataSize++;

								MoveData_byte2buff ((BYTE*)&sensorDataPacket->length,  2, _output_buff, &insertionLocation);
								movedDataSize++;
								movedDataSize++;

								movedDataSize += MoveGpsData_packet2buff    (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MoveOBD2Data_packet2buff    (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MoveUsrCntData_packet2buff    (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MoveWildDrivingData_packet2buff  (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MoveBeaconData_packet2buff    (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MoveHygrothermalData_packet2buff  (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MovePanicButtonData_packet2buff  (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MoveImageData_packet2buff    (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MoveSpeakerData_packet2buff   (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MoveIoData_packet2buff     (sensorDataPacket, _output_buff, &insertionLocation);
								movedDataSize += MoveDisabledPersonResvData_packet2buff (sensorDataPacket, _output_buff, &insertionLocation);

								MoveData_byte2buff (sensorDataPacket->errorCheck, 1, _output_buff, &insertionLocation);
								movedDataSize++;
								MoveData_byte2buff (sensorDataPacket->control_etx, 1, _output_buff, &insertionLocation);
								movedDataSize++;


								return movedDataSize;
}


int32_t MoveData_byte2buff (BYTE *data, int32_t dataLength, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t i;

								if(*insertionLocation + dataLength > SEND_BUFF_MAX_LENGTH)
																return 0;

								for (i = 0; i < dataLength; i++)
																_output_buff[(*insertionLocation)++] = data[i];


								return dataLength;
}

int32_t MoveGpsData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->gpsTime,      4, _output_buff, insertionLocation);
								MoveData_byte2buff ((BYTE*)&sensorDataPacket->gpsX,       4, _output_buff, insertionLocation);
								MoveData_byte2buff ((BYTE*)&sensorDataPacket->gpsY,       4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->gpsCnt,        1, _output_buff, insertionLocation);
								MoveData_byte2buff ((BYTE*)&sensorDataPacket->gpsSpeed,      4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->gpsHeading,       3, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->gpsReserved,       10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MoveOBD2Data_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->obdTime,      4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->busSpeed,        3, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->busInnerOxygen,      2, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->runTimeToEngineStart,     2, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->absoluteBarometricPressure,   3, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->fuelTankLevelInput,     3, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->engineRPM,       2, _output_buff, insertionLocation);
								MoveData_byte2buff ((BYTE*)sensorDataPacket->engineOilTemperature,   1, _output_buff, insertionLocation);
								MoveData_byte2buff ((BYTE*)sensorDataPacket->engineCoolantTemperature,  1, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->obdReserved,       10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MoveUsrCntData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->usrCntTime,     4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->usrCnt,        3, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->oldUsrCnt,       3, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->usrCntReserved,      10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MoveWildDrivingData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->wildDrivingTime,    4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->isWildDriving,      1, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->gSensorX,        2, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->gSensorY,        2, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->gSensorZ,        2, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->wildDrivingReserved,     10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MoveBeaconData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->beaconTime,     4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->beaconUuid,       16, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->beaconMajor,       2, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->beaconMinor,       2, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->beaconReserved,      10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MoveHygrothermalData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->thermometerTime,    4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->thermometerTemperature,    1, _output_buff, insertionLocation);
								MoveData_byte2buff ((BYTE*)&sensorDataPacket->hygrometerTime,    4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->hygrometerHumidity,     3, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->hygrothermalReserved,     10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MovePanicButtonData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->panicButtonTime,    4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->panicButtonIsPushed,     1, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->panicButtonReserved,     10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MoveImageData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->imageTime,     4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->imageName,       30, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->imageReserved,      10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MoveSpeakerData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->speakerTime,     4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->speakerStationId,      4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->speakerReserved,      10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MoveIoData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->ioTime,      4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->ioInput,        2, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->ioReserved,       10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}

int32_t MoveDisabledPersonResvData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_byte2buff ((BYTE*)&sensorDataPacket->disabledPersonResvTime,  4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->busNo,        10, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->busLicenseNo,       12, _output_buff, insertionLocation);
								MoveData_byte2buff ((BYTE*)&sensorDataPacket->resvUsrGpsX,     4, _output_buff, insertionLocation);
								MoveData_byte2buff ((BYTE*)&sensorDataPacket->resvUsrGpsY,     4, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->isResvSuccess,      1, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->resvBusStopId,      10, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->resvPhone,       12, _output_buff, insertionLocation);
								MoveData_byte2buff (sensorDataPacket->disabledPersonResvReserved,   10, _output_buff, insertionLocation);


								return *insertionLocation - movedDataSize;
}


int32_t BakeBuffToSend (BYTE buff[SEND_BUFF_MAX_LENGTH], int32_t buffSize, BYTE _output_bakedbuff[SEND_BUFF_MAX_LENGTH]) {
								int32_t i, length = 0;
								BYTE _buff[SEND_BUFF_MAX_LENGTH];
								memcpy((char*)_buff, (char*)buff, SEND_BUFF_MAX_LENGTH);
								_output_bakedbuff[336] = '\0';
								_output_bakedbuff[length++] = _buff[0];
								for (i = length; i < buffSize-1; i++) {
																if(_buff[i] == CONTROL_STX) {
																								_output_bakedbuff[length++] = 0x10;
																								_output_bakedbuff[length++] = 0x16;
																} else if (_buff[i] == CONTROL_ETX) {
																								_output_bakedbuff[length++] = 0x10;
																								_output_bakedbuff[length++] = 0x17;
																} else if (_buff[i] == 0x10) {
																								_output_bakedbuff[length++] = 0x10;
																								_output_bakedbuff[length++] = 0x10;
																} else {
																								_output_bakedbuff[length++] = _buff[i];
																}
								}

								_output_bakedbuff[length++] = _buff[buffSize-1];

								return length;
}
//packet2buff end














//buff2value
int32_t MoveData_buff2value (BYTE *buff, SensorDataValue *_output_sensorDataValue) {
								int32_t insertionLocation = 0;
								int32_t movedDataSize = 0;

								memset(_output_sensorDataValue, '\0', sizeof(SensorDataValue));


								MoveData_buff2byte (buff, &insertionLocation, &_output_sensorDataValue->control_stx,       1);
								movedDataSize++;
								MoveData_buff2byte (buff, &insertionLocation, (BYTE*)&_output_sensorDataValue->serialId,      5);
								movedDataSize += 5;
								MoveData_buff2byte (buff, &insertionLocation, (BYTE*)&_output_sensorDataValue->terminalId,     4);
								movedDataSize += 4;

								MoveData_buff2byte (buff, &insertionLocation, &_output_sensorDataValue->responseCode,      1);
								movedDataSize++;
								MoveData_buff2byte (buff, &insertionLocation, &_output_sensorDataValue->errorCode,       1);
								movedDataSize++;
								MoveData_buff2byte (buff, &insertionLocation, &_output_sensorDataValue->commandCode,       1);
								movedDataSize++;
								MoveData_buff2byte (buff, &insertionLocation, &_output_sensorDataValue->seqNo,        1);
								movedDataSize++;

								MoveData_buff2byte (buff, &insertionLocation, (BYTE*)&_output_sensorDataValue->length,        2);
								_output_sensorDataValue->length = ntohs(_output_sensorDataValue->length);
								movedDataSize++;
								movedDataSize++;

								movedDataSize += MoveGpsData_buff2value     (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MoveOBD2Data_buff2value    (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MoveUsrCntData_buff2value    (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MoveWildDrivingData_buff2value   (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MoveBeaconData_buff2value    (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MoveHygrothermalData_buff2value  (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MovePanicButtonData_buff2value   (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MoveImageData_buff2value    (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MoveSpeakerData_buff2value    (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MoveIoData_buff2value     (buff, &insertionLocation, _output_sensorDataValue);
								movedDataSize += MoveDisabledPersonResvData_buff2value (buff, &insertionLocation, _output_sensorDataValue);

								MoveData_buff2byte (buff, &insertionLocation, &_output_sensorDataValue->errorCheck,       1);
								movedDataSize++;
								MoveData_buff2byte (buff, &insertionLocation, &_output_sensorDataValue->control_etx,       1);
								movedDataSize++;

								return movedDataSize;
}

int32_t MoveData_buff2byte (BYTE *buff, int32_t *insertionLocation, BYTE *_output_data, int32_t dataLength) {
								int32_t i;

								memset(_output_data, '\0', dataLength);

								if(*insertionLocation + dataLength > SEND_BUFF_MAX_LENGTH)
																return 0;

								for (i = 0; i < dataLength; i++)
																_output_data[i] = buff[(*insertionLocation)++];

								return dataLength;
}

int32_t MoveGpsData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;
								BYTE tmpBuff[4];

								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->gpsTime,      4);
								_output_sensorDataValue->gpsTime = ntohl(_output_sensorDataValue->gpsTime);

								MoveData_buff2byte (buff, insertionLocation, tmpBuff,              4);
								_output_sensorDataValue->gpsX = ntohl(*(int32_t*)tmpBuff) * 0.000001f;
								MoveData_buff2byte (buff, insertionLocation, tmpBuff,              4);
								_output_sensorDataValue->gpsY = ntohl(*(int32_t*)tmpBuff) * 0.000001f;

								MoveData_buff2byte (buff, insertionLocation, &_output_sensorDataValue->gpsCnt,        1);
								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->gpsSpeed,      4);
								_output_sensorDataValue->gpsSpeed = (float)ntohl(_output_sensorDataValue->gpsSpeed);

								MoveData_buff2byte (buff, insertionLocation, tmpBuff, 3);
								_output_sensorDataValue->gpsHeading = atoi((char*)tmpBuff);


								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->gpsReserved,       10);


								return *insertionLocation - movedDataSize;
}

int32_t MoveOBD2Data_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;
								BYTE tmpBuff[4];


								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->obdTime,      4);
								_output_sensorDataValue->obdTime = ntohl(_output_sensorDataValue->obdTime);

								MoveData_buff2byte (buff, insertionLocation, tmpBuff, 3);
								_output_sensorDataValue->busSpeed = atoi((char*)tmpBuff);

								_output_sensorDataValue->busInnerOxygen[0]   = buff[(*insertionLocation)++] * 0.005f;
								_output_sensorDataValue->busInnerOxygen[1]   = buff[(*insertionLocation)++] * _100_DIV_128_ - 100;

								_output_sensorDataValue->runTimeToEngineStart  = buff[(*insertionLocation)++] | (buff[(*insertionLocation)++]<<8);

								MoveData_buff2byte (buff, insertionLocation, tmpBuff, 3);
								_output_sensorDataValue->absoluteBarometricPressure = atoi((char*)tmpBuff);

								MoveData_buff2byte (buff, insertionLocation, tmpBuff, 3);
								_output_sensorDataValue->fuelTankLevelInput   = atoi((char*)tmpBuff);

								_output_sensorDataValue->engineRPM     = (buff[(*insertionLocation)++] | (buff[(*insertionLocation)++]<<8)) * 0.25f;

								_output_sensorDataValue->engineOilTemperature  = buff[(*insertionLocation)++] - 40;
								_output_sensorDataValue->engineCoolantTemperature = buff[(*insertionLocation)++] - 40;

								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->obdReserved,       10);


								return *insertionLocation - movedDataSize;
}

int32_t MoveUsrCntData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;
								BYTE tmpBuff[4];


								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->usrCntTime,     4);
								_output_sensorDataValue->usrCntTime = ntohl(_output_sensorDataValue->usrCntTime);

								MoveData_buff2byte (buff, insertionLocation, tmpBuff, 3);
								_output_sensorDataValue->usrCnt  = atoi((char*)tmpBuff);
								MoveData_buff2byte (buff, insertionLocation, tmpBuff, 3);
								_output_sensorDataValue->oldUsrCnt = atoi((char*)tmpBuff);

								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->usrCntReserved,      10);


								return *insertionLocation - movedDataSize;
}

int32_t MoveWildDrivingData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->wildDrivingTime,    4);
								_output_sensorDataValue->wildDrivingTime = ntohl(_output_sensorDataValue->wildDrivingTime);

								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->isWildDriving,    1);

								_output_sensorDataValue->gSensorX[0] = buff[(*insertionLocation)++];
								_output_sensorDataValue->gSensorX[1] = buff[(*insertionLocation)++];

								_output_sensorDataValue->gSensorY[0] = buff[(*insertionLocation)++];
								_output_sensorDataValue->gSensorY[1] = buff[(*insertionLocation)++];

								_output_sensorDataValue->gSensorZ[0] = buff[(*insertionLocation)++];
								_output_sensorDataValue->gSensorZ[1] = buff[(*insertionLocation)++];

								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->wildDrivingReserved,     10);


								return *insertionLocation - movedDataSize;
}

int32_t MoveBeaconData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->beaconTime,     4);
								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->beaconUuid,       16);
								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->beaconMajor,       2);
								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->beaconMinor,       2);
								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->beaconReserved,      10);


								return *insertionLocation - movedDataSize;
}

int32_t MoveHygrothermalData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;
								BYTE tmpBuff[4];


								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->thermometerTime,    4);
								_output_sensorDataValue->thermometerTime = ntohl(_output_sensorDataValue->thermometerTime);

								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->thermometerTemperature,  1);
								_output_sensorDataValue->thermometerTemperature -= 40;

								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->hygrometerTime,    4);
								_output_sensorDataValue->hygrometerTime = ntohl(_output_sensorDataValue->hygrometerTime);

								MoveData_buff2byte (buff, insertionLocation, tmpBuff, 3);
								_output_sensorDataValue->hygrometerHumidity = atoi((char*)tmpBuff);

								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->hygrothermalReserved,     10);


								return *insertionLocation - movedDataSize;
}

int32_t MovePanicButtonData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->panicButtonTime,    4);
								_output_sensorDataValue->panicButtonTime = ntohl(_output_sensorDataValue->panicButtonTime);

								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->panicButtonIsPushed,   1);
								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->panicButtonReserved,     10);


								return *insertionLocation - movedDataSize;
}

int32_t MoveImageData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;

								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->imageTime,     4);
								_output_sensorDataValue->imageTime = ntohl(_output_sensorDataValue->imageTime);

								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->imageName,       30);
								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->imageReserved,      10);


								return *insertionLocation - movedDataSize;
}

int32_t MoveSpeakerData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->speakerTime,     4);
								_output_sensorDataValue->speakerTime = ntohl(_output_sensorDataValue->speakerTime);

								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->speakerStationId,      4);
								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->speakerReserved,      10);


								return *insertionLocation - movedDataSize;
}

int32_t MoveIoData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;


								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->ioTime,      4);
								_output_sensorDataValue->ioTime = ntohl(_output_sensorDataValue->ioTime);

								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->ioInput,        2);
								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->ioReserved,       10);


								return *insertionLocation - movedDataSize;
}

int32_t MoveDisabledPersonResvData_buff2value (BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue) {
								int32_t movedDataSize = *insertionLocation;
								BYTE tmpBuff[4];



								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->disabledPersonResvTime,  4);
								_output_sensorDataValue->disabledPersonResvTime = ntohl(_output_sensorDataValue->disabledPersonResvTime);

								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->busNo,        10);
								MoveData_buff2byte (buff, insertionLocation, _output_sensorDataValue->busLicenseNo,       12);

								MoveData_buff2byte (buff, insertionLocation, tmpBuff, 4);
								_output_sensorDataValue->resvUsrGpsX = ntohl(*(int32_t*)tmpBuff) * 0.000001f;
								MoveData_buff2byte (buff, insertionLocation, tmpBuff, 4);
								_output_sensorDataValue->resvUsrGpsY = ntohl(*(int32_t*)tmpBuff) * 0.000001f;

								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->isResvSuccess,    1);
								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->resvBusStopId,    10);
								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->resvPhone,     12);
								MoveData_buff2byte (buff, insertionLocation, (BYTE*)&_output_sensorDataValue->disabledPersonResvReserved, 10);


								return *insertionLocation - movedDataSize;
}


int32_t BakeBuffToRecv (BYTE buff[SEND_BUFF_MAX_LENGTH], int32_t buffSize, BYTE _output_bakedbuff[SEND_BUFF_MAX_LENGTH]) {
								int i, length = 0;
								BYTE _buff[SEND_BUFF_MAX_LENGTH];
								memcpy((char*)_buff, (char*)buff, SEND_BUFF_MAX_LENGTH);

								_output_bakedbuff[length++] = _buff[0];
								for (i = length; i < buffSize-1; i++) {
																if (_buff[i] == 0x10) {
																								if (_buff[i+1] == 0x10) {
																																_output_bakedbuff[length++] = 0x10;
																								} else if (_buff[i+1] == 0x16) {
																																_output_bakedbuff[length++] = CONTROL_STX;
																								} else if (_buff[i+1] == 0x17) {
																																_output_bakedbuff[length++] = CONTROL_ETX;
																								}

																								i++;
																} else {
																								_output_bakedbuff[length++] = _buff[i];
																}
								}

								_output_bakedbuff[length++] = _buff[buffSize-1];

								return length;
}
//buff2value end




















void PrintTime (char *head, int32_t printTime) {
								time_t timet = (time_t)printTime;
								struct tm *timeInfo = localtime (&timet);
								BYTE buff[20];

								memset(buff, '\0', 20);

								if(timeInfo != NULL)
																sprintf(
																								(char*)buff,
																								"%04d-%02d-%02d-%02d-%02d-%02d",
																								timeInfo->tm_year + 1900,
																								timeInfo->tm_mon + 1,
																								timeInfo->tm_mday,
																								timeInfo->tm_hour,
																								timeInfo->tm_min,
																								timeInfo->tm_sec
																								);

								printf("%s %s\n", head, buff);
								printf("%s src:: %d\n", head, printTime);
}


void PrintSensorDataValue (SensorDataValue *sensorDataValue) {

								int i;

								/*
								   sensorDataValue->serialId[0] = 'S';
								   sensorDataValue->serialId[1] = 'S';
								   sensorDataValue->serialId[2] = 'S';
								   sensorDataValue->serialId[3] = 'S';
								   sensorDataValue->serialId[4] = 'S';
								   sensorDataValue->terminalId[0] = 'T';
								   sensorDataValue->terminalId[1] = 'T';
								   sensorDataValue->terminalId[2] = 'T';
								   sensorDataValue->terminalId[3] = 'T';
								 */

								printf("control_stx:: %x\n", sensorDataValue->control_stx);
								printf("\n");

								printf("    serialId:: %c%c%c%c%c\n", sensorDataValue->serialId[0], sensorDataValue->serialId[1], sensorDataValue->serialId[2], sensorDataValue->serialId[3], sensorDataValue->serialId[4]);
								printf("  terminalId:: %c%c%c%c\n", sensorDataValue->terminalId[0], sensorDataValue->terminalId[1], sensorDataValue->terminalId[2], sensorDataValue->terminalId[3]);
								printf("responseCode:: %x\n", sensorDataValue->responseCode);
								printf("   errorCode:: %x\n", sensorDataValue->errorCode);
								printf(" commandCode:: %x\n", sensorDataValue->commandCode);
								printf("       seqNo:: %x\n", sensorDataValue->seqNo);
								printf("\n");

								printf("length:: %d\n", sensorDataValue->length);
								printf("\n");

								PrintTime ("   gpsTime::", sensorDataValue->gpsTime);
								printf  ("      gpsX:: %f\n", sensorDataValue->gpsX);
								printf  ("      gpsY:: %f\n", sensorDataValue->gpsY);
								printf  ("    gpsCnt:: %d\n", sensorDataValue->gpsCnt);
								printf  ("  gpsSpeed:: %f\n", sensorDataValue->gpsSpeed);
								printf  ("gpsHeading:: %d\n", sensorDataValue->gpsHeading);
								printf  ("\n");

								PrintTime ("                   obdTime::", sensorDataValue->obdTime);
								printf  ("                  busSpeed:: %d\n", sensorDataValue->busSpeed);
								printf  ("         busInnerOxygen[0]:: %f\n", sensorDataValue->busInnerOxygen[0]);
								printf  ("         busInnerOxygen[1]:: %f\n", sensorDataValue->busInnerOxygen[1]);
								printf  ("      runTimeToEngineStart:: %d\n", sensorDataValue->runTimeToEngineStart);
								printf  ("absoluteBarometricPressure:: %d\n", sensorDataValue->absoluteBarometricPressure);
								printf  ("        fuelTankLevelInput:: %d\n", sensorDataValue->fuelTankLevelInput);
								printf  ("                 engineRPM:: %f\n", sensorDataValue->engineRPM);
								printf  ("      engineOilTemperature:: %d\n", sensorDataValue->engineOilTemperature);
								printf  ("  engineCoolantTemperature:: %d\n", sensorDataValue->engineCoolantTemperature);
								printf  ("\n");

								PrintTime ("usrCntTime::", sensorDataValue->usrCntTime);
								printf  ("    usrCnt:: %d\n", sensorDataValue->usrCnt);
								printf  (" oldUsrCnt:: %d\n", sensorDataValue->oldUsrCnt);
								printf  ("\n");

								PrintTime ("wildDrivingTime::", sensorDataValue->wildDrivingTime);
								printf  ("  isWildDriving:: %d\n", sensorDataValue->isWildDriving);
								printf  ("       gSensorX:: %d, %d\n", sensorDataValue->gSensorX[0], sensorDataValue->gSensorX[1]);
								printf  ("       gSensorY:: %d, %d\n", sensorDataValue->gSensorY[0], sensorDataValue->gSensorY[1]);
								printf  ("       gSensorZ:: %d, %d\n", sensorDataValue->gSensorZ[0], sensorDataValue->gSensorZ[1]);
								printf  ("\n");

								PrintTime (" beaconTime::", sensorDataValue->beaconTime);
								printf  (" beaconUuid:: ");
								for (i = 0; i < 16; i++)
																printf("%c", sensorDataValue->beaconUuid[i]);
								printf  ("\n");
								printf  ("beaconMajor:: %c, %c\n", sensorDataValue->beaconMajor[0], sensorDataValue->beaconMajor[1]);
								printf  ("beaconMinor:: %c, %c\n", sensorDataValue->beaconMinor[0], sensorDataValue->beaconMinor[1]);
								printf  ("\n");

								PrintTime ("       thermometerTime::", sensorDataValue->thermometerTime);
								printf  ("thermometerTemperature:: %d\n", sensorDataValue->thermometerTemperature);
								PrintTime ("        hygrometerTime::", sensorDataValue->hygrometerTime);
								printf  ("    hygrometerHumidity:: %d\n", sensorDataValue->hygrometerHumidity);
								printf  ("\n");

								PrintTime ("    panicButtonTime::", sensorDataValue->panicButtonTime);
								printf  ("panicButtonIsPushed:: %d\n", sensorDataValue->panicButtonIsPushed);
								printf  ("\n");

								PrintTime ("imageTime::", sensorDataValue->imageTime);
								printf  ("imageName:: %s\n", sensorDataValue->imageName);
								printf  ("\n");

								PrintTime ("     speakerTime::", sensorDataValue->speakerTime);
								printf  ("speakerStationId:: %02x %02x %02x %02x\n", sensorDataValue->speakerStationId[0], sensorDataValue->speakerStationId[1], sensorDataValue->speakerStationId[2], sensorDataValue->speakerStationId[3]);
								printf  ("\n");

								PrintTime ("    ioTime::", sensorDataValue->ioTime);
								printf  ("ioInput[0]:: %x\n", sensorDataValue->ioInput[0]);
								printf  ("ioInput[1]:: %x\n", sensorDataValue->ioInput[1]);
								printf  ("\n");

								PrintTime ("disabledPersonResvTime::", sensorDataValue->disabledPersonResvTime);
								printf  ("                 busNo:: ");
								for (i = 0; i < 10; i++)
																printf("%c", sensorDataValue->busNo[i]);
								printf("\n");

								printf  ("          busLicenseNo:: ");
								for (i = 0; i < 12; i++)
																printf("%c", sensorDataValue->busLicenseNo[i]);
								printf("\n");

								printf  ("           resvUsrGpsX:: %f\n", sensorDataValue->resvUsrGpsX);
								printf  ("           resvUsrGpsY:: %f\n", sensorDataValue->resvUsrGpsY);
								printf  ("         isResvSuccess:: %d\n", sensorDataValue->isResvSuccess);
								printf  ("         resvBusStopId:: ");
								for (i = 0; i < 10; i++)
																printf("%c", sensorDataValue->resvBusStopId[i]);
								printf("\n");

								printf  ("             resvPhone:: ");
								for (i = 0; i < 12; i++)
																printf("%c", sensorDataValue->resvPhone[i]);
								printf("\n");
								printf  ("\n");


								printf  (" errorCheck:: %x\n", sensorDataValue->errorCheck);
								printf  ("control_etx:: %x\n", sensorDataValue->control_etx);
								printf  ("\n");


								printf(">>>>>>>repeat\n");
								printf(">>>>>>>serialId:: %c%c%c%c%c\n", sensorDataValue->serialId[0], sensorDataValue->serialId[1], sensorDataValue->serialId[2], sensorDataValue->serialId[3], sensorDataValue->serialId[4]);
								printf(">>>>>>>terminalId:: %c%c%c%c\n", sensorDataValue->terminalId[0], sensorDataValue->terminalId[1], sensorDataValue->terminalId[2], sensorDataValue->terminalId[3]);
}
