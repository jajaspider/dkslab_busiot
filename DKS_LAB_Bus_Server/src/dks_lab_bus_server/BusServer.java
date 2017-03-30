/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dks_lab_bus_server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;

/**
 *
 * @author Admit
 */
public class BusServer {
    private final static int SERVER_PORT = 29903;
    private ServerSocket server = null;
    
    public BusServer() {}
    
    public void startServerSocket() {
        System.out.println("[Info] Server Started");
        try {
            server = new ServerSocket(SERVER_PORT);
            Socket socket;
            //서버소켓에 연결되는 클라이언트가 있으면 소켓처리하는 쓰레드를 생성하고, 시작한다.
            while( (socket = server.accept()) != null) {                
                SocketThread sockThread = new SocketThread(socket);
                sockThread.start();
                System.out.println("[Info] Thread Create Complete");
            }
        }catch(SocketException se) {
            System.out.println("[Info] Server Shutdown Gracefully");
        }catch(IOException ioe) {
            System.out.println("[Erro] Socket Create Error");
        }
    }
    
    public void closeServerSocket() {
        try {
            server.close();
            System.out.println("[Info] ServerSocket Close Success");
        }catch(IOException ioe) {
            System.out.println("[Erro] ServerSocket Close Error");
        }
    }
}
