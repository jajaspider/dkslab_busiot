/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dks_lab_bus_server;

/**
 *
 * @author Admit
 */
public class BusServerMain {
    
    public static void main(String[] args) {
        // TODO code application logic here
        BusServer server = new BusServer();
        Runtime.getRuntime().addShutdownHook(new Thread(){
            //서버가 강제종료 되는 경우 처리하는 쓰레드
            @Override
            public void run() {
                System.out.println("[Info] Program Shutdown Catch");
                server.closeServerSocket();
            }
        });
        server.startServerSocket();
    }
}
