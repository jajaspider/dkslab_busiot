
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
    <link href="https://bootswatch.com/superhero/bootstrap.min.css" rel="stylesheet">
    <script src="http://code.jquery.com/jquery-latest.min.js"></script>
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
    <div class = "container">
    	<div class="wrapper col-md-6 col-md-offset-3">
    		<form action="main.php" method="post" name="Login_Form" class="form-signin">
    		    <h3 class="form-signin-heading"><span style="color: black">관리자님! 환영합니다.</span></h3>
    			  <hr class="colorgraph"><br>

    			  <input type="text" class="form-control" name="id" placeholder="id" required="" autofocus=""/>
    			  <input type="password" class="form-control" name="pass" placeholder="pass" required=""/>

    			  <button class="btn btn-lg btn-info btn-block"  name="Submit" value="Login" type="Submit">Login</button>
    		</form>
    	</div>
    </div>

    <!-- jQuery (부트스트랩의 자바스크립트 플러그인을 위해 필요합니다) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <!-- 모든 컴파일된 플러그인을 포함합니다 (아래), 원하지 않는다면 필요한 각각의 파일을 포함하세요 -->
    <script src="bootstrap/js/bootstrap.min.js"></script>

  </body>

  <footer>

  </footer>

</html>
