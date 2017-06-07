var clickCount = 0;
var passengerSliderValue;
var temperatureSliderValue;
var passengerVal;
var mapContainer;
var map;
var clusterer;
var marker;
var infowindow;
var markers = [];
var passenger_num = new Array(23, 41, 88, 3, 62, 43, 55);
var positions = [{
        "lat": 35.147814,
        "lng": 129.034641,
        "store": '<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue0"></span>온도 : <span id="temperatureValue">31</span></div>'
    },
    {
        "lat": 35.157818,
        "lng": 129.058025,
        "store": '<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue1"></span>온도 : <span id="temperatureValue">36</span></div>'
    },
    {
        "lat": 35.163357,
        "lng": 129.063777,
        "store": '<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue2"></span>온도 : <span id="temperatureValue">18</span></div>'
    },
    {
        "lat": 35.173202,
        "lng": 129.071120,
        "store": '<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue3"></span>온도 : <span id="temperatureValue">5</span></div>'
    },
    {
        "lat": 35.186167,
        "lng": 129.081328,
        "store": '<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue4"></span>온도 : <span id="temperatureValue">11</span></div>'
    },
    {
        "lat": 35.209991,
        "lng": 129.078317,
        "store": '<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue5"></span>온도 : <span id="temperatureValue">21</span></div>'
    },
    {
        "lat": 35.155608,
        "lng": 129.041998,
        "store": '<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue6"></span>온도 : <span id="temperatureValue">32</span></div>'
    }
];

function init() {
    mapContainer = document.getElementById('map'), // 지도를 표시할 div
        mapOption = {
            center: new daum.maps.LatLng(35.144809, 129.034790), // 지도의 중심좌표
            level: 5 // 지도의 확대 레벨
        };
    map = new daum.maps.Map(mapContainer, mapOption); // 지도를 생성합니다

    // 마커 클러스터러를 생성합니다
    clusterer = new daum.maps.MarkerClusterer({
        map: map, // 마커들을 클러스터로 관리하고 표시할 지도 객체
        averageCenter: true, // 클러스터에 포함된 마커들의 평균 위치를 클러스터 마커 위치로 설정
        minLevel: 5 // 클러스터 할 최소 지도 레벨
    });

    for (var i = 0, len = positions.length; i < len; i++) {
        markers.push(addMarker(positions[i]));
    }

    function addMarker(position) {
        marker = new daum.maps.Marker({
            position: new daum.maps.LatLng(position.lat, position.lng)
        });

        infowindow = new daum.maps.InfoWindow({
            content: position.store // 인포윈도우에 표시할 내용
        });

        daum.maps.event.addListener(marker, 'mouseover', makeOverListener(map, marker, infowindow));
        daum.maps.event.addListener(marker, 'mouseout', makeOutListener(infowindow));

        return marker;
    };

    $('#110-1').click(function() {
        if (clickCount == 0) {
            clusterer.addMarkers(markers);
            clickCount = 1;

        } else {
            clusterer.clear();
            clickCount = 0;
        }
    })
    // 인포윈도우를 표시하는 클로저를 만드는 함수입니다
    function makeOverListener(map, marker, infowindow) {
        return function() {
            infowindow.open(map, marker);
            //승객 값

            for (var i = 0; i < passenger_num.length; i++) {
                $("#passengerValue" + i).text(passenger_num[i]);
            }
        };
    }

    // 인포윈도우를 닫는 클로저를 만드는 함수입니다
    function makeOutListener(infowindow) {
        return function() {
            infowindow.close();
        };
    }
}

function sensorSubmit() {
    //슬라이더 값
    passengerSliderValue = document.getElementById("passengerSlider").value;
    temperatureSliderValue = document.getElementById("temperatureSlider").value;
    clickCount = 1;

    for (var i = 0; i < passenger_num.length; i++) {
        if (passenger_num[i] <= passengerSliderValue) {
            clusterer.removeMarker(markers[i]);
        }
    }
}


$(document).ready(function() {
    $(".search").keyup(function () {
    var searchTerm = $(".search").val();
    var listItem = $('.results tbody').children('tr');
    var searchSplit = searchTerm.replace(/ /g, "'):containsi('")

    $.extend($.expr[':'], {'containsi': function(elem, i, match, array){
      return (elem.textContent || elem.innerText || '').toLowerCase().indexOf((match[3] || "").toLowerCase()) >= 0;
    }
    });

    $(".results tbody tr").not(":containsi('" + searchSplit + "')").each(function(e){
    $(this).attr('visible','false');
    });

    $(".results tbody tr:containsi('" + searchSplit + "')").each(function(e){
    $(this).attr('visible','true');
    });

    var jobCount = $('.results tbody tr[visible="true"]').length;
    $('.counter').text(jobCount + ' item');

    if(jobCount == '0') {$('.no-result').show();}
    else {$('.no-result').hide();}
        });
  });

function callBus(){
var busTag = document.getElementById("Bus");

var style = window.getComputedStyle(busTag);
var v = style.getPropertyValue("visibility");

if(v == "hidden")
  busTag.style.visibility = "visible";
else
  busTag.style.visibility = "hidden";

}
