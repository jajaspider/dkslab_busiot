#pragma warning(disable:4996)

#include <WinSock2.h>
#include <stdio.h>
#include <vector>
#include <stdint.h>
#include <time.h>
#include <conio.h>
#include "utilForPacket.h"
#include "paths.h"
#include "codes.h"


#define MAX_THREAD_NUM	100
#define BUFLEN			80

using namespace std;




CRITICAL_SECTION cs;

vector<SOCKET> client;
int th_index;

SensorDataPacket g_sendPacket;
SensorDataPacket g_recvPacket;

SensorDataValue g_sendValue;
SensorDataValue g_recvValue;

BYTE g_sendBuff[SEND_BUFF_MAX_LENGTH];
BYTE g_recvBuff[SEND_BUFF_MAX_LENGTH];

char g_serialId[5];
char g_terminalId[4];

extern "C" void SensorDataValueCpoy (SensorDataValue *src, SensorDataValue *dst);
extern "C" void PrintSensorDataValue (SensorDataValue *sensorDataValue);
extern "C" int32_t MoveData_sensor2value (SensorDataPacket *_output_sensorDataValue);
extern "C" int32_t MoveData_value2packet (SensorDataValue *sensorDataValue, SensorDataPacket *_output_sensorDataPacket);
extern "C" int32_t MoveData_packet2buff (SensorDataPacket *sensorDataPacket, BYTE *_output_buff);
extern "C" int32_t MoveData_buff2value (BYTE *buff, SensorDataValue *_output_sensorDataValue);
extern "C" int32_t BakeBuffToSend							(BYTE buff[SEND_BUFF_MAX_LENGTH], int32_t buffSize, BYTE _output_bakedbuff[SEND_BUFF_MAX_LENGTH]);
extern "C" int32_t BakeBuffToRecv							(BYTE buff[SEND_BUFF_MAX_LENGTH], int32_t buffSize, BYTE _output_bakedbuff[SEND_BUFF_MAX_LENGTH]);



void RemoveSocket(SOCKET target)
{
	for(unsigned int i=0; i < client.size(); i++)
		if(client.at(i) == target){
			client.erase(client.begin()+i);
			closesocket(target);
			printf("--------------------Remove %d sock--------------------\n\n\n", i);
		}
}



/**
	*@brief		서버 메인 루틴
	*@author	정동진
	*@date		2017.04.02
*/
DWORD WINAPI Chat_Serv(LPVOID arg)
{
//	int i;
	SOCKET c_sock = (SOCKET)arg;
	SOCKADDR_IN caddr;
	int namelen = sizeof(caddr);
	int isFirst = 1;
	//char buf[BUFLEN];
	int buffLength = 0;

	unsigned char temp[4] = {0,};
	int recvlen;
	int recvSize = 0;


	getpeername(c_sock, (SOCKADDR*)&caddr, &namelen);
	client.push_back(c_sock);

	printf("\n Clinet is connected. %s(%d)\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

//	while(1)
//	{
		recvlen = recv(c_sock, (char*)g_recvBuff, SEND_BUFF_MAX_LENGTH, 0);
		recvSize = 0;

		while(recvlen < SEND_BUFF_MAX_LENGTH) {
			recvSize = recv(c_sock, (char*)g_recvBuff, SEND_BUFF_MAX_LENGTH, 0);

			recvlen += recvSize;
			printf("(recvSize):: %d\n", recvSize);
			printf("   (total):: %d\n", recvlen);
			printf("          :: %3.5f%%\n\n", (float)recvlen/SEND_BUFF_MAX_LENGTH*100);

			if(recvSize == SOCKET_ERROR)
			{
				printf("(in)recv() error case\n");
				RemoveSocket(c_sock);
				closesocket(c_sock);

				return -1;
			}

			if(recvSize == 0)
			{
				printf("(in)client Good-bye case\n");
				RemoveSocket(c_sock);
				closesocket(c_sock);
				return 0;
			}
		}
		printf("  complete:: %d (%3.2f%%)\n", recvlen, /*(i==0?1:i)*/(float)recvlen/SEND_BUFF_MAX_LENGTH*100);
		buffLength = recvlen;
//*****************************************************
//work!
		BakeBuffToRecv(g_recvBuff, buffLength, g_recvBuff);







		MoveData_buff2value(g_recvBuff, &g_recvValue);
		PrintSensorDataValue(&g_recvValue);
		
		SensorDataValueCpoy(&g_sendValue, &g_recvValue);

		g_sendValue.commandCode = COMMAND_CODE_DEPART_FROME_BUS_STOP;

		if (kbhit()) {
			switch (getch())
			{
			case 'd':
			case 'D':
				g_sendValue.commandCode = COMMAND_CODE_DISABLED_PERSON_RESV_SEND;

				g_sendValue.resvCnt = 1;
				strncpy((char*)g_sendValue.busNo,			"110-1", strlen("110-1"));
				strncpy((char*)g_sendValue.busLicenseNo,	"70바 1234", strlen("70바 1234"));
				g_sendValue.resvUsrGpsX = 127.123456f;
				g_sendValue.resvUsrGpsY = 127.456789f;
				g_sendValue.isResvSuccess = 0;
				strncpy((char*)g_sendValue.resvBusStopId,	"82234", strlen("82234"));
				strncpy((char*)g_sendValue.resvPhone,		"001012345678", strlen("001012345678"));

				break;
			default:
				break;
			}

			while(kbhit()){getch();}
		}

//for(int i=0; i<SEND_BUFF_MAX_LENGTH; i++) printf("%d, %02x\n", i, g_sendBuff[i]);
//*****************************************************


		MoveData_value2packet (&g_sendValue, &g_sendPacket);
		buffLength = MoveData_packet2buff (&g_sendPacket, g_sendBuff);

		//ACK
		buffLength = BakeBuffToSend(g_sendBuff, buffLength, g_sendBuff);
		send (c_sock, (char*)g_sendBuff, SEND_BUFF_MAX_LENGTH, 0);













		if(g_sendValue.commandCode == COMMAND_CODE_DISABLED_PERSON_RESV_SEND) {
			buffLength = recv(c_sock, (char*)g_recvBuff, SEND_BUFF_MAX_LENGTH, 0);
			BakeBuffToRecv(g_recvBuff, buffLength, g_recvBuff);
			MoveData_buff2value(g_recvBuff, &g_recvValue);
			
			PrintSensorDataValue(&g_recvValue);
			if(g_recvValue.isResvSuccess)
				printf("RecvSuccess:: The disable person is reserved.\n");
			else
				printf("RecvFail:: The disable person is not reserved.\n");
		}
		




		switch (g_recvValue.commandCode) {
		case COMMAND_CODE_INIT:
			printf("COMMAND_CODE:: INIT\n");
			break;

		case COMMAND_CODE_SEND_SENSOR_DATA:
			printf("COMMAND_CODE:: SEND_SENSOR_DATA\n");
			break;

		case COMMAND_CODE_START_DRIVING:
			printf("COMMAND_CODE:: START_DRIVING\n");
			break;

		case COMMAND_CODE_RESTART_DRIVING:
			printf("COMMAND_CODE:: RESTART_DRIVING\n");
			break;

		case COMMAND_CODE_STOP_DRIVING:
			printf("COMMAND_CODE:: STOP_DRIVING\n");
			printf("-------------------------------------\n");
			printf("client Good-bye case\n");
			return 0;
			break;

		case COMMAND_CODE_ARRIVE_AT_BUS_STOP:
			printf("COMMAND_CODE:: ARRIVE_AT_BUS_STOP\n");
			break;

		case COMMAND_CODE_DEPART_FROME_BUS_STOP:
			printf("COMMAND_CODE:: DEPART_FROME_BUS_STOP\n");
			break;

		case COMMAND_CODE_PASS_KEY_SPOT:
			printf("COMMAND_CODE:: PASS_KEY_SPOT\n");
			break;

		case COMMAND_CODE_DISABLED_PERSON_RESV_SEND:
			printf("COMMAND_CODE:: DISABLED_PERSON_RESV_SEND\n");
			printf("Impossible cammand code.\n");
			return -1;
			break;

		case COMMAND_CODE_DISABLED_PERSON_RESV_PUSH:
			printf("COMMAND_CODE:: DISABLED_PERSON_RESV_PUSH\n");
			break;

		case COMMAND_CODE_DISABLED_PERSON_RESV_CANCEL:
			printf("COMMAND_CODE:: DISABLED_PERSON_RESV_CANCEL\n");
			break;

		case COMMAND_CODE_PANIC:
			printf("COMMAND_CODE:: PANIC\n");
			break;

		default:
			printf("Unknown Error:: %x\n", g_sendValue.commandCode);
			return -1;
			break;
		}

		//LeaveCriticalSection(&cs);
//	}

	RemoveSocket(c_sock);
}



int main()
{

	WSADATA wsa;

	SOCKET s_sock;

	SOCKADDR_IN saddr;
	SOCKADDR_IN caddr;
	int namelen;

	HANDLE th[MAX_THREAD_NUM];

	SOCKET c_sock;

	InitializeCriticalSection(&cs);
	EnterCriticalSection(&cs);

	WSAStartup(MAKEWORD(2, 2), &wsa);


	s_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(4200);
	//saddr.sin_port = htons(30000);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(s_sock, (SOCKADDR*)&saddr, sizeof(saddr));
	listen(s_sock, SOMAXCONN);

	namelen = sizeof(caddr);
	

	InitializeCriticalSection(&cs);


	while(1)
	{
		printf("Server is waiting for connection......");
		c_sock = accept(s_sock, (SOCKADDR*)&caddr, &namelen);

		th[th_index++] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Chat_Serv, (LPVOID)c_sock, 0, NULL);


		printf("th: %d\n", th_index);
	}



	closesocket(s_sock);
	WSACleanup();
	return 0;
}