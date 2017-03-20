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
    
    private final static int GPS_BYTE         = 6;
    private final static int TIME_BYTE        = 2;
    private final static int TEMPERATURE_BYTE = 2;
    private final static int HUMIDITY_BYTE    = 2;
    private final static int PASSENGERS_BYTE  = 2;
    
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
    
    private String getClientData(String clientData, int startNumber, int bytes) {
        return new String(clientData.getBytes(), startNumber, bytes);
    }
    
    private String readDataStream() {
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
    
    @Override
    public void run() {
        if(dIStream == null) { createDataInputStream(); }
        if(writer == null) { createPrintWriter(); }
        if(dbService == null) { dbService = new BusDBService(); }
        if(busClientData == null) { busClientData = new BusClientData(); }
        
//        String str;
//        while( (str = readStreamData()) != null ) {
//            //데이터 분류 후 DB입력
//            if(str.equals("")) { break; }
//            System.out.println("[Info] Input Data : " + str);
//            String[] values = dataClassification(str);
//            try{
//                String result = dbService.dataInsert(values[0], values[1], values[2], values[3]);
//                writer.print(result);
//                writer.flush();
//            }catch(ArrayIndexOutOfBoundsException aioe) {
//                System.out.println("[Erro] Input Data Error");
//                break;
//            }
//        }

        String clientData;
        while( (clientData = readDataStream()) != null ) {
            if(clientData.equals("")) { break; }
            System.out.println("[Info] Input Data : " + clientData);
            String gps_x = getClientData(clientData, 0, GPS_BYTE);
            int gpsXData = busClientData.getIntData(gps_x);
            System.out.println("GPS X -> " + gpsXData);
            String gps_y = getClientData(clientData, 6, GPS_BYTE);
            int gpsYData = busClientData.getIntData(gps_y);
            System.out.println("GPS Y -> " + gpsYData);
            String hour = getClientData(clientData, 12, TIME_BYTE);
            int hourData = busClientData.getIntData(hour);
            System.out.println("Hour -> " + hourData);
            String minute = getClientData(clientData, 14, TIME_BYTE);
            int minuteData = busClientData.getIntData(minute);
            System.out.println("Minute -> " + minuteData);
            String second = getClientData(clientData, 16, TIME_BYTE);
            int secondData = busClientData.getIntData(second);
            System.out.println("Second -> " + secondData);
            String temperature = getClientData(clientData, 18, TEMPERATURE_BYTE);
            int temperatureData = busClientData.getIntData(temperature);
            System.out.println("Temperature -> " + temperatureData);
            String humidity = getClientData(clientData, 20, HUMIDITY_BYTE);
            int humidityData = busClientData.getIntData(humidity);
            System.out.println("Humidity -> " + humidityData);
            String passengers = getClientData(clientData, 22, PASSENGERS_BYTE);
            int passengersData = busClientData.getIntData(passengers);
            System.out.println("Passengers -> " + passengersData);
        }

        closeDataInputStream();
        closePrintWriter();
        closeSocket();
        System.out.println("[Info] Socket End Connection");
    }
}