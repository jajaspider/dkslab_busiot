/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dks_lab_bus_server;

import java.sql.*;
/**
 *
 * @author Admit
 */
public class BusDBService {
    //소켓 쓰레드에서 사용하는 DB 객체
    private final static String DBID        = "busadmin";
    private final static String DBPW        = "bussystem";
    private final static String DBURL       = "jdbc:mysql://113.198.236.96:3306/bus?characterEncoding=utf8&autoReconnect=true&useSSL=false";
    
    private Connection conn = null; //DB Connect
    private Statement  stmt = null; //DB Working
    
    public String dataInsert(String carNumber, String time, String code, String data) {
        try {
            conn = DriverManager.getConnection(DBURL, DBID, DBPW);
            System.out.println("[Info] Database Access Success");
            stmt = conn.createStatement();
            
            StringBuilder builder = new StringBuilder();
            builder.append("insert into data values(null,'");
            builder.append(carNumber); builder.append("','");
            builder.append(time); builder.append("','");
            builder.append(code); builder.append("','");
            builder.append(data); builder.append("');");
            
            int result = stmt.executeUpdate(builder.toString());
            if(result == 1) { //변경된 행이 하나인 경우(insert 결과)
                System.out.println("[Info] Data Entry Complete");
                return "Success";
            }else {
                System.out.println("[Info] Data Entry Failed");
                return "Failed";
            }
        } catch (SQLException sqle) {
            System.out.println("[Erro] Database Connection Error");
            return "Failed";
        } finally {
            if(stmt!=null){try{stmt.close();}catch(SQLException sqle){System.out.println("[Erro] Statement Shutdown Error");}}
            if(conn!=null){try{conn.close();}catch(SQLException sqle){System.out.println("[Erro] Connection Shutdown Error");}}
        }
    }
}
