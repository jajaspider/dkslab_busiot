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
    
    private final static int GPS_BYTE          = 6;
    private final static int TIME_BYTE         = 2;
    private final static int TEMPERATURE_BYTE  = 2;
    private final static int HUMIDITY_BYTE     = 2;
    private final static int PASSENGERS_BYTE   = 2;
    private final static int PANIC_BUTTON_BYTE = 2;
    
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
    
    private String getClientData(String clientData, int startNumber, int bytes) {
        //readDataStream으로 읽어낸 데이터를 잘라내는 함수
        return new String(clientData.getBytes(), startNumber, bytes);
    }
    
    private Object inputDataParse(String clientData, int byteCount, int byteNumber, String dataType) {
        //readDataStream으로 읽어낸 데이터를 파싱하는 함수
        String data = getClientData(clientData, byteCount, byteNumber);
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
                                
                int hourData = (int)inputDataParse(clientData, byteCount, TIME_BYTE, "int");
                byteCount += TIME_BYTE;
                System.out.println("[Data] Hour Data : " + hourData);
                
                int minuteData = (int)inputDataParse(clientData, byteCount, TIME_BYTE, "int");
                byteCount += TIME_BYTE;
                System.out.println("[Data] Minute Data : " + minuteData);
                
                int secondData = (int)inputDataParse(clientData, byteCount, TIME_BYTE, "int");
                byteCount += TIME_BYTE;
                System.out.println("[Data] Second Data : " + secondData);
                
                int gpsXData = (int)inputDataParse(clientData, byteCount, GPS_BYTE, "int");
                byteCount += GPS_BYTE;
                System.out.println("[Data] GPS X Data : " + gpsXData);
                
                int gpsYData = (int)inputDataParse(clientData, byteCount, GPS_BYTE, "int");
                byteCount += GPS_BYTE;
                System.out.println("[Data] GPS Y Data : " + gpsYData);
                
                int temperatureData = (int)inputDataParse(clientData, byteCount, TEMPERATURE_BYTE, "int");
                byteCount += TEMPERATURE_BYTE;
                System.out.println("[Data] Temperature Data : " + temperatureData);
                
                int humidityData = (int)inputDataParse(clientData, byteCount, HUMIDITY_BYTE, "int");
                byteCount += HUMIDITY_BYTE;
                System.out.println("[Data] Humidity Data : " + humidityData);
                
                int passengersData = (int)inputDataParse(clientData, byteCount, PASSENGERS_BYTE, "int");
                byteCount += PASSENGERS_BYTE;
                System.out.println("[Data] Passengers Data : " + passengersData);
                
                String panicButtonData = (String)inputDataParse(clientData, byteCount, PANIC_BUTTON_BYTE, "String");
                byteCount += PANIC_BUTTON_BYTE;
                System.out.println("[Data] PanicButton Data : " + panicButtonData);
                
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