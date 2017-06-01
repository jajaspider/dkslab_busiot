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
    <script src="./iotbus.js"></script>
    <script type="text/javascript" src="http://apis.daum.net/maps/maps3.js?apikey=b3138577083cb1fe9cd9d4d6474e2a8e&libraries=services,clusterer,drawing"></script>


    

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
    <!-- 목차 -->
    <nav id="menubar" class="navbar navbar-inverse navbar-static-top">
      <div class="collapse navbar-collapse">
        <ul class="nav navbar-nav">
          <li><a href="/main.php#busPanel">Bus</a></li>
          <li><a href="/main.php#sensorPanel">Sensor</a></li>
          <li>
            <a class="btn btn-default" href="#" role="button" data-toggle="modal" data-target="#Disabled" id="disabledButton">Panic</a>
            <!-- Modal -->
            <div class="modal fade" id="Disabled" tabindex="-1" role="dialog" aria-labelledby="DisabledLabel" aria-hidden="true">
              <div class="modal-dialog">
                <div class="modal-content">
                  <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                    <h4 class="modal-title" id="DisabledLabel">Panic</h4>
                  </div>
                  <div class="modal-body">
                    Main text...
                  </div>
                </div>
              </div>
            </div>
          </li>
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
                    Main text...
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
               <table>
                    <tr><td><button id="110-1"type="button" class="btn btn-default">110-1</button></td></tr>
                    <!--
                    <?php
                    /*
                    while($row_b_bus = oci_fetch_array($parse_b_bus,OCI_ASSOC)){
                       $busID = $row_b_bus['BUS_ID'];
                      echo "<tr><td>버스ID: " . $busID . "</td></tr>";
                      }
                    */
                      ?>-->

            </table>
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
