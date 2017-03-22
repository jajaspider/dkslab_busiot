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
    <!-- IE8 에서 HTML5 요소와 미디어 쿼리를 위한 HTML5 shim 와 Respond.js -->
    <!-- WARNING: Respond.js 는 당신이 file:// 을 통해 페이지를 볼 때는 동작하지 않습니다. -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body>
    <div class="container" style="padding-top: 50px;" id="login">
        <div class="text-center">
          <form class="form-signin" style ="padding-top : 40px;">
            <h2 class="form-signin-heading">로그인</h2>
            <label for="inputEmail" class="sr-only">이메일 주소</label>
            <input type="email" id="inputEmail" class="form-control" placeholder="이메일 주소" required autofocus>
            <label for="inputPassword" class="sr-only">비밀번호</label>
            <input type="password" id="inputPassword" class="form-control" placeholder="비밀번호" required>
            <div class="checkbox">
              <label>
                <input type="checkbox" value="remember-me"> 기억하기
              </label>
            </div>
            <button class="btn btn-lg btn-primary btn-block" type="submit">로그인</button>
          </form>
      </div> <!-- /container -->
    </div>

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
                  <li class="divider"></li>
                  <li><a href="http://113.130.158.195:3306/Surveillance_status_monitoringp.php">Surveillance status monitoring</a></li>
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

    <!-- jQuery (부트스트랩의 자바스크립트 플러그인을 위해 필요합니다) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <!-- 모든 컴파일된 플러그인을 포함합니다 (아래), 원하지 않는다면 필요한 각각의 파일을 포함하세요 -->
    <script src="http://113.130.158.195:3306/bootstrap/js/bootstrap.min.js"></script>

  </body>
</html>
