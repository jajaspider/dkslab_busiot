#pragma once

#include "codes.h"
#include <stdint.h>
#include <stdarg.h>

#define SEND_BUFF_MAX_LENGTH		650
#define BYTE						unsigned char
#define DIV256						0.00390625f

/**
	*@brief		센서 데이터를 패킷의 형태로 가지고 있는 구조체.
	*@details	각 데이터는 프로토콜에 정의 된 순서대로 선언되었습니다.\n
				클라이언트에서 센서에 직접 접근하여 초기화 및 갱신됩니다.
	*@see		InitSensorDataPacket
	*@see		GetSensorDataPacketSize
	*@see		UpdateSensorDataPacket
	*@see		GetGpsData_sensor2packet
	*@see		GetThermometerData_sensor2packet
	*@see		GetCoolerData_sensor2packet
	*@see		GetUsrCntData_sensor2packet
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
	*@author	정동진
	*@date		2017.04.02
*/
typedef struct _SensorDataPacket {
//header
	BYTE	control_stx						[1];

	//!센서보드의 시리얼 ID.
	BYTE	serialId						[5];
	//!센서보드의 터미널 ID.
	BYTE	terminalId						[4];
	/**
	@brief	응답 코드.
	@see	RESPONSE_CODE_ACK
	@see	RESPONSE_CODE_NACK
	@see	RESPONSE_CODE_REQ
	*/
	BYTE	responseCode					[1];
	/**
	@brief	에러 코드.
	@see	ERROR_CODE_SUCCESS
	@see	ERROR_CODE_DATA_LENGTH_ERROR
	@see	ERROR_CODE_DATA_FORMAT_ERROR
	@see	ERROR_CODE_CRC_ERROR
	@see	ERROR_CODE_TIME_OUT
	@see	ERROR_CODE_DATASTORE_ERROR
	@see	ERROR_CODE_RESPONSE_CODE_ERROR
	@see	ERROR_CODE_ERROR_CODE_ERROR
	@see	ERROR_CODE_COMMAND_CODE_ERROR
	@see	ERROR_CODE_TERMINAL_ID_ERROR
	@see	ERROR_CODE_UNREGISTERED_TERMINAL_ERROR
	@see	ERROR_CODE_REQUEST_DATA_NOT_EXIST
	@see	ERROR_CODE_UNKNOWN_ERROR
	*/
	BYTE	errorCode						[1];
	/**
	@brief	명령 코드.
	@see	COMMAND_CODE_INIT
	@see	COMMAND_CODE_SEND_SENSOR_DATA
	@see	COMMAND_CODE_START_DRIVING
	@see	COMMAND_CODE_RESTART_DRIVING
	@see	COMMAND_CODE_STOP_DRIVING
	@see	COMMAND_CODE_ARRIVE_BUS_STOP
	@see	COMMAND_CODE_PASS_KEY_SPOT
	@see	COMMAND_CODE_DISABLED_PERSON_RESV_TRY
	@see	COMMAND_CODE_DISABLED_PERSON_RESV_SUCCESS
	@see	COMMAND_CODE_DISABLED_PERSON_RESV_CANCEL
	*/
	BYTE	commandCode						[1];
	BYTE	seqNo							[1];

	int16_t	length;
//header end





	int32_t	gpsTime;
	int32_t	gpsX;
	int32_t	gpsY;
	BYTE	gpsCnt							[1];
	float	gpsSpeed;
	int16_t	gpsHeading;
	BYTE	gpsReserved						[10];

//OBD-II
	int32_t	obdTime;
	BYTE	busSpeed						[1];
	BYTE	busInnerOxygen					[2];
	int16_t	runTimeToEngineStart;
	BYTE	absoluteBarometricPressure		[1];
	BYTE	fuelTankLevelInput				[1];
	BYTE	engineRPM						[2];
	char	engineOilTemperature			[1];
	char	engineCoolantTemperature		[1];
	BYTE	obdReserved						[10];
//OBD-II end
	
	int32_t	usrCntTime;
	int16_t	usrCnt;
	int16_t	oldUsrCnt;
	BYTE	usrCntReserved					[10];

	int32_t	wildDrivingTime;
	BYTE	isWildDriving					[1];
	BYTE	gSensorX						[2];
	BYTE	gSensorY						[2];
	BYTE	gSensorZ						[2];
	BYTE	wildDrivingReserved				[10];

	int32_t	beaconTime;
	BYTE	beaconUuid						[16];
	BYTE	beaconMajor						[2];
	BYTE	beaconMinor						[2];
	BYTE	beaconReserved					[10];

	int32_t	thermometerTime;
	BYTE	thermometerTemperature			[1];
	int32_t	hygrometerTime;
	BYTE	hygrometerHumidity				[1];
	BYTE	hygrothermalReserved			[10];

	int32_t	panicButtonTime;
	BYTE	panicButtonIsPushed				[1];
	BYTE	panicButtonReserved				[10];

	int32_t	imageTime;
	BYTE	imageName						[30];
	BYTE	imageReserved					[10];

	int32_t	speakerTime;
	BYTE	speakerStationId				[4];
	BYTE	speakerReserved					[10];

	int32_t	ioTime;
	BYTE	ioInput							[2];
	BYTE	ioReserved						[10];

	int32_t	disabledPersonResvTime;
	BYTE	busNo							[10];
	BYTE	busLicenseNo					[12];
	int32_t	resvUsrGpsX;
	int32_t	resvUsrGpsY;
	BYTE	isResvSuccess					[1];
	BYTE	resvBusStopId					[10];
	BYTE	resvPhone						[12];
	BYTE	disabledPersonResvReserved		[10];

	BYTE	errorCheck						[1];
	BYTE	control_etx						[1];

}SensorDataPacket;
//SensorDataPacket g_sendPacket;
//SensorDataPacket g_recvPacket;












/**
	*@brief		센서 데이터를 변수의 형태로 가지고 있는 구조체.
	*@details	각 데이터는 프로토콜에 정의 된 순서대로 선언되었습니다.\n
				버퍼에 저장된 값을 통해 초기화 및 갱신됩니다.
	*@see		GetDataFromRecvBuff
	*@see		PrintSensorDataValue
	*@see		GetGpsData_buff2value
	*@see		GetThermometerData_buff2value
	*@see		GetCoolerData_buff2value
	*@see		GetUsrCntData_buff2value
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
	*@author	정동진
	*@date		2017.04.02
*/
typedef struct _SensorDataValue {

//header
	BYTE	control_stx;

	BYTE	serialId						[5];
	BYTE	terminalId						[4];
	BYTE	responseCode;
	BYTE	errorCode;
	BYTE	commandCode;
	BYTE	seqNo;

	int32_t	length;
//header end

	


	int32_t	gpsTime;
	float	gpsX;
	float	gpsY;
	BYTE	gpsCnt;
	float	gpsSpeed;
	int32_t	gpsHeading;
	BYTE	gpsReserved						[10];

//OBD-II
	int32_t obdTime;
	int32_t	busSpeed;
	float	busInnerOxygen					[2];
	int32_t	runTimeToEngineStart;
	int32_t	absoluteBarometricPressure;
	int32_t	fuelTankLevelInput;
	float	engineRPM;
	int32_t	engineOilTemperature;
	int32_t	engineCoolantTemperature;
	BYTE	obdReserved						[10];
//OBD-II end

	int32_t	usrCntTime;
	int32_t	usrCnt;
	int32_t	oldUsrCnt;
	BYTE	usrCntReserved					[10];

	int32_t	wildDrivingTime;
	int32_t	isWildDriving;
	BYTE	gSensorX						[2];
	BYTE	gSensorY						[2];
	BYTE	gSensorZ						[2];
	BYTE	wildDrivingReserved				[10];

	int32_t	beaconTime;
	BYTE	beaconUuid						[16];
	BYTE	beaconMajor						[2];
	BYTE	beaconMinor						[2];
	BYTE	beaconReserved					[10];

	int32_t	thermometerTime;
	int32_t	thermometerTemperature;
	int32_t	hygrometerTime;
	int32_t	hygrometerHumidity;
	BYTE	hygrothermalReserved			[10];

	int32_t	panicButtonTime;
	int32_t	panicButtonIsPushed;
	BYTE	panicButtonReserved				[10];

	int32_t	imageTime;
	BYTE	imageName						[30];
	BYTE	imageReserved					[10];

	int32_t	speakerTime;
	BYTE	speakerStationId				[4];
	BYTE	speakerReserved					[10];

	int32_t	ioTime;
	BYTE	ioInput							[2];
	BYTE	ioReserved						[10];

	int32_t	disabledPersonResvTime;
	BYTE	busNo							[10];
	BYTE	busLicenseNo					[12];
	float	resvUsrGpsX;
	float	resvUsrGpsY;
	int32_t	isResvSuccess;
	BYTE	resvBusStopId					[10];
	BYTE	resvPhone						[12];
	BYTE	disabledPersonResvReserved		[10];

	BYTE	errorCheck;
	BYTE	control_etx;
}SensorDataValue;
//SensorDataValue g_sendValue;
//SensorDataValue g_recvValue;


//char g_serialId[5];
//char g_terminalId[4];

//!패킷을 전송하기 위한 버퍼입니다.
//BYTE g_sendBuff[SEND_BUFF_MAX_LENGTH];
//!g_sendBuff에 패킷을 입력할 때, 현재 입력해야 할 위치를 나타냅니다.\n현재까지 입력 한 데이터의 길이 이기도 합니다.
//int32_t g_sendBuffInsertionLocation;

//!패킷을 수신하기 위한 버퍼입니다.
//BYTE g_recvBuff[SEND_BUFF_MAX_LENGTH];
//!g_recvBuff에서 패킷을 읽을 때, 현재 읽어야 할 위치를 나타냅니다.\n현재까지 읽은 데이터의 길이 이기도 합니다.
//int32_t g_recvBuffInsertionLocation;

//void SensorDataValueCpoy (SensorDataValue *src, SensorDataValue *dst);
//void initReservedValue (BYTE *reserved, int length);

//패킷을 '\0'으로 초기화합니다.
void InitSensorDataPacket (SensorDataPacket *sensorDataPacket);





//sensor2value
//int32_t MoveData_sensor2value					(SensorDataValue *_output_sensorDataValue, BYTE *serialId, BYTE *terminalId);

int32_t MoveGpsData_sensor2value				(SensorDataValue *_output_sensorDataValue);

int32_t MoveOBD2Data_sensor2value				(SensorDataValue *_output_sensorDataValue);

int32_t MoveUsrCntData_sensor2value				(SensorDataValue *_output_sensorDataValue);

int32_t MoveWildDrivingData_sensor2value		(SensorDataValue *_output_sensorDataValue);

int32_t MoveBeaconData_sensor2value				(SensorDataValue *_output_sensorDataValue);

int32_t MoveHygrothermalData_sensor2value		(SensorDataValue *_output_sensorDataValue);

int32_t MovePanicButtonData_sensor2value		(SensorDataValue *_output_sensorDataValue);

int32_t MoveImageData_sensor2value				(SensorDataValue *_output_sensorDataValue);

int32_t MoveSpeakerData_sensor2value			(SensorDataValue *_output_sensorDataValue);

int32_t MoveIoData_sensor2value					(SensorDataValue *_output_sensorDataValue);

int32_t MoveDisabledPersonResvData_sensor2value	(SensorDataValue *_output_sensorDataValue);

//sensor2value end




//value2packet
//int32_t MoveData_value2packet					(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveGpsData_value2packet				(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveOBD2Data_value2packet				(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveUsrCntData_value2packet				(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveWildDrivingData_value2packet		(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveBeaconData_value2packet				(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveHygrothermalData_value2packet		(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MovePanicButtonData_value2packet		(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveImageData_value2packet				(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveSpeakerData_value2packet			(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveIoData_value2packet					(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);

int32_t MoveDisabledPersonResvData_value2packet	(SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);
//value2packet end









//packet2buff
//int32_t MoveData_packet2buff					(SensorDataPacket *sensorDataPacket, BYTE *_output_buff);
int32_t MoveData_byte2buff						(BYTE *data, int32_t dataLengthBYTE, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveGpsData_packet2buff					(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveOBD2Data_packet2buff				(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveUsrCntData_packet2buff				(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveWildDrivingData_packet2buff			(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveBeaconData_packet2buff				(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveHygrothermalData_packet2buff		(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MovePanicButtonData_packet2buff			(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveImageData_packet2buff				(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveSpeakerData_packet2buff				(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveIoData_packet2buff					(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);

int32_t MoveDisabledPersonResvData_packet2buff	(SensorDataPacket *sensorDataPacket, BYTE *_output_buff, int32_t *insertionLocation);


//int32_t BakeBuffToSend							(BYTE buff[SEND_BUFF_MAX_LENGTH], int32_t buffSize, BYTE _output_bakedbuff[SEND_BUFF_MAX_LENGTH]);
//packet2buff end


















//buff2value
//int32_t MoveData_buff2value					(BYTE *buff, SensorDataValue *_output_sensorDataValue);
int32_t MoveData_buff2byte						(BYTE *buff, int32_t *insertionLocation, BYTE *_output_data, int32_t dataLength);

int32_t MoveGpsData_buff2value					(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MoveOBD2Data_buff2value					(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MoveUsrCntData_buff2value				(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MoveWildDrivingData_buff2value			(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MoveBeaconData_buff2value				(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MoveHygrothermalData_buff2value			(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MovePanicButtonData_buff2value			(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MoveImageData_buff2value				(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MoveSpeakerData_buff2value				(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MoveIoData_buff2value					(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);

int32_t MoveDisabledPersonResvData_buff2value	(BYTE *buff, int32_t *insertionLocation, SensorDataValue *_output_sensorDataValue);


//int32_t BakeBuffToRecv							(BYTE buff[SEND_BUFF_MAX_LENGTH], int32_t buffSize, BYTE _output_bakedbuff[SEND_BUFF_MAX_LENGTH]);
//buff2value end







void PrintTime (char *head, int32_t printTime);
//void PrintSensorDataValue (SensorDataValue *sensorDataValue);