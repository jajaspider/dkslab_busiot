#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <termios.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <memory.h>
#include <arpa/inet.h>

#include "codes.h"
#include "utilForPacket.h"
#include "paths.h"

int g_delay = 5000000;

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

void close_keyboard () {
								tcsetattr(0, TCSANOW, &initial_settings);
}

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




								init_keyboard();




								memset((char*)&sin, '\0', sizeof(sin));
								sin.sin_family = AF_INET;
								sin.sin_port = htons(4200);
								sin.sin_addr.s_addr = inet_addr("192.168.0.49");
								memset(&(sin.sin_zero), 0, 8);
								connect(sock, (struct sockaddr*)&sin, sizeof(struct sockaddr));


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




/*************************************************************
 **************************************************************/

								ClearSendBuff();
								memset(&g_recvBuff, '\0', SEND_BUFF_MAX_LENGTH);
								InitSensorDataPacket(&g_sensorDataPacket_send);
								InitSensorDataPacket(&g_sensorDataPacket_recv);

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
																								isPanicButtonPushed_isChecked = 0;







																if(currentTime <=  sendTime && !isPanicButtonPushed)
																								continue;




																ClearSendBuff ();
																ClearSensorDataPacket (&g_sensorDataPacket_send);
																UpdateSensorDataPacket(&g_sensorDataPacket_send, 0 /*!isAwake*/);

																if (isAwake) {
																								g_sensorDataPacket_send.commandCode[0] = COMMAND_CODE_START_DRIVING;
																								isAwake = 0;
																}

																if(count >= repeatCount) {
																								isAwake = 1;
																								g_sensorDataPacket_send.commandCode[0] = COMMAND_CODE_STOP_DRIVING;
																}



																if (isPanicButtonPushed) {
																								g_sensorDataPacket_send.panicButtonIsPushed[0] = 1;
																								printf(">>>>Panic Button Pushed!\n");
																}


																AddDataToSendBuff_packet(&g_sensorDataPacket_send);
																percentageOfPacket = send(sock, g_sendBuff, g_sendBuffInsertionLocation, 0);
																printf("PercentageOf(Send)Packet:: %d (%3.2f%%)\n", percentageOfPacket, (float)percentageOfPacket/g_sensorDataPacket_send.length*100);




																recv(sock, (char*)g_recvBuff, g_sensorDataPacket_send.length, 0);
																if(g_recvBuff[60] == 1) {
																								printf("RecvSucccess:: The disable person reserved.\n");
																								GetDataFromRecvBuff(&g_recvValue);
																								printf("disabledPersonReservedTime:: %.3f\n", g_recvValue.disabledPersonReservedTime);
																								printf("disabledPersonReservedStationId:: %d\n", g_recvValue.disabledPersonReservedStationId);
																								printf("disabledPersonPhon:: %d\n", g_recvValue.disabledPersonPhon);
																								send(sock, (char*)g_recvBuff, g_sensorDataPacket_send.length, 0);
																}




																if (g_sensorDataPacket_send.commandCode[0] == COMMAND_CODE_STOP_DRIVING)
																								break;






																count++;

																isPanicButtonPushed_isChecked = 1;
																sendTime = clock() + g_delay;
								}


/*************************************************************
 **************************************************************/




								close_keyboard();
								return 0;
}
