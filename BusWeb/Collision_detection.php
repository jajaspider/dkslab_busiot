<?php
  $conn = mysqli_connect("localhost", "root", "hoyoung");
  if(mysqli_connect_errno($conn)){
  }else {
      mysqli_select_db($conn, "collision_detection");
      $cn = array('0','1','2','3','4','5','6','7','8','9');
      $randcn1 = rand(0,count($cn)-1);
      $randcn2 = rand(0,count($cn)-1);
      $randcn3 = rand(0,count($cn)-1);
      $randcn4 = rand(0,count($cn)-1);
      $randcn5 = rand(0,count($cn)-1);
      $randcn6 = rand(0,count($cn)-1);
      $randcn7 = rand(0,count($cn)-1);
      $randcn8 = rand(0,count($cn)-1);
      $randcn9 = rand(0,count($cn)-1);
      $cn1 = array('가','나','다','라','마','구','아','서','감');
      $randcns1 = rand(0,count($cn1)-1);
      $lo1 = array('중구','진구', '서구', '남구', '북구', '동구' ,'해운대구', '사하구');
      $randlo1 = rand(0,count($lo1)-1);
      $lo2 = array('가야동', '범일동', '연산동', '개금동', '범천동', '대연동', '용호동', '반여동', '수영동', '광안동');
      $randlo2 = rand(0,count($lo2)-1);
      $st = array('단독사고', '전복사고', '추돌사고', '추락사고');
      $randst = rand(0,count($st)-1);
      $sql = "INSERT INTO detection_tb (bus_num, bus_plate ,location, status , times)
        VALUES ('$cn[$randcn7]$cn[$randcn8]$cn[$randcn9]',
          '$cn[$randcn1]$cn[$randcn2]$cn1[$randcns1]$cn[$randcn3]$cn[$randcn4]$cn[$randcn5]$cn[$randcn6]',
           '부산시 $lo1[$randlo1] $lo2[$randlo2]',
           '$st[$randst]',
            now())";
            if ($conn->query($sql) === TRUE) {
              echo "New record created successfully";
              } else {
                echo "Error: " . $sql . "<br>" . $conn->error;
            }
      $sql1 = "SELECT * FROM detection_tb";
      $result = $conn->query($sql1);


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

    <!-- 부트스트랩 -->
    <link href="http://113.130.158.195:3306/bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="http://113.130.158.195:3306/bootstrap/css/bootstrap-theme.min.css" rel="stylesheet">
    <link href="http://113.130.158.195:3306/style.css" rel="stylesheet">
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <!-- IE8 에서 HTML5 요소와 미디어 쿼리를 위한 HTML5 shim 와 Respond.js -->
    <!-- WARNING: Respond.js 는 당신이 file:// 을 통해 페이지를 볼 때는 동작하지 않습니다. -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body>
    <nav class="navbar navbar-inverse navbar-fixed-top" style="margin-bottom: 10px;">
      <div class="container-fluid" >
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="http://113.130.158.195:3306/index.html">BIMS(Bus Information Manager System)</a>
        </div>
        <div id="navbar" class="navbar-collapse collapse">
          <form class="navbar-form navbar-right">
            <div class="form-group">
            <input type="text" class="form-control" placeholder="Search.." />
            </div>
            <button type="submit" class="btn btn-default">Search</button>
          </form>
          <ul class="nav navbar-nav navbar-right">
            <li class="dropdown">
                <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false">Menu<span class="caret"></span></a>
                <ul class="dropdown-menu" role="menu">
                  <li><a href="http://113.130.158.195:3306/Number_of_vehicle_passengers.php">Number of vehicle passengers</a></li>
                  <li><a href="http://113.130.158.195:3306/Check_internal_temperature.php">Check internal temperature</a></li>
                  <li class="divider"></li>
                  <li><a href="http://113.130.158.195:3306/Illegal_parking_enforcement.php">Illegal parking enforcement</a></li>
                  <li><a href="http://113.130.158.195:3306/Operation_violation_monitoring.php">Operation violation monitoring</a></li>
                  <li><a href="http://113.130.158.195:3306/Collision_detection.php">Collision detection</a></li>
                  <li><a href="http://113.130.158.195:3306/Surveillance_status_monitoring.php">Surveillance status monitoring</a></li>
                </ul>
              </li>
              <script>$('.dropdown-toggle').dropdown()</script>
            <li><a href="http://113.130.158.195:3306/index.html">Home</a></li>
            <li><a href="http://113.130.158.195:3306/sign_in.php">Login</a></li>
            <li><a href="http://113.130.158.195:3306/sign_up.php">Sign up</a></li>
          </ul>
        </div>
      </div>
    </nav>

    <div class="container-fluid">
     <div class="row">
        <h2>추돌사고 모니터링</h2>
         <div id="chart_div" style="width: 800px; height: 600px; margin: auto;">
           <?php
             $cvar1_1 = "SELECT COUNT(if(location LIKE '%중구%' AND status= '단독사고', location AND status, NULL)) FROM detection_tb";
             $cvar1_2 = "SELECT COUNT(if(location LIKE '%중구%' AND status= '전복사고', location AND status, NULL)) FROM detection_tb";
             $cvar1_3 = "SELECT COUNT(if(location LIKE '%중구%' AND status= '추돌사고', location AND status, NULL)) FROM detection_tb";
             $cvar1_4 = "SELECT COUNT(if(location LIKE '%중구%' AND status= '추락사고', location AND status, NULL)) FROM detection_tb";
             $cvar2_1 = "SELECT COUNT(if(location LIKE '%진구%' AND status= '단독사고', location AND status, NULL)) FROM detection_tb";
             $cvar2_2 = "SELECT COUNT(if(location LIKE '%진구%' AND status= '전복사고', location AND status, NULL)) FROM detection_tb";
             $cvar2_3 = "SELECT COUNT(if(location LIKE '%진구%' AND status= '추돌사고', location AND status, NULL)) FROM detection_tb";
             $cvar2_4 = "SELECT COUNT(if(location LIKE '%진구%' AND status= '추락사고', location AND status, NULL)) FROM detection_tb";
             $cvar3_1 = "SELECT COUNT(if(location LIKE '%서구%' AND status= '단독사고', location AND status, NULL)) FROM detection_tb";
             $cvar3_2 = "SELECT COUNT(if(location LIKE '%서구%' AND status= '전복사고', location AND status, NULL)) FROM detection_tb";
             $cvar3_3 = "SELECT COUNT(if(location LIKE '%서구%' AND status= '추돌사고', location AND status, NULL)) FROM detection_tb";
             $cvar3_4 = "SELECT COUNT(if(location LIKE '%서구%' AND status= '추락사고', location AND status, NULL)) FROM detection_tb";
             $cvar4_1 = "SELECT COUNT(if(location LIKE '%남구%' AND status= '단독사고', location AND status, NULL)) FROM detection_tb";
             $cvar4_2 = "SELECT COUNT(if(location LIKE '%남구%' AND status= '전복사고', location AND status, NULL)) FROM detection_tb";
             $cvar4_3 = "SELECT COUNT(if(location LIKE '%남구%' AND status= '추돌사고', location AND status, NULL)) FROM detection_tb";
             $cvar4_4 = "SELECT COUNT(if(location LIKE '%남구%' AND status= '추락사고', location AND status, NULL)) FROM detection_tb";
             $cvar5_1 = "SELECT COUNT(if(location LIKE '%북구%' AND status= '단독사고', location AND status, NULL)) FROM detection_tb";
             $cvar5_2 = "SELECT COUNT(if(location LIKE '%북구%' AND status= '전복사고', location AND status, NULL)) FROM detection_tb";
             $cvar5_3 = "SELECT COUNT(if(location LIKE '%북구%' AND status= '추돌사고', location AND status, NULL)) FROM detection_tb";
             $cvar5_4 = "SELECT COUNT(if(location LIKE '%북구%' AND status= '추락사고', location AND status, NULL)) FROM detection_tb";
             $cvar6_1 = "SELECT COUNT(if(location LIKE '%동구%' AND status= '단독사고', location AND status, NULL)) FROM detection_tb";
             $cvar6_2 = "SELECT COUNT(if(location LIKE '%동구%' AND status= '전복사고', location AND status, NULL)) FROM detection_tb";
             $cvar6_3 = "SELECT COUNT(if(location LIKE '%동구%' AND status= '추돌사고', location AND status, NULL)) FROM detection_tb";
             $cvar6_4 = "SELECT COUNT(if(location LIKE '%동구%' AND status= '추락사고', location AND status, NULL)) FROM detection_tb";
             $cvar7_1 = "SELECT COUNT(if(location LIKE '%해운대구%' AND status= '단독사고', location AND status, NULL)) FROM detection_tb";
             $cvar7_2 = "SELECT COUNT(if(location LIKE '%해운대구%' AND status= '전복사고', location AND status, NULL)) FROM detection_tb";
             $cvar7_3 = "SELECT COUNT(if(location LIKE '%해운대구%' AND status= '추돌사고', location AND status, NULL)) FROM detection_tb";
             $cvar7_4 = "SELECT COUNT(if(location LIKE '%해운대구%' AND status= '추락사고', location AND status, NULL)) FROM detection_tb";
             $cvar8_1 = "SELECT COUNT(if(location LIKE '%사하구%' AND status= '단독사고', location AND status, NULL)) FROM detection_tb";
             $cvar8_2 = "SELECT COUNT(if(location LIKE '%사하구%' AND status= '전복사고', location AND status, NULL)) FROM detection_tb";
             $cvar8_3 = "SELECT COUNT(if(location LIKE '%사하구%' AND status= '추돌사고', location AND status, NULL)) FROM detection_tb";
             $cvar8_4 = "SELECT COUNT(if(location LIKE '%사하구%' AND status= '추락사고', location AND status, NULL)) FROM detection_tb";
            ?>
         <script type='text/javascript'>
         google.charts.load('current', {'packages':['corechart']});
         google.charts.setOnLoadCallback(drawVisualization);
          function drawVisualization() {
            // Some raw data (not necessarily accurate)
            var data = google.visualization.arrayToDataTable([
             ['종류', '중구', '진구', '서구', '남구', '북구', '동구', '해운대구', '사하구'],
             ['단독사고',  <?php $res = mysqli_query($conn, $cvar1_1);
                                   while($row = mysqli_fetch_array($res)){
                                     echo $row[0];
                                   }
                                   ?>,      <?php $res = mysqli_query($conn, $cvar2_1);
                                                         while($row = mysqli_fetch_array($res)){
                                                           echo $row[0];
                                                         }
                                                         ?>,         <?php $res = mysqli_query($conn, $cvar3_1);
                                                                               while($row = mysqli_fetch_array($res)){
                                                                                 echo $row[0];
                                                                               }
                                                                               ?>,             <?php $res = mysqli_query($conn, $cvar4_1);
                                                                                                     while($row = mysqli_fetch_array($res)){
                                                                                                       echo $row[0];
                                                                                                     }
                                                                                                     ?>,           <?php $res = mysqli_query($conn, $cvar5_1);
                                                                                                                           while($row = mysqli_fetch_array($res)){
                                                                                                                             echo $row[0];
                                                                                                                           }
                                                                                                                           ?>,      <?php $res = mysqli_query($conn, $cvar6_1);
                                                                                                                                                 while($row = mysqli_fetch_array($res)){
                                                                                                                                                   echo $row[0];
                                                                                                                                                 }
                                                                                                                                                 ?>,      <?php $res = mysqli_query($conn, $cvar7_1);
                                                                                                                                                                       while($row = mysqli_fetch_array($res)){
                                                                                                                                                                         echo $row[0];
                                                                                                                                                                       }
                                                                                                                                                                       ?>,      <?php $res = mysqli_query($conn, $cvar8_1);
                                                                                                                                                                                             while($row = mysqli_fetch_array($res)){
                                                                                                                                                                                               echo $row[0];
                                                                                                                                                                                             }
                                                                                                                                                                                             ?>],
             ['전복사고',  <?php $res = mysqli_query($conn, $cvar1_2);
                                   while($row = mysqli_fetch_array($res)){
                                     echo $row[0];
                                   }
                                   ?>,      <?php $res = mysqli_query($conn, $cvar2_2);
                                                         while($row = mysqli_fetch_array($res)){
                                                           echo $row[0];
                                                         }
                                                         ?>,        <?php $res = mysqli_query($conn, $cvar3_2);
                                                                               while($row = mysqli_fetch_array($res)){
                                                                                 echo $row[0];
                                                                               }
                                                                               ?>,             <?php $res = mysqli_query($conn, $cvar4_2);
                                                                                                     while($row = mysqli_fetch_array($res)){
                                                                                                       echo $row[0];
                                                                                                     }
                                                                                                     ?>,          <?php $res = mysqli_query($conn, $cvar5_2);
                                                                                                                           while($row = mysqli_fetch_array($res)){
                                                                                                                             echo $row[0];
                                                                                                                           }
                                                                                                                           ?>,      <?php $res = mysqli_query($conn, $cvar6_2);
                                                                                                                                                 while($row = mysqli_fetch_array($res)){
                                                                                                                                                   echo $row[0];
                                                                                                                                                 }
                                                                                                                                                 ?>,        <?php $res = mysqli_query($conn, $cvar7_2);
                                                                                                                                                                       while($row = mysqli_fetch_array($res)){
                                                                                                                                                                         echo $row[0];
                                                                                                                                                                       }
                                                                                                                                                                       ?>,      <?php $res = mysqli_query($conn, $cvar8_2);
                                                                                                                                                                                             while($row = mysqli_fetch_array($res)){
                                                                                                                                                                                               echo $row[0];
                                                                                                                                                                                             }
                                                                                                                                                                                             ?>],
             ['추돌사고',  <?php $res = mysqli_query($conn, $cvar1_3);
                                   while($row = mysqli_fetch_array($res)){
                                     echo $row[0];
                                   }
                                   ?>,      <?php $res = mysqli_query($conn, $cvar2_3);
                                                         while($row = mysqli_fetch_array($res)){
                                                           echo $row[0];
                                                         }
                                                         ?>,        <?php $res = mysqli_query($conn, $cvar3_3);
                                                                               while($row = mysqli_fetch_array($res)){
                                                                                 echo $row[0];
                                                                               }
                                                                               ?>,             <?php $res = mysqli_query($conn, $cvar4_3);
                                                                                                     while($row = mysqli_fetch_array($res)){
                                                                                                       echo $row[0];
                                                                                                     }
                                                                                                     ?>,           <?php $res = mysqli_query($conn, $cvar5_3);
                                                                                                                           while($row = mysqli_fetch_array($res)){
                                                                                                                             echo $row[0];
                                                                                                                           }
                                                                                                                           ?>,      <?php $res = mysqli_query($conn, $cvar6_3);
                                                                                                                                                 while($row = mysqli_fetch_array($res)){
                                                                                                                                                   echo $row[0];
                                                                                                                                                 }
                                                                                                                                                 ?>,        <?php $res = mysqli_query($conn, $cvar7_3);
                                                                                                                                                                       while($row = mysqli_fetch_array($res)){
                                                                                                                                                                         echo $row[0];
                                                                                                                                                                       }
                                                                                                                                                                       ?>,      <?php $res = mysqli_query($conn, $cvar8_3);
                                                                                                                                                                                             while($row = mysqli_fetch_array($res)){
                                                                                                                                                                                               echo $row[0];
                                                                                                                                                                                             }
                                                                                                                                                                                             ?>],
             ['추락사고',  <?php $res = mysqli_query($conn, $cvar1_4);
                                   while($row = mysqli_fetch_array($res)){
                                     echo $row[0];
                                   }
                                   ?>,      <?php $res = mysqli_query($conn, $cvar2_4);
                                                         while($row = mysqli_fetch_array($res)){
                                                           echo $row[0];
                                                         }
                                                         ?>,        <?php $res = mysqli_query($conn, $cvar3_4);
                                                                               while($row = mysqli_fetch_array($res)){
                                                                                 echo $row[0];
                                                                               }
                                                                               ?>,             <?php $res = mysqli_query($conn, $cvar4_4);
                                                                                                     while($row = mysqli_fetch_array($res)){
                                                                                                       echo $row[0];
                                                                                                     }
                                                                                                     ?>,           <?php $res = mysqli_query($conn, $cvar5_4);
                                                                                                                           while($row = mysqli_fetch_array($res)){
                                                                                                                             echo $row[0];
                                                                                                                           }
                                                                                                                           ?>,      <?php $res = mysqli_query($conn, $cvar6_4);
                                                                                                                                                 while($row = mysqli_fetch_array($res)){
                                                                                                                                                   echo $row[0];
                                                                                                                                                 }
                                                                                                                                                 ?>,      <?php $res = mysqli_query($conn, $cvar7_4);
                                                                                                                                                                       while($row = mysqli_fetch_array($res)){
                                                                                                                                                                         echo $row[0];
                                                                                                                                                                       }
                                                                                                                                                                       ?>,      <?php $res = mysqli_query($conn, $cvar8_4);
                                                                                                                                                                                             while($row = mysqli_fetch_array($res)){
                                                                                                                                                                                               echo $row[0];
                                                                                                                                                                                             }
                                                                                                                                                                                             ?>]
          ]);

          var options = {
            title : ' ',
            vAxis: {title: '횟수'},
            hAxis: {title: '종류'},
            seriesType: 'bars',
            series: {5: {type: 'line'}}
          };

          var chart = new google.visualization.ComboChart(document.getElementById('chart_div'));
          chart.draw(data, options);
          }
          </script>
       </div>
         <table class="table table-striped table-bordered table-hover table-condensed" id="dataTables-example">
            <thead>
                <tr>
                    <th>버스 번호</th>
                    <th>차량 번호</th>
                    <th>위치</th>
                    <th>상태</th>
                    <th>시간</th>
                </tr>
            </thead>
            <tbody>
              <?php while ($row = mysqli_fetch_array($result)) { ?>
                  <tr>
                    <td><?php echo $row[0]; ?></td>
                    <td><?php echo $row[1]; ?></td>
                    <td><?php echo $row[2]; ?></td>
                    <td><?php echo $row[3]; ?></td>
                    <td><?php echo $row[4]; ?></td>
                  </tr>
              <?php }
              mysql_close($conn); ?>
            </tbody>
        </table>


      </div>
    </div>

    <!-- jQuery (부트스트랩의 자바스크립트 플러그인을 위해 필요합니다) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <!-- 모든 컴파일된 플러그인을 포함합니다 (아래), 원하지 않는다면 필요한 각각의 파일을 포함하세요 -->
    <script src="http://113.130.158.195:3306/bootstrap/js/bootstrap.min.js"></script>
    <script type="text/javascript" src="//apis.daum.net/maps/maps3.js?apikey=b3138577083cb1fe9cd9d4d6474e2a8e&libraries=services,clusterer,drawing"></script>
  </body>
</html>