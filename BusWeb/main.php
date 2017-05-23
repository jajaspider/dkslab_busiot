<?php

$srv = '113.198.235.247';
$sid = 'iotsen';
$port = 1521;
$conn = oci_connect('iot915', 'dkslab915', "(DESCRIPTION =
                                                                  (ADDRESS = (PROTOCOL = tcp) (HOST = 113.198.235.247) (PORT = 1521))
                                                                  (CONNECT_DATA = (SID = iotsen))
                                                              )");

if (!$conn) {
    $e = oci_error();
    echo "An Error occured! " .  $e['message'] . "\n";
    exit(1);
}

$sql = "select * from account";

$parse = oci_parse($conn, $sql);
oci_execute($parse);
$row = oci_fetch_array($parse,OCI_ASSOC);
$id = $row['ID'];
$pwd = $row['PASSWORD'];

$userid = $_POST['id'];
$userpwd = $_POST['pass'];

?>

<!DOCTYPE html>
<html lang="ko">
  <head>
        <?php
        $prevPage = $_SERVER["HTTP_REFERER"];
if($userid==$id&&$pwd==$userpwd){
    ?>
    <div class="modal-body">
      로그인 성공
    </div>
    <?php
      }
else{

  if($prevPage=="ids.deu.ac.kr"){

?>
<div class="modal-body">
  로그인 성공
</div>

<?php
  }
    ?>
    <p style="text-align:center;">
      로그인 실패
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
    <!-- jQuery (부트스트랩의 자바스크립트 플러그인을 위해 필요합니다) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <!-- 모든 컴파일된 플러그인을 포함합니다 (아래), 원하지 않는다면 필요한 각각의 파일을 포함하세요 -->
    <script src="./bootstrap/js/bootstrap.min.js"></script>
    <script src="./bootstrap-slider.min.js"></script>
    <script type="text/javascript" src="//apis.daum.net/maps/maps3.js?apikey=b3138577083cb1fe9cd9d4d6474e2a8e" charset="utf-8"></script>
    <style>
    #map {
      position: relative;
      width: 100%;
      height: 700px;
    }
    #formSearch {
      position: absolute;
      top: 230px;
      left: 50px;
      z-index: 3;
    }
    #inputSearch {
      width: 230px;
    }
    #busPanel {
      position: absolute;
      top: 270px;
      left: 50px;
      z-index: 3;
      background-color: white;
      width: 300px;
      height: 400px;
    }
    #sensorPanel {
      position: absolute;
      top: 410px;
      left: 0px;
      z-index: 3;
      background-color: white;
      width: 300px;
      height: 150px;
    }
    #sensorSubmitButton {
      position: absolute;
      top : 150px;
    }
    .slider {
      text-align: center;
      margin-top: 10px;
      margin-bottom: 10px;
      width: 300px;
    }
    .jumbotron {
      color: #fff;
      height: 150px;
      background: linear-gradient( to right, #2e6da4, #5bc0de );
      margin-bottom: 0px;
    }
    #imgStyle {
      width : 50px;
      height: 50px;
    }
    #BIMS {
      color: #fff;
      font-style: italic;
      font-weight: bold;
      text-align: center;
    }
    .navbar {
      margin-bottom: 0px;
      height: 40px;
    }
    .navbar .navbar-nav {
      display: inline-block;
      float: none;
    }
    .navbar .navbar-collapse {
      text-align: center;
    }
    .nav li:hover:nth-child(8n+1), .nav li.active:nth-child(8n+1){
      border-bottom: #C4E17F 3px solid;
    }
    .nav li:hover:nth-child(8n+2), .nav li.active:nth-child(8n+2){
      border-bottom: #F7FDCA 3px solid;
    }
    .nav li:hover:nth-child(8n+3), .nav li.active:nth-child(8n+3){
      border-bottom: #FECF71 3px solid;
    }
    .nav li:hover:nth-child(8n+4), .nav li.active:nth-child(8n+4){
      border-bottom: #F0776C 3px solid;
    }
    .nav li:hover:nth-child(8n+5), .nav li.active:nth-child(8n+5){
      border-bottom: #DB9DBE 3px solid;
    }
    .nav li:hover:nth-child(8n+6), .nav li.active:nth-child(8n+6){
      border-bottom: #C49CDE 3px solid;
    }
    .nav li:hover:nth-child(8n+7), .nav li.active:nth-child(8n+7){
      border-bottom: #669AE1 3px solid;
    }
    .nav li:hover:nth-child(8n+8), .nav li.active:nth-child(8n+8){
      border-bottom: #62C2E4 3px solid;
    }
    #disabledButton {
      color: #9d9d9d;
      background-color: transparent;
      border-color: transparent;
      padding: 15px 15px;
      border: 0px;
      outline: 0;
    }
    </style>

    <script>
      $('#busTab a').click(function (e) {
        e.preventDefault()
        $(this).tab('show')
      })
      $('#listTab a').click(function (e) {
        e.preventDefault()
        $(this).tab('show')
      })
      $(document).ready(function() {
          $("#passengerSlider").slider({});
          $("#temperatureSlider").slider({});
          $("#humiditySlider").slider({});
      });
      $('#Disabled').modal()
    </script>


    <script type="text/javascript">
	var map;
    	function init() {
    		map = new daum.maps.Map(document.getElementById('map'), {
    			center: new daum.maps.LatLng(35.144809, 129.034790)
    		});
        // 일반 지도와 스카이뷰로 지도 타입을 전환할 수 있는 지도타입 컨트롤을 생성합니다
      var mapTypeControl = new daum.maps.MapTypeControl();

      // 지도에 컨트롤을 추가해야 지도위에 표시됩니다
      // daum.maps.ControlPosition은 컨트롤이 표시될 위치를 정의하는데 TOPRIGHT는 오른쪽 위를 의미합니다
      map.addControl(mapTypeControl, daum.maps.ControlPosition.TOPRIGHT);

      // 지도 확대 축소를 제어할 수 있는  줌 컨트롤을 생성합니다
      var zoomControl = new daum.maps.ZoomControl();
      map.addControl(zoomControl, daum.maps.ControlPosition.RIGHT);
    	}
    </script>

  </head>
  <body onload="init()">

    <!-- 목차 -->
    <nav class="navbar navbar-inverse navbar-static-top">
      <div class="collapse navbar-collapse">
        <ul class="nav navbar-nav">
          <li><a href="#">Bus</a></li>
          <li><a href="#">Sensor</a></li>
          <li><a href="#">Panic</a></li>
          <li>
            <a class="btn btn-default" href="#" role="button" data-toggle="modal" data-target="#Disabled" id="disabledButton">Disabled Reservations</a>
            <!-- Modal -->
            <div class="modal fade" id="Disabled" tabindex="-1" role="dialog" aria-labelledby="DisabledLabel" aria-hidden="true">
              <div class="modal-dialog">
                <div class="modal-content">
                  <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                    <h4 class="modal-title" id="DisabledLabel">Disabled Reservations</h4>
                  </div>
                  <div class="modal-body">
                    예약 데이터 없음
                  </div>
                </div>
              </div>
            </div>
          </li>
        </ul>
      </div>
    </nav>
    <!-- 머리말 -->
    <header>
      <div class="jumbotron">
        <img id="imgStyle" src="./Img/Bus.png" class="img-responsive center-block" alt="Not Img" />
        <p id="BIMS">
            Bus Information Management System
        </p>
      </div>
    </header>

    <!-- 내용 -->
    <section>
        <!-- 지도 -->
        <div id="map"></div>

        <!-- 검색 -->
        <div id="formSearch">
          <form class="form-inline">
            <div class="form-group">
              <label for="inputSearch" class="sr-only">Search</label>
              <input type="search" class="form-control" id="inputSearch" placeholder="Search...">
            </div>
            <button type="reset" class="btn btn-default">Search</button>
          </form>
        </div>

        <!-- 버스 값들 -->
        <div role="tabpanel" id="busPanel">
          <ul class="nav nav-tabs nav-justified" role="tablist" id="busTab">
            <li role="presentation" class="active"><a href="#busNum" aria-controls="busNum" role="tab" data-toggle="tab">Bus Number</a></li>
            <li role="presentation"><a href="#busStop" aria-controls="busStop" role="tab" data-toggle="tab">Bus Stop</a></li>
          </ul>

          <div class="tab-content">
            <div role="tabpanel" class="tab-pane fade in active" id="busNum">
              <p>Bus Number</p>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="busStop">
              <p>Bus Stop</p>
            </div>
          </div>

        <!-- 센서 값들 -->
        <div role="tabpanel" id="sensorPanel">
          <ul class="nav nav-tabs nav-justified" role="tablist" id="listTab">
            <li role="presentation" class="active"><a href="#Passenger" aria-controls="Passenger" role="tab" data-toggle="tab">Passenger</a></li>
            <li role="presentation"><a href="#Temperature" aria-controls="Temperature" role="tab" data-toggle="tab">Temperature</a></li>
            <li role="presentation"><a href="#State" aria-controls="State" role="tab" data-toggle="tab">State</a></li>
          </ul>

          <div class="tab-content">
            <div role="tabpanel" class="tab-pane fade in active" id="Passenger">
              <p>Passenger</p>
              <div class='slider'>
                  <input id="passengerSlider" type="text" class="span2" value="" data-slider-min="1" data-slider-max="100" data-slider-step="1" data-slider-value="[1,100]"/>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="Temperature">
              <p>Temperature</p>
              <div class='slider'>
                  <input id="temperatureSlider" type="text" class="span2" value="" data-slider-min="1" data-slider-max="100" data-slider-step="1" data-slider-value="[1,100]"/>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="State">
              <p>State</p>

              <div class='slider'>
                  <input id="statusSlider" type="text"
                  data-provide="slider"
                  data-slider-ticks="[1, 2, 3]"
                  data-slider-ticks-labels='["Bad", "Normal", "Good"]'
                  data-slider-min="1"
                  data-slider-max="3"
                  data-slider-step="1"
                  data-slider-value="3"
                  data-slider-tooltip="hide"
                  />
              </div>
          </div>
          </div>
          <p><button type="button" class="btn btn-primary btn-block" id="sensorSubmitButton">Submit</button></p>
        </div>

    </section>
    <!-- 표 -->
    <article>

    </article>
    <!-- 꼬리말 -->
    <footer>

    </footer>

  </body>
</html>
