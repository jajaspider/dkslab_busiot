/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dks_lab_bus_server;

/**
 *
 * @author 915lab
 */
public class BusClientData {
    
    public int getIntData(String gpsData) {
        return Integer.parseInt(gpsData, 16);
    }
    
}
