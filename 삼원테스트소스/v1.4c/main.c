#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <termios.h>
#include <wiringPi.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <memory.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#include "codes.h"
#include "utilForPacket.h"
#include "paths.h"

#define PIN_PANIC_BUTTON 15



int g_delay = 5000000;

int i=0;



SensorDataPacket g_sendPacket;
SensorDataPacket g_recvPacket;

SensorDataValue g_sendValue;
SensorDataValue g_recvValue;


BYTE g_sendBuff[SEND_BUFF_MAX_LENGTH];
BYTE g_recvBuff[SEND_BUFF_MAX_LENGTH];

char g_serialId[5];
char g_terminalId[4];



static struct termios initial_settings, new_settings;
static int peek_character = -1;
void init_keyboard () {
	tcgetattr(0, &initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
}
void close_keyboard () {tcsetattr(0, TCSANOW, &initial_settings);}
int _kbhit () {
	unsigned char ch;
	int nread;

	if(peek_character != -1) return 1;
	new_settings.c_cc[VMIN] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0, &ch, 1);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
	if(nread == 1) {
		peek_character = ch;
		return 1;
	}
	return 0;
}
int _getch () {
	char ch;
	if (peek_character != -1) {
		ch = peek_character;
		peek_character = -1;
		return ch;
	}
	read(0, &ch, 1);
	return ch;
}
int _putch (int c) {
	putchar(c);
	fflush(stdout);
	return c;
}








int  main (int argc, char **argv) {

	int repeatCount = 10;
	char *serialInput = NULL;
	char *terminalInput = NULL;
	int opt;

	clock_t currentTime = clock();
	clock_t sendTime = clock();

	int percentageOfPacket = 0;
	int i;
	uint16_t *pUshortNum;
	int32_t isAwake = 1;
	unsigned int timeToNextSend = 2;;
	unsigned int count = 0;

	int isPanicButtonPushed = 0;
	int isPanicButtonPushed_isChecked = 0;

	int32_t sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sin;

	int key = 0;

	while ( (opt = getopt(argc, argv, "hs:t:r:")) != -1 ) {
		switch (opt) {
			case 'h':
				printf("help\n");
				printf("-h	: printf help.\n");
				printf("-s	: set serial id.	(size:: 5)\n");
				printf("-t	: set terminal id.	(size:: 4)\n");
				printf("-r	: set repeat count.	(min :: 1)\n");
				return 0; break;
			case 's':
				serialInput = optarg;
				if(strlen(serialInput) < 5) {
					printf("serial id is too short.\n");
					return 0;
				}
				break;
			case 't':
				terminalInput = optarg;
				if(strlen(terminalInput) < 4) {
					printf("terminal id is too short.\n");
					return 0;
				}
				break;
			case 'r':
				sscanf(optarg, "%d", &repeatCount);
				if(repeatCount < 1) {
					printf("repeatCount is too short.\n");
					return 0;
				}
				break;
			case '?':
				return 0; break;
		}
	}




	//init_keyboard();




	memset((char*)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4200);
	sin.sin_addr.s_addr = inet_addr("169.254.227.239");
	memset(&(sin.sin_zero), 0, 8);
	connect(sock, (struct sockaddr*)&sin, sizeof(struct sockaddr));
	printf("Connected\n");

	if(serialInput == NULL) {
		g_serialId[0] = 'S';
		g_serialId[1] = 'S';
		g_serialId[2] = 'S';
		g_serialId[3] = 'S';
		g_serialId[4] = 'S';
	} else {
		g_serialId[0] = serialInput[0];
		g_serialId[1] = serialInput[1];
		g_serialId[2] = serialInput[2];
		g_serialId[3] = serialInput[3];
		g_serialId[4] = serialInput[4];
	}


	if(terminalInput == NULL) {
		g_terminalId[0] = 'T';
		g_terminalId[1] = 'T';
		g_terminalId[2] = 'T';
		g_terminalId[3] = 'T';
	} else {
		g_terminalId[0] = terminalInput[0];
		g_terminalId[1] = terminalInput[1];
		g_terminalId[2] = terminalInput[2];
		g_terminalId[3] = terminalInput[3];
	}



	if (wiringPiSetup() == -1) return 1;


/*************************************************************
**************************************************************/

	while (1) {
		currentTime = clock();
/*
		if(_kbhit()) {
			key = _getch();
			_putch(key);

			switch (key) {
			case 'p':
			case 'P':
				sendTime = 0;
				break;
			}
		}
*/
		if(digitalRead(PIN_PANIC_BUTTON))
			isPanicButtonPushed_isChecked = 0;

		isPanicButtonPushed = !digitalRead(PIN_PANIC_BUTTON) && !isPanicButtonPushed_isChecked;



		if(currentTime <=  sendTime && !isPanicButtonPushed)
			continue;




		MoveData_sensor2value (&g_sendValue, g_serialId, g_terminalId);
		g_sendValue.commandCode = COMMAND_CODE_SEND_SENSOR_DATA;
		
		if (isAwake) {
			g_sendValue.commandCode = COMMAND_CODE_START_DRIVING;
			isAwake = 0;
		}

		if(count >= repeatCount) {
			g_sendValue.commandCode = COMMAND_CODE_STOP_DRIVING;
		}


		MoveData_value2packet (&g_sendValue, &g_sendPacket);
		MoveData_packet2buff (&g_sendPacket, g_sendBuff);
		PrintSensorDataValue(&g_sendValue);

BakeBuffToSend(g_sendBuff, SEND_BUFF_MAX_LENGTH, g_sendBuff);
		
		percentageOfPacket = send(sock, g_sendBuff, SEND_BUFF_MAX_LENGTH, 0);
		printf("PercentageOf(Send)Packet:: %d (%3.2f%%)\n", percentageOfPacket, (float)percentageOfPacket/SEND_BUFF_MAX_LENGTH*100);




		recv(sock, (char*)g_recvBuff, SEND_BUFF_MAX_LENGTH, 0);
BakeBuffToRecv(g_recvBuff, SEND_BUFF_MAX_LENGTH, g_recvBuff);
		MoveData_buff2value (g_recvBuff, &g_recvValue);
		if(g_recvValue.commandCode == COMMAND_CODE_DISABLED_PERSON_RESV_SEND) {
			SensorDataValueCpoy (&g_sendValue, &g_recvValue);
			g_sendValue.commandCode = COMMAND_CODE_DISABLED_PERSON_RESV_PUSH;
			g_sendValue.isResvSuccess = 1;
			PrintSensorDataValue(&g_sendValue);
			printf("COMMAND_CODE:: DISABLED_PERSON_RESV_PUSH\n");
			
			MoveData_value2packet (&g_sendValue, &g_sendPacket);
			MoveData_packet2buff (&g_sendPacket, g_sendBuff);
BakeBuffToSend(g_sendBuff, SEND_BUFF_MAX_LENGTH, g_sendBuff);
			send(sock, (char*)g_sendBuff, SEND_BUFF_MAX_LENGTH, 0);
		}
		
		if (g_sendValue.commandCode == COMMAND_CODE_STOP_DRIVING){
			printf("COMMAND_CODE:: STOP_DRIVING\n");
			break;
		}
		
		if (isPanicButtonPushed) {
			g_sendValue.commandCode = COMMAND_CODE_PANIC;
			g_sendValue.panicButtonIsPushed = 1;
			printf(">>>>Panic Button Pushed!\n");
		}
		
		printf("::recvComplete\n");

		count++;

		isPanicButtonPushed_isChecked = 1;
		sendTime = clock() + g_delay;
	}


/*************************************************************
**************************************************************/




//	close_keyboard();
	return 0;
}
