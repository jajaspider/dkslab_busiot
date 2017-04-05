<?php
  $conn = mysqli_connect("localhost", "root", "qwerdf");
  if(mysqli_connect_errno($conn)){
  }else {

    mysqli_select_db($conn, "login");

    $sql1 = "SELECT * FROM login_t";
    $sql2 = "SELECT * FROM buslist"
    $result = $conn->query($sql1);
    $busresult = $conn->query($sql2);
    $busrow = mysqli_fetch_array($busresult);
    $row = mysqli_fetch_array($result);
    $busnum = $busrow['busnum'];
    $id = $row['id'];
    $pwd = $row['password'];

    $userid = $_POST['id'];
    $userpwd = $_POST['pass'];
  }
 ?>

<!DOCTYPE html>
<html lang="ko">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- 위 3개의 메타 태그는 *반드시* head 태그의 처음에 와야합니다; 어떤 다른 콘텐츠들은 반드시 이 태그들 *다음에* 와야 합니다 -->
    <title>BIMS(Bus Information Manager System)</title>
    <base href="http://ids.deu.ac.kr">
    <!-- 부트스트랩 -->

    <link href="style.css" rel="stylesheet">
    <link href="./bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="./bootstrap-slider.min.css" rel="stylesheet">
    <script src="./bootstrap/js/jquery-latest.min.js"></script>
    <!--<link href="bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="bootstrap/css/bootstrap-theme.min.css" rel="stylesheet">-->

    <!--<link href="style.css" rel="stylesheet">-->
    <!-- IE8 에서 HTML5 요소와 미디어 쿼리를 위한 HTML5 shim 와 Respond.js -->
    <!-- WARNING: Respond.js 는 당신이 file:// 을 통해 페이지를 볼 때는 동작하지 않습니다. -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body>
    <?php

     if($userid===$id && $userpwd===$pwd){
       mysqli_query($conn, "UPDATE login_t set only=1");
       echo "login success";
       echo $row[2];
     ?>
    <!--네비게이션 바-->
    <nav class="navbar navbar-default">
      <div class="container-fluid">
        <!--반응형 메뉴로 스크린이 작아지면 오른쪽 끝에 아이콘으로 메뉴가 바뀜-->
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand">BIMS(Bus Information Manager System)</a>
        </div><!--navbar-header end-->

        <div class="collapse navbar-collapse" id="navbar">
          <ul class="nav navbar-nav nav-tabs" rloe="tablist">
            <li role="presentation" class="active"><a href="#senser" aria-controls="senser" role="tab" data-toggle="tab">센서</a></li>
            <li role="presentation"><a href="#bus" aria-controls="bus" role="tab" data-toggle="tab">버스</a></li>
            <li role="presentation"><a href="#panic" aria-controls="panic" role="tab" data-toggle="tab">패닉</a></li>
          </ul>
          <ul class="nav navbar-nav navbar-right">
            <li><a href="logout.php">로그아웃</a></li>

          </ul>
        </div><!--collapse navbar-collapse end-->
      </div><!--container-fluid end-->
    </nav>

    <div class="conntainer">
      <div class="row">
        <div class="col-md-3">
          <div class="tab-content">
            <div role="tabpanel" class="tab-pane fade in active" id="senser">
              <div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">
                <div class="panel panel-default">
                <!-- Default panel contents -->
                  <div class="panel-heading " role="tab" id="headingOne">
                    <h4 class="panel-title">
                      <a data-toggle="collapse" data-parent="#accordion" href="#collapseOne" aria-expanded="true" aria-controls="collapseOne">승객 수</a>
                      <div class="material-switch pull-right">
                          <input id="passenger" name="passenger" type="checkbox"/>
                            <label for="passenger" class="label-success"></label>
                      </div>
                        </h4>
                  </div>
                  <div id="collapseOne" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingOne">
                    <!-- List group -->
                      <div class="examples">
                      	<div id="example-2" class='slider-example'>
                          <div class="well">
                            <input id="ex2" type="text" class="span2" value="" data-slider-min="1" data-slider-max="100" data-slider-step="1" data-slider-value="[1,100]"/>
                          </div>
                      </div>
                    </div>
                </div><!-- collapseOne end -->
              </div><!--panel end-->

              <div class="panel panel-default">
                    <!-- Default panel contents -->
                    <div class="panel-heading" role="tab" id="headingTwo">
                      <h4 class="panel-title">
                        <a data-toggle="collapse" data-parent="#accordion" href="#collapseTwo" aria-expanded="true" aria-controls="collapseTwo">온도</a>
                          <div class="material-switch pull-right">
                              <input id="temperature" name="temperature" type="checkbox">
                              <label for="temperature" class="label-info"></label>
                          </div>
                          </h4>
                    </div>
                    <!-- List group -->
                    <div id="collapseTwo" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingTwo">

                      <div class="examples">
                      	<div id="example-1" class='slider-example'>
                          <div class="well">
                            <input id="ex1" data-slider-id='ex1Slider' type="text" data-slider-min="-5" data-slider-max="20" data-slider-step="1" data-slider-value="14"/>
                          </div>
                      </div>
                    </div>

                </div><!--panel end-->
              </div><!-- collapseTwo end -->

              <div class="panel panel-default">
                    <!-- Default panel contents -->
                    <div class="panel-heading" role="tab" id="headingThr">
                      <h4 class="panel-title">
                        <a data-toggle="collapse" data-parent="#accordion" href="#collapseThr" aria-expanded="true" aria-controls="collapseThr">운행상태</a>
                          </h4>
                    </div>
                    <!-- List group -->
                    <div id="collapseThr" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingThr">
                    <ul class="list-group">
                       <li class="list-group-item">
                          좋음
                           <div class="material-switch pull-right">
                               <input id="status_3" name="status_3" type="checkbox"/>
                               <label for="status_3" class="label-success"></label>
                           </div>
                       </li>
                        <li class="list-group-item">
                            보통
                            <div class="material-switch pull-right">
                                <input id="status_2" name="status_2" type="checkbox"/>
                                <label for="status_2" class="label-warning"></label>
                            </div>
                        </li>
                        <li class="list-group-item">
                            불량
                            <div class="material-switch pull-right">
                                <input id="status_1" name="status_1" type="checkbox"/>
                                <label for="status_1" class="label-danger"></label>
                            </div>
                        </li>
                    </ul><!-- List group end -->
                </div><!--panel end-->
              </div><!-- collapseTwo end -->

              <div class="panel panel-default">
                    <!-- Default panel contents -->
                    <div class="panel-heading" role="tab" id="headingFour">
                      <h4 class="panel-title">
                        <a data-toggle="collapse" data-parent="#accordion" href="#collapseFour" aria-expanded="true" aria-controls="collapseFour">습도</a>
                          </h4>
                    </div>
                    <!-- List group -->
                    <div id="collapseFour" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingFour">
                    <ul class="list-group">
                        <li class="list-group-item">
                            30% 이하
                            <div class="material-switch pull-right">
                                <input id="humidity_1" name="humidity_1" type="checkbox">
                                <label for="humidity_1" class="label-info"></label>
                            </div>
                        </li>

                        <li class="list-group-item">
                            31% ~ 50%
                            <div class="material-switch pull-right">
                                <input id="humidity_2" name="humidity_2" type="checkbox"/>
                                <label for="humidity_2" class="label-success"></label>
                            </div>
                        </li>
                        <li class="list-group-item">
                            41% ~ 70%
                            <div class="material-switch pull-right">
                                <input id="humidity_3" name="humidity_3" type="checkbox"/>
                                <label for="humidity_3" class="label-warning"></label>
                            </div>
                        </li>

                        <li class="list-group-item">
                            71% 이상
                            <div class="material-switch pull-right">
                                <input id="humidity_4" name="humidity_4" type="checkbox"/>
                                <label for="humidity_4" class="label-danger"></label>
                            </div>
                        </li>
                    </ul><!-- List group end -->
                </div><!--panel end-->
              </div><!-- collapseTwo end -->

            </div><!--panel group end-->


            <button type="button" class="btn btn-primary btn-lg btn-block">확인</button>
                    <script>
                    $('#passenger_1').on('click', function() {
                      if ( $(this).prop('checked') ) {
                        alert("체크 성공");
                      } else {
                        alert("체크 해제");
                      }
                    });
                    $('#passenger_2').on('click', function() {
                      if ( $(this).prop('checked') ) {
                        alert("체크 성공");
                      } else {
                        alert("체크 해제");
                      }
                    });
                    $('#passenger_3').on('click', function() {
                      if ( $(this).prop('checked') ) {
                        alert("체크 성공");
                      } else {
                        alert("체크 해제");
                      }
                    });
                    </script>
            </div><!-- tabpanel end-->
            <div role="tabpanel" class="tab-pane fade" id="bus">
                <div class="panel panel-default">
                <!-- Default panel contents -->

                  <div class="panel-heading">
                    <form class="form-inline">
                    <div class="form-group">
		                    <input type="text" class="form-control" id="BusSearch" placeholder="Search">
		                </div>
		                 <button type="button" class="btn btn-default" style="padding-left: 12px; padding-right: 12px;">검색</button>
                     </form>
                   </div>
                  <div class="panel-body">
                    <?php echo $busrow[1]; ?>
                  </div>

                </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="panic">
              패닉 메뉴부분 입니다.

            </div>


          </div><!-- tab content end-->

        </div><!--col-md-3 end-->
        <div class="col-md-9">
                  <div id="map" style="width:100%;height:600px;"></div>
                  <script type="text/javascript" src="//apis.daum.net/maps/maps3.js?apikey=b3138577083cb1fe9cd9d4d6474e2a8e&libraries=services,clusterer,drawing"></script>
                  <script>
                  var mapContainer = document.getElementById('map'), // 지도를 표시할 div
                  mapOption = {
                    center: new daum.maps.LatLng(35.144809, 129.034790), // 지도의 중심좌표
                    level: 8 // 지도의 확대 레벨
                  };

                  // 지도를 표시할 div와  지도 옵션으로  지도를 생성합니다
                  var map = new daum.maps.Map(mapContainer, mapOption);
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

                    var iwContent = '<span style="color: black"><?php echo $row[0]; ?></span>', // 인포윈도우에 표출될 내용으로 HTML 문자열이나 document element가 가능합니다
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

                  </script>
        </div><!--col-md-9 end-->
      </div><!--row end-->
    </div><!--container end-->
    <?php
          }else {
            echo "login fail";
            echo $row[2];
            echo("<script>location.replace('login.php');</script>");
            }

     ?>
    <!-- jQuery (부트스트랩의 자바스크립트 플러그인을 위해 필요합니다) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <script src="https:////cdnjs.cloudflare.com/ajax/libs/jquery/2.2.4/jquery.min.js"></script>
    <!-- 모든 컴파일된 플러그인을 포함합니다 (아래), 원하지 않는다면 필요한 각각의 파일을 포함하세요 -->
    <script src="./bootstrap/js/bootstrap.min.js"></script>
    <script src="./bootstrap-slider.min.js"></script>

    <script type='text/javascript'>
  $(document).ready(function() {
    /* Example 1 */
    $('#ex1').slider({
          formatter: function(value) {
            return 'Current value: ' + value;
          }
      });

    /* Example 2 */
      $("#ex2").slider({});

      /* Example 3 */
      var RGBChange = function() {
        $('#RGB').css('background', 'rgb('+r.getValue()+','+g.getValue()+','+b.getValue()+')')
      };

      var r = $('#R').slider()
                .on('slide', RGBChange)
                .data('slider');
      var g = $('#G').slider()
                .on('slide', RGBChange)
                .data('slider');
      var b = $('#B').slider()
                .on('slide', RGBChange)
                .data('slider');

      /* Example 4 */
      $("#ex4").slider({
        reversed : true
      });

      /* Example 5 */
      $("#ex5").slider();
  $("#destroyEx5Slider").click(function() {
    $("#ex5").slider('destroy');
  });

  /* Example 6 */
  $("#ex6").slider();
  $("#ex6").on('slide', function(slideEvt) {
    $("#ex6SliderVal").text(slideEvt.value);
  });

  /* Example 7 */
  $("#ex7").slider();
  $("#ex7-enabled").click(function() {
    if(this.checked) {
      $("#ex7").slider("enable");
    }
    else {
      $("#ex7").slider("disable");
    }
  });

  /* Example 8 */
  $("#ex8").slider({
    tooltip: 'always'
  });

  /* Example 9 */
  $("#ex9").slider({
    precision: 2,
    value: 8.115
  });

      /* Example 10 */
      $("#ex10").slider({});

      /* Example 11 */
      $("#ex11").slider({
        step: 20000,
        min: 0,
        max: 200000
      });

  /* Example 12 */
  $("#ex12a").slider({
    id: "slider12a",
    min: 0,
    max: 10,
    value: 5
        });
  $("#ex12b").slider({
    id: "slider12b",
    min: 0,
    max: 10,
    range: true,
    value: [ 3, 7 ]
  });
  $("#ex12c").slider({
    id: "slider12c",
    min: 0,
    max: 10,
    range: true,
    value: [ 3, 7 ]
  });

  /* Example 13 */
  $("#ex13").slider({
    ticks: [0, 100, 200, 300, 400],
    ticks_labels: ['$0', '$100', '$200', '$300', '$400'],
    ticks_snap_bounds: 30,
    value: 200
  });

  /* Example 14 */
  $("#ex14").slider({
    ticks: [0, 100, 200, 300, 400],
    ticks_labels: ['$0', '$100', '$200', '$300', '$400'],
    ticks_positions: [0, 30, 70, 90, 100],
    ticks_snap_bounds: 20,
    value: 200,
    reversed: true
  });

  /* Example 15 */
  $("#ex15").slider({
    min: 10,
    max: 1000,
    scale: 'logarithmic',
    step: 10
  });

  /* Example 16 */
  $("#ex16a").slider({
    min  : 0,
    max  : 10,
    value: 0,
    focus: true
  });
  $("#ex16b").slider({
    min  : 0,
    max  : 10,
    value: [ 0, 10 ],
    focus: true
  });

  /* Example 17 */
  $("#ex17a").slider({
    min  : 0,
    max  : 10,
    value: 0,
    tooltip_position:'bottom'
  });
  $("#ex17b").slider({
    min  : 0,
    max  : 10,
    value: 0,
    orientation: 'vertical',
    tooltip_position:'left'
  });

  /* Example 18 */
  $('#ex18a').slider({
    min  : 0,
    max  : 10,
    value: 5,
    labelledby: 'ex18-label-1'
  });

  $('#ex18b').slider({
    min  : 0,
    max  : 10,
    value: [3, 6],
    labelledby: ['ex18-label-2a', 'ex18-label-2b']
  });

  $('#ex20a').on('click', function(e) {
    $('#ex20a')
      .parent()
      .find(' >.well')
      .toggle()
      .find('input')
      .slider('relayout');
    e.preventDefault();
  });

  /* Example 22 */
        $('#ex22').slider({});

  /* Example 23 */
        $('#ex23').slider({
    ticks: [0, 1, 2, 3, 4],
    ticks_positions: [0, 30, 70, 90, 100],
    formatter: function(value) {
      return 'Current value: ' + value;
    },
    step: 0.01,
    ticks_tooltip: true
  });
});
  /* example 24 */
  $('#ex24').slider({});
</script>
  </body>
  <footer>
  </footer>
</html>
