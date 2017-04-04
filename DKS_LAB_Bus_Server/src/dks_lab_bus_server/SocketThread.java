/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dks_lab_bus_server;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

/**
 *
 * @author Admit
 */
public class SocketThread extends Thread {
    /* 
        수집된 데이터들을 분류, 각 클래스에 저장함 
        데이터 앞의 첫 글자로 데이터들을 분류해서 처리함
    */
    private Socket socket = null;
    
    private BusDBService dbService = null;
    private DataInputStream dIStream = null;
    private PrintWriter writer = null;
    
    private BusClientData busClientData = null;
    
    public SocketThread(Socket socket) {
        this.socket = socket;
        this.dbService = new BusDBService();
    }
    
    private void createPrintWriter() {
        try {
            writer = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
        } catch (IOException ex) {
            System.out.println("[Erro] PrintWriter Create Error");
        }
    }
    
    private void createDataInputStream() {
        try {
            dIStream = new DataInputStream(socket.getInputStream());
        }catch(IOException ex){
            System.out.println("[Erro] DataInputStream Create Error");
        }
    }
    
    private void closePrintWriter() {
        writer.close();
    }
    
    private void closeDataInputStream() {
        try {
            dIStream.close();
        }catch(IOException ex) {
            System.out.println("[Erro] DataInputStream Close Error");
        }
    }
    
    private void closeSocket() {
        try{
            socket.close();
        }catch(IOException ex) {
            System.out.println("[Erro] Socket Close Error");
        }
    }
    
    private String readDataStream() {
        //소켓으로부터 전송된 byte 데이터를 읽어내 String으로 변환해 보여주는 함수
        byte[] readStream = new byte[1024];
        byte[] readData = null;
        String clientData = null;
        try {
            int streamSize = dIStream.read(readStream);
            if(streamSize != 0) {
                readData = new byte[streamSize];
                for(int i=0;i<streamSize;++i) {
                    readData[i] = readStream[i];
                }
                clientData = new String(readData, 0, readData.length);
            }
            return clientData;
        }catch(NegativeArraySizeException ex) {
            System.out.println("[Erro] Data ArraySize Error");
            return null;
        }catch(IOException ex) {
            System.out.println("[Erro] Data Read Error");
            return null;
        }
    }
    
    private Object inputDataParse(String clientData, int byteCount, int byteNumber, String dataType) {
        //readDataStream으로 읽어낸 데이터를 파싱하는 함수
        String data = new String(clientData.getBytes(), byteCount, byteNumber);
        switch(dataType) {
            case "String" :
                String stringData = busClientData.getStringData(data);
                return stringData;
            case "int" :
                int intData = busClientData.getIntData(data);
                return intData;
            default :
                return null;
        }
    }
    
    @Override
    public void run() {
        //통신 시 필요한 객체들이 없을 경우에만 생성함
        if(dIStream == null) { createDataInputStream(); }
        if(writer == null) { createPrintWriter(); }
        if(dbService == null) { dbService = new BusDBService(); }
        if(busClientData == null) { busClientData = new BusClientData(); }
        
        String clientData;
        while( (clientData = readDataStream()) != null ) {
            if(clientData.equals("")) { break; }
            //소켓으로부터 읽어낸 데이터를 변환했을 때, null값이거나 빈 칸이 아닐 경우에만 진행
            try{
                System.out.println("[Info] Input Data : " + clientData);
                int byteCount = 0;
                
                //GPS X Data
                int gpsXIntData = (int)inputDataParse(clientData, byteCount, ParsingByte.GPS_INT_BYTE, "int");
                byteCount += ParsingByte.GPS_INT_BYTE;
                int gpsXDecimalData = (int)inputDataParse(clientData, byteCount, ParsingByte.GPS_DECIMAL_BYTE, "int");
                byteCount += ParsingByte.GPS_DECIMAL_BYTE;
                System.out.println("[Data] GPS X Data : " + gpsXIntData + "." + gpsXDecimalData);
                //GPS Y Data
                int gpsYIntData = (int)inputDataParse(clientData, byteCount, ParsingByte.GPS_INT_BYTE, "int");
                byteCount += ParsingByte.GPS_INT_BYTE;
                int gpsYDecimalData = (int)inputDataParse(clientData, byteCount, ParsingByte.GPS_DECIMAL_BYTE, "int");
                byteCount += ParsingByte.GPS_DECIMAL_BYTE;
                System.out.println("[Data] GPS Y Data : " + gpsYIntData + "." + gpsYDecimalData);
                //GPS Time
                int gpsHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int gpsMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int gpsSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                System.out.println("[Data] GPS Time Data : " + gpsHourData + ":" + gpsMinuteData + ":" + gpsSecondData);
                
                //Temperature Time
                int temperatureHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int temperatureMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int temperatureSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int temperatureMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Temperature Time Data : " + temperatureHourData + ":" + temperatureMinuteData + ":" + temperatureSecondData + "." + temperatureMilliSecondData);
                //Temperature Data
                int temperatureData = (int)inputDataParse(clientData, byteCount, ParsingByte.TEMPERATURE_BYTE, "int");
                byteCount += ParsingByte.TEMPERATURE_BYTE;
                System.out.println("[Data] Temperature Data : " + temperatureData);
                
                //Car Cooling Time
                int coolingHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int coolingMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int coolingSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int coolingMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Cooling Time Data : " + coolingHourData + ":" + coolingMinuteData + ":" + coolingSecondData + "." + coolingMilliSecondData);
                //Car Cooling Data
                int coolingData = (int)inputDataParse(clientData, byteCount, ParsingByte.COOLING_BYTE, "int");
                byteCount += ParsingByte.COOLING_BYTE;
                System.out.println("[Data] Cooling Data : " + coolingData);
                
                //Bus Passengers Time
                int passengersHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int passengersMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int passengersSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int passengersMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Passengers Time Data : " + passengersHourData + ":" + passengersMinuteData + ":" + passengersSecondData + "." + passengersMilliSecondData);
                //Bus Passengers Data
                int passengersData = (int)inputDataParse(clientData, byteCount, ParsingByte.PASSENGERS_BYTE, "int");
                byteCount += ParsingByte.PASSENGERS_BYTE;
                System.out.println("[Data] Passengers Data : " + passengersData);
                //Previous Bus Passengers Data
                int prevPassengersData = (int)inputDataParse(clientData, byteCount, ParsingByte.OLD_PASSENGERS_BYTE, "int");
                byteCount += ParsingByte.OLD_PASSENGERS_BYTE;
                System.out.println("[Data] PreviousPassengers Data : " + prevPassengersData);
                
                //Humidity Time
                int humidityHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int humidityMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int humiditySecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int humidityMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Humidity Time Data : " + humidityHourData + ":" + humidityMinuteData + ":" + humiditySecondData + "." + humidityMilliSecondData);
                //Humidity Data
                int humidityData = (int)inputDataParse(clientData, byteCount, ParsingByte.HUMIDITY_BYTE, "int");
                byteCount += ParsingByte.HUMIDITY_BYTE;
                System.out.println("[Data] Humidity Data : " + humidityData);
                
                //Panic Button Push Time
                int panicButtonHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int panicButtonMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int panicButtonSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int panicButtonMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] PanicButton Push Time Data : " + panicButtonHourData + ":" + panicButtonMinuteData
                        + ":" + panicButtonSecondData + "." + panicButtonMilliSecondData);
                //Panic Button Push Data
                String panicButtonData = (String)inputDataParse(clientData, byteCount, ParsingByte.PANIC_BUTTON_BYTE, "String");
                byteCount += ParsingByte.PANIC_BUTTON_BYTE;
                System.out.println("[Data] PanicButton Push Data : " + panicButtonData);
                
                //Reservation Call Time
                int reservationHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int reservationMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int reservationSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int reservationMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Reservation Call Time Data : " + reservationHourData + ":" + reservationMinuteData
                        + ":" + reservationSecondData + "." + reservationMilliSecondData);
                //Reservation Call Data
                String reservationCallData = (String)inputDataParse(clientData, byteCount, ParsingByte.RESERVATION_CHECK_BYTE, "String");
                byteCount += ParsingByte.RESERVATION_CHECK_BYTE;
                System.out.println("[Data] Reservation Data : " + reservationCallData);
                //Reservation ID Data
                int reservationIdData = (int)inputDataParse(clientData, byteCount, ParsingByte.RESERVATION_ID_BYTE, "int");
                byteCount += ParsingByte.RESERVATION_ID_BYTE;
                System.out.println("[Data] Reservation ID Data : " + reservationIdData);
                //Reservation Phone Data
                int reservationPhoneData = (int)inputDataParse(clientData, byteCount, ParsingByte.RESERVATION_PHONE_BYTE, "int");
                byteCount += ParsingByte.RESERVATION_PHONE_BYTE;
                System.out.println("[Data] Reservation Phone Data : 0" + reservationPhoneData);
                
                //Reckless Time Data
                int recklessHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int recklessMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int recklessSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int recklessMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Reckless Time Data : " + recklessHourData + ":" + recklessMinuteData + ":" + recklessSecondData + "." + recklessMilliSecondData);
                //Reckless Data
                String recklessData = (String)inputDataParse(clientData, byteCount, ParsingByte.RECKLESS_BYTE, "String");
                byteCount += ParsingByte.RECKLESS_BYTE;
                System.out.println("[Data] Reckless Data : " + recklessData);
                
                //G-Sensor Datas
                int gSensorXIntData = (int)inputDataParse(clientData, byteCount, ParsingByte.G_SENSOR_INT_BYTE, "int");
                byteCount += ParsingByte.GPS_INT_BYTE;
                int gSensorXDecimalData = (int)inputDataParse(clientData, byteCount, ParsingByte.G_SENSOR_DECIMAL_BYTE, "int");
                byteCount += ParsingByte.GPS_DECIMAL_BYTE;
                System.out.println("[Data] G Sensor X Data : " + gSensorXIntData + "." + gSensorXDecimalData);
                int gSensorYIntData = (int)inputDataParse(clientData, byteCount, ParsingByte.G_SENSOR_INT_BYTE, "int");
                byteCount += ParsingByte.GPS_INT_BYTE;
                int gSensorYDecimalData = (int)inputDataParse(clientData, byteCount, ParsingByte.G_SENSOR_DECIMAL_BYTE, "int");
                byteCount += ParsingByte.GPS_DECIMAL_BYTE;
                System.out.println("[Data] G Sensor Y Data : " + gSensorYIntData + "." + gSensorYDecimalData);
                int gSensorZIntData = (int)inputDataParse(clientData, byteCount, ParsingByte.G_SENSOR_INT_BYTE, "int");
                byteCount += ParsingByte.GPS_INT_BYTE;
                int gSensorZDecimalData = (int)inputDataParse(clientData, byteCount, ParsingByte.G_SENSOR_DECIMAL_BYTE, "int");
                byteCount += ParsingByte.GPS_DECIMAL_BYTE;
                System.out.println("[Data] G Sensor Z Data : " + gSensorZIntData + "." + gSensorZDecimalData);
                
                //Car Speed Time
                int carSpeedHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int carSpeedMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int carSpeedSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int carSpeedsMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] CarSpeed Time Data : " + carSpeedHourData + ":" + carSpeedMinuteData + ":" + carSpeedSecondData + "." + carSpeedsMilliSecondData);
                //Car Speed Data
                int carSpeedData = (int)inputDataParse(clientData, byteCount, ParsingByte.CAR_SPEED_BYTE, "int");
                byteCount += ParsingByte.CAR_SPEED_BYTE;
                System.out.println("[Data] CarSpeed Data : " + carSpeedData);
                
                //Car Pressure Time
                int carPressureHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int carPressureMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int carPressureSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int carPressureMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] CarPressure Time Data : " + carPressureHourData + ":" + carPressureMinuteData + ":" + carPressureSecondData + "." + carPressureMilliSecondData);
                //Car Pressure Data
                int carPressureData = (int)inputDataParse(clientData, byteCount, ParsingByte.CAR_PRESSURE_BYTE, "int");
                byteCount += ParsingByte.CAR_PRESSURE_BYTE;
                System.out.println("[Data] CarPressure Data : " + carPressureData);
                
                //Fuel Time
                int fuelHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int fuelMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int fuelSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int fuelMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Fuel Time Data : " + fuelHourData + ":" + fuelMinuteData + ":" + fuelSecondData + "." + fuelMilliSecondData);
                //Fuel Height Data
                int fuelHeightData = (int)inputDataParse(clientData, byteCount, ParsingByte.FUEL_HEIGHT_BYTE, "int");
                byteCount += ParsingByte.FUEL_HEIGHT_BYTE;
                System.out.println("[Data] Fuel Height Data : " + fuelHeightData);
                
                //Oil Time
                int oilHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int oilMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int oilSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int oilMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Oil Time Data : " + oilHourData + ":" + oilMinuteData + ":" + oilSecondData + "." + oilMilliSecondData);
                //Oil Data
                int oilData = (int)inputDataParse(clientData, byteCount, ParsingByte.OIL_BYTE, "int");
                byteCount += ParsingByte.OIL_BYTE;
                System.out.println("[Data] Oil Data : " + oilData);
                
                //GPS Count
                int gpsCountData = (int)inputDataParse(clientData, byteCount, ParsingByte.GPS_COUNT_BYTE, "int");
                byteCount += ParsingByte.GPS_COUNT_BYTE;
                System.out.println("[Data] GPS Count Data : " + gpsCountData);
                
                //Car Oxygen Time
                int oxygenHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int oxygenMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int oxygenSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int oxygenMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Car Oxygen Time Data : " + oxygenHourData + ":" + oxygenMinuteData + ":" + oxygenSecondData + "." + oxygenMilliSecondData);
                //Car Oxygen Data
                int oxygenData = (int)inputDataParse(clientData, byteCount, ParsingByte.CAR_OXYGEN_BYTE, "int");
                byteCount += ParsingByte.CAR_OXYGEN_BYTE;
                System.out.println("[Data] Car Oxygen Data : " + oxygenData);
                
                //Engine Next Time
                int engineHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int engineMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int engineSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int engineMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Engine Next Time Data : " + engineHourData + ":" + engineMinuteData + ":" + engineSecondData + "." + engineMilliSecondData);
                //Engine Next Data
                int engineData = (int)inputDataParse(clientData, byteCount, ParsingByte.ENGINE_NEXT_BYTE, "int");
                byteCount += ParsingByte.ENGINE_NEXT_BYTE;
                System.out.println("[Data] Engine Next Data : " + engineData);
                
                //Rotation Time Data
                int rotationHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int rotationMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int rotationSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int rotationMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Rotation Time Data : " + rotationHourData + ":" + rotationMinuteData + ":" + rotationSecondData + "." + rotationMilliSecondData);
                //Rotation Data
                int rotationData = (int)inputDataParse(clientData, byteCount, ParsingByte.ROTATION_BYTE, "int");
                byteCount += ParsingByte.ROTATION_BYTE;
                System.out.println("[Data] Rotation Data : " + rotationData);
                
                //Beacon Time Data
                int beaconHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int beaconMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int beaconSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int beaconMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Beacon Time Data : " + beaconHourData + ":" + beaconMinuteData + ":" + beaconSecondData + "." + beaconMilliSecondData);
                //Beacon Data
                int beaconUUIDData = (int)inputDataParse(clientData, byteCount, ParsingByte.BEACON_UUID_BYTE, "int");
                byteCount += ParsingByte.BEACON_UUID_BYTE;
                System.out.println("[Data] Beacon UUID Data : " + beaconUUIDData);
                int beaconMajorData = (int)inputDataParse(clientData, byteCount, ParsingByte.BEACON_MAJOR_BYTE, "int");
                byteCount += ParsingByte.BEACON_MAJOR_BYTE;
                System.out.println("[Data] Beacon Major Data : " + beaconMajorData);
                int beaconMinorData = (int)inputDataParse(clientData, byteCount, ParsingByte.BEACON_MINOR_BYTE, "int");
                byteCount += ParsingByte.BEACON_MINOR_BYTE;
                System.out.println("[Data] Beacon Minor Data : " + beaconMinorData);
                
                //Speaker Time Data
                int speakerHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int speakerMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int speakerSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int speakerMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Speaker Time Data : " + speakerHourData + ":" + speakerMinuteData + ":" + speakerSecondData + "." + speakerMilliSecondData);
                //Speaker Data
                String speakerData = (String)inputDataParse(clientData, byteCount, ParsingByte.SPEAKER_BYTE, "String");
                byteCount += ParsingByte.SPEAKER_BYTE;
                System.out.println("[Data] Speaker Data : " + speakerData);
                
                //IO Input Time Data
                int ioHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int ioMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int ioSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int ioMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] IO Input Time Data : " + ioHourData + ":" + ioMinuteData + ":" + ioSecondData + "." + ioMilliSecondData);
                //IO Input Data
                String ioData = (String)inputDataParse(clientData, byteCount, ParsingByte.IO_INPUT_BYTE, "String");
                byteCount += ParsingByte.IO_INPUT_BYTE;
                System.out.println("[Data] IO Input Data : " + ioData);
                
                //Image Time Data
                int imageHourData = (int)inputDataParse(clientData, byteCount, ParsingByte.HOUR_BYTE, "int");
                byteCount += ParsingByte.HOUR_BYTE;
                int imageMinuteData = (int)inputDataParse(clientData, byteCount, ParsingByte.MINUTE_BYTE, "int");
                byteCount += ParsingByte.MINUTE_BYTE;
                int imageSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.SECOND_BYTE, "int");
                byteCount += ParsingByte.SECOND_BYTE;
                int imageMilliSecondData = (int)inputDataParse(clientData, byteCount, ParsingByte.MILLISECOND_BYTE, "int");
                byteCount += ParsingByte.MILLISECOND_BYTE;
                System.out.println("[Data] Image Time Data : " + imageHourData + ":" + imageMinuteData + ":" + imageSecondData + "." + imageMilliSecondData);
                //Image Data
                String imageData = (String)inputDataParse(clientData, byteCount, ParsingByte.IMAGE_BYTE, "String");
                byteCount += ParsingByte.IMAGE_BYTE;
                System.out.println("[Data] Image Data : " + imageData);
                
                //Error Check Data
                String errorData = (String)inputDataParse(clientData, byteCount, ParsingByte.ERROR_CHECK_BYTE, "String");
                byteCount += ParsingByte.ERROR_CHECK_BYTE;
                System.out.println("[Data] Error Check Data : " + errorData);
                
                //ETX Data
                int etxData = (int)inputDataParse(clientData, byteCount, ParsingByte.CONTROL_BYTE, "int");
                byteCount += ParsingByte.CONTROL_BYTE;
                System.out.println("[Data] ETX Data : " + etxData);
                
            } catch(StringIndexOutOfBoundsException ex) {
                System.out.println("[Erro] Missing Data Transfer");
                break;
            } catch(NumberFormatException ex) {
                System.out.println("[Erro] Data Not Received Normally");
                break;
            }
        }

        //통신 종료하면서, 열었던 객체들을 모두 닫는다
        closeDataInputStream();
        closePrintWriter();
        closeSocket();
        System.out.println("[Info] Socket End Connection");
    }
}