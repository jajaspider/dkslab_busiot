<?php
$srv = '113.198.235.247';
$sid = 'iotsen';
$port = 1521;
$conn = oci_connect('iot915', 'dkslab915', "(DESCRIPTION =(ADDRESS = (PROTOCOL = tcp) (HOST = 113.198.235.247) (PORT = 1521))(CONNECT_DATA = (SID = iotsen)))",'AL32UTF8');
if (!$conn) {
    $e = oci_error();
    echo "An Error occured! " .  $e['message'] . "\n";
    exit(1);
}
?>
<?php
$sql = "select * from account";
$parse = oci_parse($conn, $sql);
oci_execute($parse);
$row = oci_fetch_array($parse,OCI_ASSOC);
$id = $row['ID'];
$pwd = $row['PASSWORD'];

$userid = $_POST['id'];
$userpwd = $_POST['pass'];
?>
<?php
$data_sql = "select GPSX, GPSY, BUSSPEED, USRCNT, ThermometerTemperature, HygrometerHumidity from sensordatainfo";
$data_parse = oci_parse($conn, $data_sql);
oci_execute($data_parse);
$data_row;
$gpsx=0;
$gpsy=0;
$busSpeed=0;
$usrcnt=0;
$thermometertemperature=0;
$hygrometerhumidity=0;
$passenger = "";
$i = 0;
?>
<?php
$BS_sql = "select BSTOPNM, GPSX, GPSY from bus_station";
$BS_parse = oci_parse($conn, $BS_sql);
oci_execute($BS_parse);
$BS_row;
$BS_gpsx=0;
$BS_gpsy=0;
$BS_name;
?>
<!DOCTYPE html>
<html lang="ko">
  <head>
        <?php
        $prevPage = $_SERVER["HTTP_REFERER"];
if($userid==$id&&$pwd==$userpwd){
    ?>
      <script> alert("로그인성공"); </script>
    <?php
      }
else{

  if($prevPage=="ids.deu.ac.kr"){

?>
<div class="modal-body">
  <script> alert("로그인성공"); </script>
</div>

<?php
  }
    ?>
    <p style="text-align:center;">
      <script> alert("로그인 실패"); </script>
    </p>
    <p style="text-align:center;"><a href="login.php">
        다시 로그인하기
    </a>
    </p>
	<script type="text/javascript">window.location.href="login.php"; </script>

<?php
}
?>


    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>DKS BUS IoT</title>
    <base href="http://ids.deu.ac.kr">

    <link href="./bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="./bootstrap-slider.min.css" rel="stylesheet">
    <link href="./iotbus.css" rel="stylesheet">
    <!-- jQuery (부트스트랩의 자바스크립트 플러그인을 위해 필요합니다) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <!-- 모든 컴파일된 플러그인을 포함합니다 (아래), 원하지 않는다면 필요한 각각의 파일을 포함하세요 -->
    <script src="./bootstrap/js/bootstrap.min.js"></script>
    <script src="./bootstrap-slider.min.js"></script>
    <!--<script src="./js/iotbus.js"></script>-->
    <script type="text/javascript" src="http://apis.daum.net/maps/maps3.js?apikey=f06db548c98701cea74fdd012ba4bbec&libraries=services,clusterer,drawing"></script>


    <script>
var clickCount = 0;
var busStopClick = 0;
var passengerSliderValue;
var temperatureSliderValue;
var passengerVal;
var mapContainer;
var map;
var clusterer;
var clusterer2;
var markers = [];
var markers2 = [];
  var busmarkers = [];

function init() {

var marker;
var infowindow;
var positions = [
  <?php
  while(null!=($data_row = oci_fetch_array($data_parse,OCI_ASSOC))){//DB테이블 행 하나씩 읽어서 값 가져오기
  $gpsx = $data_row['GPSX'];
  $gpsy = $data_row['GPSY'];
  $busSpeed = $data_row['BUSSPEED'];
  $usrcnt = (int)$data_row['USRCNT'];
  $thermometertemperature = $data_row['THERMOMETERTEMPERATURE'];
  $hygrometerhumidity = $data_row['HYGROMETERHUMIDITY'];
  if($i++ !=0){//자바스크립트로 넘겨주기 위해 하나의 스트링 데이터로 파싱한다. 조건문을 통해 첫 스트링에는 콤마 구분자를 넣지 않는다.
    $passenger.=",";
  }
  $passenger.="'".$usrcnt."'";//각데이터를 스트링 형태로 저장한다. 결과적으로 하나의 긴 스트링 데이터가 만들어진다.
  ?>
  {
      "lat": <?php echo $gpsx/1000000 ?>,
      "lng": <?php echo $gpsy/1000000 ?>,
      "store":
    '<table style="text-align: center;">'+
    '<thead>'+
    '<tr>'+
    '<td>'+
    '110-1 정보'+
    '</td>'+
    '</tr>'+
    '</thead>'+
    '<tbody>'+
    '<tr>'+
    '<td width="100" height="50" style="text-align: center;" >'+
    '<img src="/img/temparature.png" width="15" height="30">'+
    ' <?php echo $thermometertemperature ?>ºc'+
    '</td>'+
    '<td width="100" height="50">'+
    '<img src="/img/humidity.png" width="25" height="25">'+
    ' <?php echo $hygrometerhumidity ?>%'+
    '</td>'+
    '</tr>'+
    '<tr>'+
    '<td width="100" height="50">'+
    '<img src="/img/user_count.png" width="25" height="25">'+
    ' <?php echo $usrcnt ?>명'+
    '</td>'+
    '<td width="100" height="50">'+
    '<img src="/img/bus_speed.png" width="30" height="20">'+
    ' <?php echo $busSpeed ?>km/h'+
    '</td>'+
    '</tr>'+
    '</tbody>'+
    '</table>'
  },
  <?php
}
?>
];

    mapContainer = document.getElementById('map'), // 지도를 표시할 div
        mapOption = {
            center: new daum.maps.LatLng(35.144809, 129.034790), // 지도의 중심좌표
            level: 5 // 지도의 확대 레벨
        };
daum.maps.disableBusSymbol();
    map = new daum.maps.Map(mapContainer, mapOption); // 지도를 생성합니다
	var imageSrc = './img/BusIcon.png', // 마커이미지의 주소입니다
        imageSize = new daum.maps.Size(20, 25), // 마커이미지의 크기입니다
        imageOprion = {offset: new daum.maps.Point(27, 69)};
    var markerImage = new daum.maps.MarkerImage(imageSrc, imageSize, imageOprion);
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
            position: new daum.maps.LatLng(position.lat, position.lng),
image: markerImage // 마커이미지 설정
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

var passenger_num = new Array(<?php echo $passenger?>);//만들어진 긴 스트링 데이터를 그대로 출력하면 자바스트립트에서의 배열 생성시 초기 값들을 생성하듯이 생성 된다. 이 배열을 자바스크립트 변수로 사용할 수 있다.

function sensorSubmit() {
    //슬라이더 값
    passengerSliderValue = document.getElementById("passengerSlider").value;
    temperatureSliderValue = document.getElementById("temperatureSlider").value;
    clickCount = 1;

    for (var i = 0; i < passenger_num.length; i++) {
        if (parseInt(passenger_num[i]) >= passengerSliderValue) {
            clusterer.redraw();
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
var vbusTag;
var vsensorTag;

function callBus(){

  var busTag = document.getElementById("Bus");
  var style = window.getComputedStyle(busTag);
  vbusTag = style.getPropertyValue("visibility");

  if(vbusTag == "hidden"){
    busTag.style.visibility = "visible";
  }else{
    busTag.style.visibility = "hidden";
  }
}

function callSensor(){
var sensorTag = document.getElementById("Sensor");
  var style = window.getComputedStyle(sensorTag);
  vsensorTag = style.getPropertyValue("visibility");

  if(vsensorTag == "hidden"){
  document.getElementById("ac1").setAttribute('class', 'SliderVisible');
  document.getElementById("ac2").setAttribute('class', 'SliderVisible');
  document.getElementById("ac3").setAttribute('class', 'SliderVisible');
  document.getElementById("ac4").setAttribute('class', 'SliderVisible');
    sensorTag.style.visibility = "visible";
  }else{
    document.getElementById("ac1").setAttribute('class', 'SliderHidden');
    document.getElementById("ac2").setAttribute('class', 'SliderHidden');
    document.getElementById("ac3").setAttribute('class', 'SliderHidden');
    document.getElementById("ac4").setAttribute('class', 'SliderHidden');
    sensorTag.style.visibility = "hidden";

  }

}

function callBusStop(){
  var maker;
  var infowindow;
  if(busStopClick == 0){

    var positions = [
      <?php
      $count = 0;
      while(null!=($ch=($BS_row = oci_fetch_array($BS_parse,OCI_ASSOC)))){//DB테이블 행 하나씩 읽어서 값 가져오기
      $BS_name = $BS_row['BSTOPNM'];
      $BS_gpsx = $BS_row['GPSX'];
      $BS_gpsy = $BS_row['GPSY'];
      $count++;
      ?>
        {
            content: '<div><?php echo $BS_name ?></div>',
            latlng: new daum.maps.LatLng(<?php echo $BS_gpsy ?>, <?php echo $BS_gpsx ?>)
        }<?php if($count != 8760){ echo ",";}
       }
        ?>

    ];
    var imageSrc = './img/busStop.png', // 마커이미지의 주소입니다
        imageSize = new daum.maps.Size(20, 20), // 마커이미지의 크기입니다
        imageOprion = {offset: new daum.maps.Point(11, 20)}; // 마커이미지의 옵션입니다. 마커의 좌표와 일치시킬 이미지 안에서의 좌표를 설정합니다.
    var markerImage = new daum.maps.MarkerImage(imageSrc, imageSize, imageOprion);
    // 마커를 표시할 위치와 내용을 가지고 있는 객체 배열입니다
    clusterer2 = new daum.maps.MarkerClusterer({
        map: map, // 마커들을 클러스터로 관리하고 표시할 지도 객체
        averageCenter: true, // 클러스터에 포함된 마커들의 평균 위치를 클러스터 마커 위치로 설정
        minLevel: 3 // 클러스터 할 최소 지도 레벨
    });
    for (var i = 0, len = positions.length; i < len; i++) {
        markers2.push(addMarker(positions[i]));
    }
    function addMarker(position) {
        marker = new daum.maps.Marker({
            position: positions[i].latlng,
image: markerImage // 마커이미지 설정
        });

        infowindow = new daum.maps.InfoWindow({
            content: position.content // 인포윈도우에 표시할 내용
        });

        daum.maps.event.addListener(marker, 'mouseover', makeOverListener(map, marker, infowindow));
        daum.maps.event.addListener(marker, 'mouseout', makeOutListener(infowindow));

        return marker;
    };
clusterer2.addMarkers(markers2);
/*
    for (var i = 0; i < positions.length; i ++) {
        // 마커를 생성합니다
        marker = new daum.maps.Marker({
            map: map, // 마커를 표시할 지도
            position: positions[i].latlng, // 마커의 위치
            image: markerImage
        });
        busmarkers.push(marker);
        // 마커에 표시할 인포윈도우를 생성합니다
        var infowindow = new daum.maps.InfoWindow({
            content: positions[i].content // 인포윈도우에 표시할 내용
        });

        // 마커에 mouseover 이벤트와 mouseout 이벤트를 등록합니다
        // 이벤트 리스너로는 클로저를 만들어 등록합니다
        // for문에서 클로저를 만들어 주지 않으면 마지막 마커에만 이벤트가 등록됩니다
        daum.maps.event.addListener(marker, 'mouseover', makeOverListener(map, marker, infowindow));
        daum.maps.event.addListener(marker, 'mouseout', makeOutListener(infowindow));
    }

    // 인포윈도우를 표시하는 클로저를 만드는 함수입니다
    function makeOverListener(map, marker, infowindow) {
        return function() {
            infowindow.open(map, marker);
        };
    }

    // 인포윈도우를 닫는 클로저를 만드는 함수입니다
    function makeOutListener(infowindow) {
        return function() {
            infowindow.close();
        };
    }

  setMarkers(map);
  */

  busStopClick = 1;
  }
  else{
    //setMarkers(null);
    clusterer2.clear();
    busStopClick = 0;
  }

  // 인포윈도우를 표시하는 클로저를 만드는 함수입니다
  function makeOverListener(map, marker, infowindow) {
      return function() {
          infowindow.open(map, marker);
      };
  }

  // 인포윈도우를 닫는 클로저를 만드는 함수입니다
  function makeOutListener(infowindow) {
      return function() {
          infowindow.close();
      };
  }
}
/*
function setMarkers(map) {
    for (var i = 0; i < busmarkers.length; i++) {
        busmarkers[i].setMap(map);
    }
}*/

$(document).ready(function() {
    $("#passengerSlider").slider();
    $("#temperatureSlider").slider();
    $("#humiditySlider").slider();
    $("#carspeedSlider").slider();
});


    </script>

  </head>
  <body onload="init()">
<?php
$sql_b_bus = "select * from b_bus";
$parse_b_bus = oci_parse($conn, $sql_b_bus);
oci_execute($parse_b_bus);

/* 페이지 네이션 구현 할 때
$LIST_SIZE = 6;
$MORE_PAGE = 3;
$page = $_GET['page'] ? intval($_GET['page']) : 1;
$page_count = "select count(BUS_ID)/$LIST_SIZE FROM b_bus";
$parse_parse_count = oci_parse($conn, $page_count);
oci_execute($parse_parse_count);

$start_page = max($page - $MORE_PAGE, 1);
$end_page = min($page + $MORE_PAGE, $page_count);
$prev_page = max($start_page - $MORE_PAGE - 1, 1);
$next_page = min($end_page + $MORE_PAGE + 1, $page_count);

$offset = ( $page - 1 ) * $LIST_SIZE;

$sql_b_bus = "select * from b_bus where rownum >=$offset and rownum <=$LIST_SIZE";
$parse_b_bus = oci_parse($conn, $sql_b_bus);
oci_execute($parse_b_bus);
*/
//$b_bus_carno = $row_b_bus['CARNO'];
//$b_bus_busid = $row_b_bus['BUS_ID'];
?>
<div id="map"></div>
    <header>
      <nav class="menu">
       <input type="checkbox" href="#" class="menu-open" name="menu-open" id="menu-open" />
       <label class="menu-open-button" for="menu-open">
         <!--
        <span class="lines line-1"></span>
        <span class="lines line-2"></span>
        <span class="lines line-3"></span>
        -->
      <img src="img/Bus.png" width="50%" height="50%">
      </label>

       <a href="javascript:void(0);" onclick="callBus()" class="menu-item blue"> 버스 </a>
       <a href="javascript:void(0);" onclick="callSensor()" class="menu-item green"> 센서 </a>
       <a href="javascript:void(0);" onclick="callBusStop()" class="menu-item red"> 정류장 </a>
       <a href="javascript:void(0);" class="menu-item purple"> 장애인 </a>
       <a href="javascript:void(0);" class="menu-item orange"> 패닉 </a>
       <a href="javascript:void(0);" class="menu-item lightblue"> 통계 </a>
     </nav>
    </header>

    <section>

      <article>
        <div id="Bus" >
          <form class="searchform form-group pull-right">
            <input class="searchfield search form-control" type="text" value="Search..." onfocus="if (this.value == 'Search...') {this.value = '';}" onblur="if (this.value == '') {this.value = 'Search...';}" />
          </form>
              <table cellspacing='0' class="table table-hover table-bordered results">
                <thead>
                  <tr>
                    <th>버스 번호</th>
                    <th>출발 - 종착</th>
                    <th>버스 종류</th>
                  </tr>
                </thead><!-- Table Header -->

                  <tbody>
                    <tr>
                      <td><a href"javascript:void(0);" id="110-1">110-1</a></td>
                      <td>가야동 - 동래</td>
                      <td>일반</td>
                    </tr><!-- Table Row -->

                    <tr>
                      <td>11</td>
                      <td>다대포 - 영도</td>
                      <td>일반</td>
                    </tr><!-- Darker Table Row -->

                    <tr>
                      <td>23</td>
                      <td>용선 - 구포</td>
                      <td>마을</td>
                    </tr>

                    <tr>
                      <td>87</td>
                      <td>토곡 - 까치고개</td>
                      <td>일반</td>
                    </tr>

                    <tr>
                      <td>115</td>
                      <td>토곡 - 왕자맨션</td>
                      <td>마을</td>
                    </tr>

                    <tr>
                      <td>168</td>
                      <td>용당 - 녹산동신호민원센터</td>
                      <td>일반</td>
                    </tr>

                    <tr>
                      <td>203</td>
                      <td>죽전마을 - 온천장역</td>
                      <td>좌석</td>
                    </tr>

                  </tbody>
              </table>


            </div>

      </article>

      <article>
	        <div id="Sensor">
          <div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">
            <div class="panel panel-default">
              <div class="panel-heading" role="tab" id="headingOne">
                <h4 class="panel-title">
                  <a class="collapsed" data-toggle="collapse" data-parent="#accordion" href="#collapseOne" aria-expanded="false" aria-controls="collapseOne" >
                    승객 수
                  </a>
                </h4>
              </div>
              <div id="collapseOne" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingOne">
                <div class="panel-body">
                  <div class='slider' id="ac1">
                    <input id="passengerSlider" type="text" data-slider-min="0" data-slider-max="300" data-slider-step="1" data-slider-value="0"/>
                  </div>
                </div>
              </div>
            </div>
            <div class="panel panel-default">
              <div class="panel-heading" role="tab" id="headingTwo">
                <h4 class="panel-title">
                  <a class="collapsed" data-toggle="collapse" data-parent="#accordion" href="#collapseTwo" aria-expanded="false" aria-controls="collapseTwo">
                    온도
                  </a>
                </h4>
              </div>
              <div id="collapseTwo" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingTwo">
                <div class="panel-body">
                  <div class='slider' id="ac2">
                    <input id="temperatureSlider" type="text" data-slider-min="0" data-slider-max="300" data-slider-step="1" data-slider-value="0"/>
                  </div>
                </div>
              </div>
            </div>
            <div class="panel panel-default">
              <div class="panel-heading" role="tab" id="headingThree">
                <h4 class="panel-title">
                  <a class="collapsed" data-toggle="collapse" data-parent="#accordion" href="#collapseThree" aria-expanded="false" aria-controls="collapseThree">
                    습도
                  </a>
                </h4>
              </div>
              <div id="collapseThree" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingThree">
                <div class="panel-body">
                  <div class='slider' id="ac3">
                    <input id="humiditySlider" type="text" data-slider-min="0" data-slider-max="300" data-slider-step="1" data-slider-value="0"/>
                  </div>
                </div>
              </div>
            </div>
            <div class="panel panel-default">
              <div class="panel-heading" role="tab" id="headingFour">
                <h4 class="panel-title">
                  <a class="collapsed" data-toggle="collapse" data-parent="#accordion" href="#collapseFour" aria-expanded="false" aria-controls="collapseFour">
                    차량 속도
                  </a>
                </h4>
              </div>
              <div id="collapseFour" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingFour">
                <div class="panel-body">
                  <div class='slider' id="ac4">
                    <input id="carspeedSlider" type="text" data-slider-min="0" data-slider-max="300" data-slider-step="1" data-slider-value="0"/>
                  </div>
                </div>
              </div>
            </div>
          </div>
          <p><button type="button" class="btn btn-primary btn-block" id="sensorSubmitButton" onclick="sensorSubmit()">Submit</button></p>
        </div>
      </article>

    </section>

    <footer>

    </footer>

  </body>

</html>
