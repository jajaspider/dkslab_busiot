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
    
    public int getIntData(String data) {
        return Integer.parseInt(data, 16);
    }
    
    public String getStringData(String data) {
        int value = Integer.parseInt(data, 16);
        switch (value) {
            case 0:
                return "not pushed";
            case 1:
                return "pushed";
            default:
                return "error";
        }
    }
    
}
