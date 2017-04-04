/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dks_lab_bus_server;

/**
 *
 * @author how32
 */
public class ParsingByte {
    public final static int GPS_INT_BYTE           = 1 * 2;
    public final static int GPS_DECIMAL_BYTE       = 3 * 2;
    public final static int HOUR_BYTE              = 1 * 2;
    public final static int MINUTE_BYTE            = 1 * 2;
    public final static int SECOND_BYTE            = 1 * 2;
    public final static int MILLISECOND_BYTE       = 1 * 2;
    public final static int TEMPERATURE_BYTE       = 1 * 2;
    public final static int COOLING_BYTE           = 1 * 2;
    public final static int PASSENGERS_BYTE        = 1 * 2;
    public final static int OLD_PASSENGERS_BYTE    = 1 * 2;
    public final static int HUMIDITY_BYTE          = 1 * 2;
    public final static int PANIC_BUTTON_BYTE      = 1 * 2;
    public final static int RESERVATION_CHECK_BYTE = 1 * 2;
    public final static int RESERVATION_ID_BYTE    = 3 * 2;
    public final static int RESERVATION_PHONE_BYTE = 5 * 2;
    public final static int RECKLESS_BYTE          = 1 * 2;
    public final static int G_SENSOR_INT_BYTE      = 1 * 2;
    public final static int G_SENSOR_DECIMAL_BYTE  = 3 * 2;
    public final static int CAR_SPEED_BYTE         = 1 * 2;
    public final static int CAR_PRESSURE_BYTE      = 2 * 2;
    public final static int FUEL_HEIGHT_BYTE       = 1 * 2;
    public final static int OIL_BYTE               = 1 * 2;
    public final static int GPS_COUNT_BYTE         = 1 * 2;
    public final static int CAR_OXYGEN_BYTE        = 1 * 2;
    public final static int ENGINE_NEXT_BYTE       = 2 * 2;
    public final static int ROTATION_BYTE          = 4 * 2;
    public final static int BEACON_UUID_BYTE       = 16 * 2;
    public final static int BEACON_MAJOR_BYTE      = 2 * 2;
    public final static int BEACON_MINOR_BYTE      = 2 * 2;
    public final static int SPEAKER_BYTE           = 1 * 2;
    public final static int IO_INPUT_BYTE          = 1 * 2;
    public final static int IMAGE_BYTE             = 4 * 2;
    public final static int ERROR_CHECK_BYTE       = 1 * 2;
    public final static int CONTROL_BYTE           = 1 * 2;
}
