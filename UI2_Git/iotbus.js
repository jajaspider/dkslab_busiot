$('#busTab a').click(function (e) {
  e.preventDefault()
  $(this).tab('show')
})
$('#listTab a').click(function (e) {
  e.preventDefault()
  $(this).tab('show')
})
$(document).ready(function() {
    $("#passengerSlider").slider();
    $("#temperatureSlider").slider();
});


$('#Disabled').modal()

$('body').scrollspy({ target: '#menubar' })

/*
  var map;
  function init() {
    map = new daum.maps.Map(document.getElementById('map'), {
      center: new daum.maps.LatLng(35.144809, 129.034790),
      level: 5
    });
    // 일반 지도와 스카이뷰로 지도 타입을 전환할 수 있는 지도타입 컨트롤을 생성합니다
  var mapTypeControl = new daum.maps.MapTypeControl();

  // 지도에 컨트롤을 추가해야 지도위에 표시됩니다
  // daum.maps.ControlPosition은 컨트롤이 표시될 위치를 정의하는데 TOPRIGHT는 오른쪽 위를 의미합니다
  map.addControl(mapTypeControl, daum.maps.ControlPosition.TOPRIGHT);

  // 지도 확대 축소를 제어할 수 있는  줌 컨트롤을 생성합니다
  var zoomControl = new daum.maps.ZoomControl();
  map.addControl(zoomControl, daum.maps.ControlPosition.RIGHT);

  var imageSrc = 'http://t1.daumcdn.net/localimg/localimages/07/mapapidoc/marker_red.png', // 마커이미지의 주소입니다
  imageSize = new daum.maps.Size(24, 29), // 마커이미지의 크기입니다
  imageOption = {offset: new daum.maps.Point(27, 69)}; // 마커이미지의 옵션입니다. 마커의 좌표와 일치시킬 이미지 안에서의 좌표를 설정합니다.
  var markerImage = new daum.maps.MarkerImage(imageSrc, imageSize, imageOption);

  var clusterer = new daum.maps.MarkerClusterer({
    map: map, // 마커들을 클러스터로 관리하고 표시할 지도 객체
    averageCenter: true, // 클러스터에 포함된 마커들의 평균 위치를 클러스터 마커 위치로 설정
    minLevel: 7 // 클러스터 할 최소 지도 레벨
  });

  $('#110-1').on('click', function() {
    if ( $(this).prop('click') ) {
      // 데이터를 가져오기 위해 jQuery를 사용합니다
      // 데이터를 가져와 마커를 생성하고 클러스터러 객체에 넘겨줍니다
      $.get("wherebus.json", function(data) {
        // 데이터에서 좌표 값을 가지고 마커를 표시합니다
        // 마커 클러스터러로 관리할 마커 객체는 생성할 때 지도 객체를 설정하지 않습니다
        var markers = $(data.positions).map(function(i, position) {
          var maks =  new daum.maps.Marker({
            map: map,
            position : new daum.maps.LatLng(position.lat, position.lng),
            image: markerImage,
            clickable: true
        });
        maks.setMap(map);

        var iwContent = '<span style="color: black">Hello World!</span>', // 인포윈도우에 표출될 내용으로 HTML 문자열이나 document element가 가능합니다
            iwRemoveable = true; // removeable 속성을 ture 로 설정하면 인포윈도우를 닫을 수 있는 x버튼이 표시됩니다

        var infowindow = new daum.maps.InfoWindow({
          content : iwContent,
          removable : iwRemoveable
        });

        daum.maps.event.addListener(maks, "click", function() {
        infowindow.open(map, maks);
        });

        daum.maps.event.addListener(map, "click", function() {
        infowindow.close();
        });
        return maks;
      });

        // 클러스터러에 마커들을 추가합니다
        clusterer.addMarkers(markers);
      });
    } else {
      clusterer.clear();
    }
  });
  }

*/

  var clickCount = 0;
  var passengerSliderValue;
  var temperatureSliderValue;
  var passengerVal;
  var passenger_num = new Array(23, 41, 88, 3, 62, 43, 55);
  var mapContainer;
  var map;
  var clusterer;
  var markers = [];
  var positions = [
  {"lat":35.147814,"lng":129.034641,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue0"></span>온도 : <span id="temperatureValue">31</span></div>'},
  {"lat":35.157818,"lng":129.058025,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue1"></span>온도 : <span id="temperatureValue">36</span></div>'},
  {"lat":35.163357,"lng":129.063777,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue2"></span>온도 : <span id="temperatureValue">18</span></div>'},
  {"lat":35.173202,"lng":129.071120,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue3"></span>온도 : <span id="temperatureValue">5</span></div>'},
  {"lat":35.186167,"lng":129.081328,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue4"></span>온도 : <span id="temperatureValue">11</span></div>'},
  {"lat":35.209991,"lng":129.078317,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue5"></span>온도 : <span id="temperatureValue">21</span></div>'},
  {"lat":35.155608,"lng":129.041998,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue6"></span>온도 : <span id="temperatureValue">32</span></div>'}
  ];
  var marker;
  var infowindow;
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

  //var markers = [];
  /*
  var positions = [
  {"lat":35.147814,"lng":129.034641,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span name="passengerValue">23 </span>온도 : <span id="temperatureValue">31</span></div>'},
  {"lat":35.157818,"lng":129.058025,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span name="passengerValue">41 </span>온도 : <span id="temperatureValue">36</span></div>'},
  {"lat":35.163357,"lng":129.063777,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span name="passengerValue">88 </span>온도 : <span id="temperatureValue">18</span></div>'},
  {"lat":35.173202,"lng":129.071120,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span name="passengerValue">3 </span>온도 : <span id="temperatureValue">5</span></div>'},
  {"lat":35.186167,"lng":129.081328,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span name="passengerValue">62 </span>온도 : <span id="temperatureValue">11</span></div>'},
  {"lat":35.209991,"lng":129.078317,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span name="passengerValue">43 </span>온도 : <span id="temperatureValue">21</span></div>'},
  {"lat":35.155608,"lng":129.041998,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span name="passengerValue">55 </span>온도 : <span id="temperatureValue">32</span></div>'}
];
*/


/*
for(var i = 0; i< bus_num.length;i++)
{
  alert(bus_num[i]);
}
document.getElementById("#passengerValue0").innerHTML = bus_num[0];
document.getElementById("#passengerValue2").innerHTML = bus_num[2];
document.getElementById("#passengerValue1").innerHTML = bus_num[1];
document.getElementById("#passengerValue3").innerHTML = bus_num[3];
document.getElementById("#passengerValue4").innerHTML = bus_num[4];
document.getElementById("#passengerValue5").innerHTML = bus_num[5];
document.getElementById("#passengerValue6").innerHTML = bus_num[6];


var positions = [
{"lat":35.147814,"lng":129.034641,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue0"></span>온도 : <span id="temperatureValue">31</span></div>);'},
{"lat":35.157818,"lng":129.058025,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue1"></span>온도 : <span id="temperatureValue">36</span></div>'},
{"lat":35.163357,"lng":129.063777,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue2"></span>온도 : <span id="temperatureValue">18</span></div>'},
{"lat":35.173202,"lng":129.071120,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue3"></span>온도 : <span id="temperatureValue">5</span></div>'},
{"lat":35.186167,"lng":129.081328,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue4"></span>온도 : <span id="temperatureValue">11</span></div>'},
{"lat":35.209991,"lng":129.078317,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue5"></span>온도 : <span id="temperatureValue">21</span></div>'},
{"lat":35.155608,"lng":129.041998,"store":'<div>버스 번호 : <span id="bus_number">110-1 </span>승객 수 : <span id="passengerValue6"></span>온도 : <span id="temperatureValue">32</span></div>'}
];*/
  for (var i=0, len=positions.length; i<len; i++) {
    markers.push(addMarker(positions[i]));
   }

   function addMarker(position) {
     marker = new daum.maps.Marker({
       position : new daum.maps.LatLng(position.lat, position.lng)
     });

    infowindow = new daum.maps.InfoWindow({
      content: position.store // 인포윈도우에 표시할 내용
    });

      daum.maps.event.addListener(marker, 'mouseover', makeOverListener(map, marker, infowindow));
      daum.maps.event.addListener(marker, 'mouseout', makeOutListener(infowindow));

     return marker;
   };
   /*
   //버스 승객 수 온도 확인
   var passengerValueArray = document.getElementById("passengerValue");
   var passengerVal;
   for(var i in passengerValueArray)
   {
     passengerVal = passengerValueArray[i].value;
   }
   alert(passengerVal);
   */

  $('#110-1').click(function () {
    if(clickCount == 0){
    clusterer.addMarkers(markers);
    clickCount = 1;

    }
    else{
      clusterer.clear();
      clickCount = 0;
    }
  })
  // 인포윈도우를 표시하는 클로저를 만드는 함수입니다
  function makeOverListener(map, marker, infowindow) {
    return function() {
      infowindow.open(map, marker);
      //승객 값

      for(var i =0;i<passenger_num.length;i++){
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

  //  alert(passengerSliderValue);
  //  alert(temperatureSliderValue);
    for(var i =0; i<passenger_num.length;i++)
    {
      if(passenger_num[i] <= passengerSliderValue)
      {

        //markers[i].setMap(null); // 지도에서 제거한다.
        //clusterer.removeMarkers( markers );
        clusterer.removeMarker(markers[i]);
      }
    }
}
