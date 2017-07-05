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
    <link href="css/iotbus.css" rel="stylesheet">
    <!-- jQuery (부트스트랩의 자바스크립트 플러그인을 위해 필요합니다) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <!-- 모든 컴파일된 플러그인을 포함합니다 (아래), 원하지 않는다면 필요한 각각의 파일을 포함하세요 -->
    <script src="./bootstrap/js/bootstrap.min.js"></script>
    <script src="./bootstrap-slider.min.js"></script>
    <script src="js/iotbus.js"></script>
    <script type="text/javascript" src="http://apis.daum.net/maps/maps3.js?apikey=f06db548c98701cea74fdd012ba4bbec&libraries=services,clusterer,drawing"></script>




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
       <a href="javascript:void(0);" class="menu-item green"> 센서 </a>
       <a href="javascript:void(0);" class="menu-item red"> <i class="fa fa-heart"></i> </a>
       <a href="javascript:void(0);" class="menu-item purple"> <i class="fa fa-microphone"></i> </a>
       <a href="javascript:void(0);" class="menu-item orange"> <i class="fa fa-star"></i> </a>
       <a href="javascript:void(0);" class="menu-item lightblue"> <i class="fa fa-diamond"></i> </a>
     </nav>
    </header>

    <section>

      <article>
        <div id="Bus">
          <div class="form-group pull-right">
            <input type="text" class="search form-control" placeholder="Search..">
          </div>
          <table cellspacing='0' class="table table-hover table-bordered results"> <!-- cellspacing='0' is important, must stay -->
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

      </article>

    </section>

    <footer>

    </footer>

  </body>

</html>
