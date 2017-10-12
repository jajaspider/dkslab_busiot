all:
	gcc -c utilForPacket.c utilForSensor.c
	gcc -o main main.c utilForPacket.o utilForSensor.o -lcurses -lwiringPi
