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

extern "C" int32_t GetDataFromRecvBuff (BYTE g_recvBuff[SEND_BUFF_MAX_LENGTH], SensorDataValue *_output_sensorDataValue);
extern "C" void PrintSensorDataValue (SensorDataValue *sensorDataValue);



void RemoveSocket(SOCKET target)
{
	for(unsigned int i=0; i < client.size(); i++)
	{
		if(client.at(i) == target)
			client.erase(client.begin()+i);
	}
}



/**
	*@brief		서버 메인 루틴
	*@author	정동진
	*@date		2017.04.02
*/
DWORD WINAPI Chat_Serv(LPVOID arg)
{
	int i;
	SOCKET c_sock = (SOCKET)arg;
	SOCKADDR_IN caddr;
	int namelen = sizeof(caddr);
	int isFirst = 1;
	//char buf[BUFLEN];

	unsigned char temp[4] = {0,};
	int recvlen;
	int recvSize = 0;
	int bufflength;


	getpeername(c_sock, (SOCKADDR*)&caddr, &namelen);
	client.push_back(c_sock);

	printf("\n Clinet is connected. %s(%d)\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

	while(1)
	{
		recvlen = recv(c_sock, (char*)g_recvBuff, FRAME_LENGTH_TO_LENGTH_DATA, 0);
		recvSize = 0;

		temp[0] = g_recvBuff[14];
		temp[1] = g_recvBuff[15];
		temp[2] = g_recvBuff[16];
		temp[3] = g_recvBuff[17];
		bufflength = *(unsigned int*)temp;
		printf("    header:: %d\n", recvlen);
		printf("bufflength:: %u\n", bufflength);


		while(recvlen < bufflength) {
			recvSize = recv(c_sock, (char*)&g_recvBuff[FRAME_LENGTH_TO_LENGTH_DATA], bufflength, 0);

			recvlen += recvSize;
			printf("(recvSize):: %d\n", recvSize);
			printf("   (total):: %d\n", recvlen);
			printf("          :: %3.5f%%\n\n", (float)recvlen/bufflength*100);

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

		

		printf("  complete:: %d (%3.2f%%)\n", recvlen, /*(i==0?1:i)*/(float)recvlen/bufflength*100);



		FILE *fp = fopen(CAMERA_IMAGE_PATH, "wb");
		if(fp == NULL) {
			printf("ERROR:: file open fail.\n");
		}
		fwrite(g_recvValue.imageData, 1, g_recvValue.imageSize, fp);
		fclose(fp);
		




		if (kbhit()) {
			switch (getch())
			{
			case 'd':
			case 'D':
				printf("g_recvBuff[60]:: 0x%X\n", g_recvBuff[60]);
				g_recvBuff[60] = 1;
				printf("g_recvBuff[60]:: 0x%X\n", g_recvBuff[60]);
				break;
			default:
				break;
			}

			while(kbhit()){getch();}
		}




		GetDataFromRecvBuff(g_recvBuff, &g_recvValue);
		PrintSensorDataValue(&g_recvValue);

		//*****************************************************

		//work!

		//*****************************************************


		//ACK
		send (c_sock, (char*)g_recvBuff, bufflength, 0);

		//!하드코딩. g_recvBuff[60]는 disabledPersonIsReserved가 저장된 위치.
		if (g_recvBuff[60] == 1) {
			recv(c_sock, (char*)g_recvBuff, bufflength, 0);

			if(g_recvBuff[60] == 1)
				printf("RecvSuccess:: The disable person is reserved.\n");
			else
				printf("RecvFail:: The disable person is not reserved.\n");
		}




		if(g_recvValue.commandCode[0] == COMMAND_CODE_START_DRIVING)
			printf("COMMAND_CODE:: START_DRIVING\n");
		if(g_recvValue.commandCode[0] == COMMAND_CODE_STOP_DRIVING) {
			printf("COMMAND_CODE:: STOP_DRIVING\n");
			printf("-------------------------------------\n");
			printf("client Good-bye case\n");
			return 0;
		}

		printf("-------------------------------------\n");

		//LeaveCriticalSection(&cs);
	}
}



int main()
{
	PROCESS_INFORMATION p_info;
    STARTUPINFO s_info;
	//CreateProcess(L"NewConsole", L"cmdLine", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &s_info, &p_info);
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
	}



	closesocket(s_sock);
	WSACleanup();
	return 0;
}