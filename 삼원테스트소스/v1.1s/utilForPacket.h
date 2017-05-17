#pragma once

#include "codes.h"
#include <stdint.h>

#define FRAME_LENGTH_TO_LENGTH_DATA	18
#define SEND_BUFF_MAX_LENGTH		1330693
#define	SEND_IMAGE_MAX_SIZE			1330560
#define BYTE						unsigned char


/**
	*@brief		���� �����͸� ��Ŷ�� ���·� ������ �ִ� ����ü.
	*@details	�� �����ʹ� �������ݿ� ���� �� ������� ����Ǿ����ϴ�.\n
				Ŭ���̾�Ʈ���� ������ ���� �����Ͽ� �ʱ�ȭ �� ���ŵ˴ϴ�.
	*@see		InitSensorDataPacket
	*@see		GetSensorDataPacketSize
	*@see		UpdateSensorDataPacket
	*@see		GetGpsData_sensor2packet
	*@see		GetThermometerData_sensor2packet
	*@see		GetCoolerData_sensor2packet
	*@see		GetUsersData_sensor2packet
	*@see		GetHygrometerData_sensor2packet
	*@see		GetPanicButtonData_sensor2packet
	*@see		GetDisabledPersonReservationData_sensor2packet
	*@see		GetWildDrivingData_sensor2packet
	*@see		GetGSensorData_sensor2packet
	*@see		GetOBD2Data_sensor2packet
	*@see		GetBeaconData_sensor2packet
	*@see		GetSpeakerData_sensor2packet
	*@see		GetIoData_sensor2packet
	*@see		GetImageData_sonsor2packet
	*@author	������
	*@date		2017.04.02
*/
typedef struct _SensorDataPacket {
	BYTE	control_stx						[1];

	//!���������� �ø��� ID.
	BYTE	serialId						[5];
	//!���������� �͹̳� ID.
	BYTE	terminalId						[4];
	/**
	@brief	���� �ڵ�.
	@see	RESPONSE_CODE_ACK
	@see	RESPONSE_CODE_NACK
	@see	RESPONSE_CODE_REQ
	*/
	BYTE	responseCode					[1];
	/**
	@brief	���� �ڵ�.
	@see	ERROR_CODE_SUCCESS
	@see	RESPONSE_CODE_NACK
	@see	RESPONSE_CODE_REQ
	@see	RESPONSE_CODE_REQ
	@see	RESPONSE_CODE_REQ
	@see	RESPONSE_CODE_REQ
	@see	RESPONSE_CODE_REQ
	@see	RESPONSE_CODE_REQ
	@see	RESPONSE_CODE_REQ
	@see	RESPONSE_CODE_REQ
	*/
	BYTE	errorCode						[1];
	BYTE	commandCode						[1];
	BYTE	seqNo							[1];

	int32_t length;

	BYTE	gpsTime							[3];
	BYTE	gpsX							[4];
	BYTE	gpsY							[4];
	BYTE	gpsSatelliteCount				[1];

	BYTE	thermometerTime					[4];
	BYTE	thermometerTemperature			[1];

	BYTE	coolerTime						[4];
	BYTE	coolerTemperature				[1];

	BYTE	usersTime						[4];
	BYTE	usersCount						[1];
	BYTE	oldUsersCount					[1];

	BYTE	hygrometerTime					[4];
	BYTE	hygrometerHumidity				[1];

	BYTE	panicButtonTime					[4];
	BYTE	panicButtonIsPushed				[1];

	BYTE	disabledPersonReservedTime		[4];
	BYTE	disabledPersonIsReserved		[1];
	int32_t	disabledPersonReservedStationId;
	int32_t	disabledPersonPhon;

	BYTE	wildDrivingTime					[4];
	BYTE	isWildDriving					[1];

	BYTE	gSensorX						[2];
	BYTE	gSensorY						[2];
	BYTE	gSensorZ						[2];

//OBD-II
	BYTE	busSpeed						[1];
	BYTE	absoluteBarometricPressure		[1];
	BYTE	fuelTankLevelInput				[1];
	BYTE	engineOilTemperature			[1];
	char	busInnerOxygen					[2];
	BYTE	runTimeToEngineStart			[2];
	BYTE	engineRPM						[2];
//OBD-II end

	BYTE	beaconTime						[4];
	BYTE	beaconUuid						[16];
	BYTE	beaconMajor						[2];
	BYTE	beaconMinor						[2];

	BYTE	speakerTime						[4];
	int32_t	speakerStationId;

	BYTE	ioTime							[4];
	BYTE	ioInput							[1];

	int32_t	imageSize;
	BYTE	imageData						[SEND_IMAGE_MAX_SIZE];
	
	BYTE	errorCheck						[1];
	BYTE	control_etx						[1];

}SensorDataPacket;
SensorDataPacket g_sensorDataPacket_send, g_sensorDataPacket_recv;


/**
	*@brief		���� �����͸� ������ ���·� ������ �ִ� ����ü.
	*@details	�� �����ʹ� �������ݿ� ���� �� ������� ����Ǿ����ϴ�.\n
				���ۿ� ����� ���� ���� �ʱ�ȭ �� ���ŵ˴ϴ�.
	*@see		GetDataFromRecvBuff
	*@see		PrintSensorDataValue
	*@see		GetGpsData_buff2value
	*@see		GetThermometerData_buff2value
	*@see		GetCoolerData_buff2value
	*@see		GetUsersData_buff2value
	*@see		GetHygrometerData_buff2value
	*@see		GetPanicButtonData_buff2value
	*@see		GetDisabledPersonReservationData_buff2value
	*@see		GetWildDrivingData_buff2value
	*@see		GetGSensorData_buff2value
	*@see		GetOBD2Data_buff2value
	*@see		GetBeaconData_buff2value
	*@see		GetSpeakerData_buff2value
	*@see		GetIoData_buff2value
	*@see		GetImageData_buff2value
	*@author	������
	*@date		2017.04.02
*/
typedef struct _SensorDataValue {
	BYTE	control_stx						[1];

	BYTE	serialId						[5];
	BYTE	terminalId						[4];
	BYTE	responseCode					[1];
	BYTE	errorCode						[1];
	BYTE	commandCode						[1];
	BYTE	seqNo							[1];

	int32_t length;

	BYTE	gpsTime							[3];
	double	gpsX;
	double	gpsY;
	int32_t	gpsSatelliteCount;

	double	thermometerTime;
	int32_t	thermometerTemperature;

	double	coolerTime;
	int32_t	coolerTemperature;

	double	usersTime;
	int32_t	usersCount;
	int32_t	oldUsersCount;

	double	hygrometerTime;
	int32_t	hygrometerHumidity;

	double	panicButtonTime;
	int32_t	panicButtonIsPushed;

	double	disabledPersonReservedTime;
	int32_t	disabledPersonIsReserved;
	int32_t	disabledPersonReservedStationId;
	int32_t	disabledPersonPhon;

	double	wildDrivingTime;
	int32_t	isWildDriving;

	BYTE	gSensorX						[2];
	BYTE	gSensorY						[2];
	BYTE	gSensorZ						[2];

//OBD-II
	int32_t	busSpeed;
	int32_t	absoluteBarometricPressure;
	int32_t	fuelTankLevelInput;
	int32_t	engineOilTemperature;
	float	busInnerOxygen;
	int32_t	runTimeToEngineStart;
	float	engineRPM;
//OBD-II end

	double	beaconTime;
	BYTE	beaconUuid						[16];
	BYTE	beaconMajor						[2];
	BYTE	beaconMinor						[2];

	double	speakerTime;
	int32_t	speakerStationId;

	double	ioTime;
	BYTE	ioInput;

	int32_t	imageSize;
	BYTE	imageData						[SEND_IMAGE_MAX_SIZE];
	
	BYTE	errorCheck						[1];
	BYTE	control_etx						[1];
}SensorDataValue;
SensorDataValue g_recvValue;


char g_serialId[5];
char g_terminalId[4];

//!��Ŷ�� �����ϱ� ���� �����Դϴ�.
BYTE g_sendBuff[SEND_BUFF_MAX_LENGTH];
//!g_sendBuff�� ��Ŷ�� �Է��� ��, ���� �Է��ؾ� �� ��ġ�� ��Ÿ���ϴ�.\n������� �Է� �� �������� ���� �̱⵵ �մϴ�.
BYTE g_sendBuffInsertionLocation;

//!��Ŷ�� �����ϱ� ���� �����Դϴ�.
BYTE g_recvBuff[SEND_BUFF_MAX_LENGTH];
//!g_recvBuff���� ��Ŷ�� ���� ��, ���� �о�� �� ��ġ�� ��Ÿ���ϴ�.\n������� ���� �������� ���� �̱⵵ �մϴ�.
BYTE g_recvBuffInsertionLocation;

//��Ŷ�� '\0'���� �ʱ�ȭ�մϴ�.
void InitSensorDataPacket (SensorDataPacket *sensorDataPacket);

//!��Ŷ�� �� ���̸� �����մϴ�.
int32_t GetSensorDataPacketSize (SensorDataPacket *sensorDataPacket);

/**
	@brief	������ ���� �����͸� �����մϴ�. �ڵ����� �޸𸮸� �ʱ�ȭ ���� �ʽ��ϴ�.
	@param	int32_t takeAPicture ���� ���� ���� (1: ����, 0: �������� ����)
*/
int32_t UpdateSensorDataPacket (SensorDataPacket *sensorDataPacket, int32_t takeAPicture);

//!g_sendBuff�� '\0'���� �ʱ�ȭ �� �� g_sendBuffInsertionLocation�� 0���� �����մϴ�.
void ClearSendBuff ();

void ClearSensorDataPacket (SensorDataPacket *sensorDataPacket);

//!���� �ð��� �����մϴ�. ����� 235959.999�� �����մϴ�.
int32_t GetOccurrenceTime ();





//!data�� g_sendBuff�� �Է��մϴ�.
int32_t AddDataToSendBuff_int (int32_t data);

//!data�� g_sendBuff�� �Է��մϴ�.
int32_t AddDataToSendBuff_data (BYTE *data, int dataLength);

//!sensorDataPacket�� g_sendBuff�� �Է��մϴ�.
int32_t AddDataToSendBuff_packet (SensorDataPacket *sensorDataPacket);





int32_t GetGpsData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetThermometerData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetCoolerData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetUsersData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetHygrometerData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetPanicButtonData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetDisabledPersonReservationData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetWildDrivingData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetGSensorData_sensor2packet(SensorDataPacket *_output_sensorDataPacket);

int32_t GetOBD2Data_sensor2packet(SensorDataPacket *_output_sensorDataPacket);

int32_t GetBeaconData_sensor2packet(SensorDataPacket *_output_sensorDataPacket);

int32_t GetSpeakerData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetIoData_sensor2packet (SensorDataPacket *_output_sensorDataPacket);

int32_t GetImageData_sonsor2packet (char *filePath, SensorDataPacket *_output_sensorDataPacket);



int32_t TakeAPicture (char *filePath, int width, int height);




int32_t GetTime2Buff (BYTE buff[SEND_BUFF_MAX_LENGTH], double *_output_time);



int32_t GetGpsData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetThermometerData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetCoolerData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetUsersData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetHygrometerData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetPanicButtonData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetDisabledPersonReservationData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetWildDrivingData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetGSensorData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetOBD2Data_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetBeaconData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetSpeakerData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetIoData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);

int32_t GetImageData_buff2value (BYTE buff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);







//int32_t GetDataFromRecvBuff (SensorDataValue *_output_sensorDataValue);
//void PrintSensorDataValue (SensorDataValue *sensorDataValue);