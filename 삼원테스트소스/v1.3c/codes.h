#pragma once

#include "utilForPacket.h"

#define CONTROL_STX                               (BYTE)0x02
#define CONTROL_ETX                               (BYTE)0x03

#define RESPONSE_CODE_ACK                         (BYTE)0x00
#define RESPONSE_CODE_NACK                        (BYTE)0x01
#define RESPONSE_CODE_REQ                         (BYTE)0x02


#define ERROR_CODE_SUCCESS                        (BYTE)0x00
#define ERROR_CODE_DATA_LENGTH_ERROR              (BYTE)0x01
#define ERROR_CODE_DATA_FORMAT_ERROR              (BYTE)0x02
#define ERROR_CODE_CRC_ERROR                      (BYTE)0x03
#define ERROR_CODE_TIME_OUT                       (BYTE)0x04
#define ERROR_CODE_DATASTORE_ERROR                (BYTE)0x05
#define ERROR_CODE_RESPONSE_CODE_ERROR            (BYTE)0x06
#define ERROR_CODE_ERROR_CODE_ERROR               (BYTE)0x07
#define ERROR_CODE_COMMAND_CODE_ERROR             (BYTE)0x08
#define ERROR_CODE_TERMINAL_ID_ERROR              (BYTE)0x09
#define ERROR_CODE_UNREGISTERED_TERMINAL_ERROR    (BYTE)0x0A
#define ERROR_CODE_REQUEST_DATA_NOT_EXIST         (BYTE)0x0B
#define ERROR_CODE_UNKNOWN_ERROR                  (BYTE)0xFF

#define COMMAND_CODE_INIT                         (BYTE)0x01
#define COMMAND_CODE_SEND_SENSOR_DATA             (BYTE)0x02
#define COMMAND_CODE_START_DRIVING                (BYTE)0x03
#define COMMAND_CODE_RESTART_DRIVING              (BYTE)0x04
#define COMMAND_CODE_STOP_DRIVING                 (BYTE)0x05
#define COMMAND_CODE_ARRIVE_AT_BUS_STOP           (BYTE)0x80
#define COMMAND_CODE_DEPART_FROME_BUS_STOP        (BYTE)0x81
#define COMMAND_CODE_PASS_KEY_SPOT                (BYTE)0x82
#define COMMAND_CODE_DISABLED_PERSON_RESV_SEND    (BYTE)0x84
#define COMMAND_CODE_DISABLED_PERSON_RESV_PUSH    (BYTE)0x85
#define COMMAND_CODE_DISABLED_PERSON_RESV_CANCEL  (BYTE)0x86
#define COMMAND_CODE_PANIC                        (BYTE)0x99

#define SEQ_NO_FROM                               (BYTE)0x00
#define SEQ_NO_TO                                 (BYTE)0xFF
#define SEQ_NO_INCREASE                           (BYTE)0x01

#define ERROR_CHECK_STX                           (BYTE)0xFF

#define CAMERA_IMAGE_WIDTH                              720
#define CAMERA_IMAGE_HEIGHT                             616
