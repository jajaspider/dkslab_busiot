#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import urllib.request
from xml.dom import minidom
import datetime
import cx_Oracle



def crolling():

    # 데이터베이스 연결
    conn = cx_Oracle.connect('iot915/dkslab915@113.198.235.247:1521/iotsen')
    cursor = conn.cursor()
    # 현재 시간 기록
    now_time = datetime.datetime.now()
    now_time = now_time.strftime('%Y%m%d%H%M%S')

    system_log(now_time, '[BusLocationSystem] Start Crolling')
    # url 접근
    apiurl = "http://61.43.246.153/openapi-data/service/busanBIMS/busStop?ServiceKey=4YstE1tC4r8vbbmmDCGqQ3P65YsFYZOPASjitkuyZUNfgwKG3gCy0QZpKfWzjIUKaZPYZOtCgfm7uPyxw5jcbA%3D%3D"
    dom = minidom.parse(urllib.request.urlopen(apiurl))
    system_log(now_time, '[BusLocationSystem] Url Connetion')
    # 파싱시작
    items = dom.getElementsByTagName("item")
    system_log(now_time, '[BusLocationSystem] Start Parse')
    print(now_time)
    print('---------------------')
    data_count =0
    for item in items:
        bStopID = ''
        bStopNM = ''
        gpsX = '0.0'
        gpsY = '0.0'
        for node in item.childNodes:
            if node.nodeName == "bstopId":
                system_log(now_time, '[BusLocationSystem] ' + node.childNodes[0].nodeValue + ' bstopId Find')
                location_log(now_time, node.childNodes[0].nodeValue)
                bStopID = node.childNodes[0].nodeValue
                print(node.childNodes[0].nodeValue)
            if node.nodeName == "bstopNm":
                system_log(now_time, '[BusLocationSystem] ' + node.childNodes[0].nodeValue + ' bstopNm Find')
                location_log(now_time, node.childNodes[0].nodeValue)
                bStopNM = node.childNodes[0].nodeValue
                print(node.childNodes[0].nodeValue)
            if node.nodeName == "gpsX":
                system_log(now_time, '[BusLocationSystem] ' + node.childNodes[0].nodeValue + ' gpsX Find')
                location_log(now_time, node.childNodes[0].nodeValue)
                gpsX = float(node.childNodes[0].nodeValue)
                print(node.childNodes[0].nodeValue)
            if node.nodeName == "gpsY":
                system_log(now_time, '[BusLocationSystem] ' + node.childNodes[0].nodeValue + ' gpsY Find')
                location_log(now_time, node.childNodes[0].nodeValue)
                gpsY = float(node.childNodes[0].nodeValue)
                print(node.childNodes[0].nodeValue)
                location_log(now_time, '---------------')
                print('---------------------')
        Parse_insert = "insert into bus_station values ('"+str(bStopID)+"','"+str(bStopNM)+"','"+str(gpsX)+"','"+str(gpsY)+"')"
        #print (Parse_insert)
        #Parse_insert = str(Parse_insert, "utf-8")
        Parse_insert = Parse_insert.encode(encoding='utf-8')
        cursor.execute(Parse_insert)
        conn.commit()
        data_count += 1
    print("data_count : "+str(data_count))
    conn.close()
    # time.sleep(90)
    # crolling()


# 로그 파일생성용 함수
def location_log(now_time, log_data):
    # 파라미터인 현재 시간 + 로그파일네임
    file_name = os.path.dirname(os.path.abspath(__file__)) + '\\log\\' + now_time + '_bus_location' + '.txt'
    # 이미존재하면 파일을 a모드로 오픈
    if os.path.exists(file_name):
        f = open(file_name, 'a')
    # 존재하지않으면 파일을 w모드로 오픈
    else:
        f = open(file_name, 'w')
    # 로그데이터기록
    f.write(log_data)
    f.write('\n')
    f.close()


def system_log(now_time, log_data):
    file_name = os.path.dirname(os.path.abspath(__file__)) + '\\log\\' + now_time + '_system_log' + '.txt'
    # 이미존재하면 파일을 a모드로 오픈
    if os.path.exists(file_name):
        f = open(file_name, 'a')
    # 존재하지않으면 파일을 w모드로 오픈
    else:
        f = open(file_name, 'w')
    # 로그데이터기록
    f.write(log_data)
    f.write('\n')
    f.close()


crolling()
