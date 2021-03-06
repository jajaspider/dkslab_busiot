#include <wiringPiI2C.h>
#include <errno.h>
#include <stdint.h>

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
#include "utilForSensor.h"
#include "paths.h"





#define PIN_PANIC_BUTTON 16

#define DevAddr 0x53 //device address
#define PIN_GAS 5






//typedef unsigned char	BYTE;

#define PIN_TRIG 29
#define PIN_ECHO 28

#define PIN_CAMERA 16

#define PIN_CONNECTING_STATE 2







int g_delay = 3000000;

int i=0;


SensorDataPacket g_sendPacket;
SensorDataPacket g_recvPacket;

SensorDataValue g_sendValue;
SensorDataValue g_recvValue;


BYTE g_sendBuff[SEND_BUFF_MAX_LENGTH];
BYTE g_recvBuff[SEND_BUFF_MAX_LENGTH];

char g_serialId[5];
char g_terminalId[4];

int32_t dht11_data[5] = {0,};





//���⼭ ���� main�Լ� �� ������ ������ ȯ�濡�� �ǽð� Ű �Է��� �ޱ����� �ڵ��Դϴ�.
//�����δ� �����ϰ� ���� �ʽ��ϴ�. �����ϼŵ� �����ϴ�.
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





int main (int argc, char **argv) {
	int count = 0;
	int i = 0;

	int fd;
	acc_dat acc_xyz;

	fd = wiringPiI2CSetup (DevAddr);








	char *serialInput = NULL;
	char *terminalInput = NULL;
	char *addressInput = NULL;
	int opt;

	int previous_CONNECTING_STATE;
	int current_CONNECTING_STATE;


	clock_t currentTime = clock();
	clock_t sendTime = clock();

	int percentageOfPacket = 0;
	int buffLength = 0;

	uint16_t *pUshortNum;
	int32_t isAwake = 1;
	unsigned int timeToNextSend = 2;;
	unsigned int recvCount = 0;

	int isPanicButtonPushed = 0;
	int isPanicButtonPushed_isChecked = 0;

	int32_t sock;// = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sin;

	int key = 0;

	srand(time(NULL));




//init
	while ( (opt = getopt(argc, argv, "hs:t:r:a:d:")) != -1 ) {
		switch (opt) {
			case '?':
				printf("????????\n");
			case 'h':
				printf("help\n");
				printf("-h	: printf help.\n");
				printf("-s	: set serial id.	  (size:: 5)\n");
				printf("-t	: set terminal id.	  (size:: 4)\n");
				printf("-a	: set server's adress	  (min :: 7)\n");
				printf("-d	: set communication delay (min :: 500000)\n");
				return 0;
				break;
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
			case 'a':
				addressInput = optarg;
				if(strlen(addressInput) < 6) {
					printf("address is too short.\n");
					return 0;
				}
				break;
			case 'd':
				g_delay = atoi(optarg);
				if(atoi(optarg) < 500000){
					printf("communication delay is too short.\n");
					return 0;
				}
				break;
		}
	}





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








	if( -1 == fd)
		perror("I2C device setup error");
	if(wiringPiSetup() == -1)
		exit(1);





	pinMode(PIN_GAS, INPUT);
	pinMode(PIN_TRIG, OUTPUT);
	pinMode(PIN_ECHO, INPUT);
	pinMode(PIN_CAMERA, INPUT);
	pinMode(PIN_CONNECTING_STATE, INPUT);

	adxl345_init(fd);



	previous_CONNECTING_STATE = current_CONNECTING_STATE = HIGH;

	while (1) {
		current_CONNECTING_STATE = digitalRead(PIN_CONNECTING_STATE);
		acc_xyz = adxl345_read_xyz(fd);
		Read_dht11_data (dht11_data);

		if(previous_CONNECTING_STATE == HIGH) {

			//Sensors
//=====================================================================
			if(digitalRead(PIN_CAMERA) == LOW)
				system("python camerapy.py");

			printf("\n\n\n\n\n\n\n");

			printf("now wating...\n");

			printf("					I");
			if (count < 6) {
				for(i=0; i<count; i++)
					printf("O");
				for(i=0; i<5-count; i++)
					printf(" ");
			} else {
				for(i=0; i<count-5; i++)
					printf(" ");
				for(i=0; i<10-count; i++)
					printf("O");
			}
			printf("I");



			printf("\n\n\n\n\n\n\n\n");

			delay(200);
			count++;

			if(count >= 10)
				count = 0;
		} else {

			//Ethernet

			currentTime = clock();

			if(recvCount == 0) isAwake = 1;


			if(digitalRead(PIN_PANIC_BUTTON))
				isPanicButtonPushed_isChecked = 0;

			isPanicButtonPushed = !digitalRead(PIN_PANIC_BUTTON) && !isPanicButtonPushed_isChecked;



			if(currentTime <=  sendTime && !isPanicButtonPushed)
				continue;


			//connect
			sock = socket(AF_INET, SOCK_STREAM, 0);
			memset((char*)&sin, '\0', sizeof(sin));
			sin.sin_family = AF_INET;
			sin.sin_port = htons(30000);
			if(addressInput == NULL)
				sin.sin_addr.s_addr = inet_addr("113.198.235.247");
			else
				sin.sin_addr.s_addr = inet_addr(addressInput);
			memset(&(sin.sin_zero), 0, 8);
			connect(sock, (struct sockaddr*)&sin, sizeof(struct sockaddr));
			printf("Connected\n");

			MoveData_sensor2value (&g_sendValue, g_serialId, g_terminalId);
			if (isPanicButtonPushed) {
				g_sendValue.panicButtonIsPushed = 1;
				g_sendValue.commandCode = COMMAND_CODE_PANIC;
			} else if (isAwake) {
				g_sendValue.commandCode = COMMAND_CODE_START_DRIVING;
				isAwake = 0;
			} else {
				g_sendValue.commandCode = COMMAND_CODE_SEND_SENSOR_DATA;
			}




			if(current_CONNECTING_STATE == HIGH) {
				g_sendValue.commandCode = COMMAND_CODE_STOP_DRIVING;
			}


			MoveData_value2packet (&g_sendValue, &g_sendPacket);
			buffLength = MoveData_packet2buff (&g_sendPacket, g_sendBuff);
			PrintSensorDataValue (&g_sendValue);
			buffLength = BakeBuffToSend(g_sendBuff, buffLength, g_sendBuff);

			//send
			percentageOfPacket = send(sock, g_sendBuff, SEND_BUFF_MAX_LENGTH, 0);
			printf("PercentageOf(Send)Packet:: %d (%3.2f%%)\n", percentageOfPacket, (float)percentageOfPacket/SEND_BUFF_MAX_LENGTH*100);



			//recv
			buffLength = recv(sock, (char*)g_recvBuff, SEND_BUFF_MAX_LENGTH, 0);



			BakeBuffToRecv(g_recvBuff, buffLength, g_recvBuff);

			MoveData_buff2value (g_recvBuff, &g_recvValue);
			if(g_recvValue.commandCode == COMMAND_CODE_DISABLED_PERSON_RESV_SEND) {
				SensorDataValueCpoy (&g_sendValue, &g_recvValue);
				g_sendValue.commandCode = COMMAND_CODE_DISABLED_PERSON_RESV_PUSH;
				g_sendValue.isResvSuccess = 1;
				PrintSensorDataValue(&g_sendValue);
				printf("COMMAND_CODE:: DISABLED_PERSON_RESV_PUSH\n");

				MoveData_value2packet (&g_sendValue, &g_sendPacket);
				buffLength = MoveData_packet2buff (&g_sendPacket, g_sendBuff);
				buffLength = BakeBuffToSend(g_sendBuff, buffLength, g_sendBuff);

				//send
				send(sock, (char*)g_sendBuff, SEND_BUFF_MAX_LENGTH, 0);
				printf("Closed\n");
			}

			if (g_sendValue.commandCode == COMMAND_CODE_STOP_DRIVING){
				printf("COMMAND_CODE:: STOP_DRIVING\n");
			}

			if (isPanicButtonPushed)
				printf(">>>>Panic Button Pushed!\n");

			printf("::recvComplete\n");
			printf("----------------------recvCount::%d----------------------\n\n\n", recvCount);

			recvCount++;

			isPanicButtonPushed_isChecked = 1;
			sendTime = clock() + g_delay;

			//close
			close(sock);


			if (g_sendValue.commandCode == COMMAND_CODE_STOP_DRIVING)
				recvCount = 0;
		}

		previous_CONNECTING_STATE = current_CONNECTING_STATE;
	}

	return 0;
}
