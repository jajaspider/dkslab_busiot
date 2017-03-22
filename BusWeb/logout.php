<?php
  $conn = mysqli_connect("localhost", "root", "hoyoung");
  if(mysqli_connect_errno($conn)){
  }else {

    mysqli_select_db($conn, "login");

    $sql1 = "SELECT * FROM login_t";
    $result = $conn->query($sql1);
    $row = mysqli_fetch_array($result);

    mysqli_query($conn, "UPDATE login_t set only=0");

    //echo("<script>location.replace('test_login.php');</script>");
    echo $row[2];

    echo("<script>location.replace('login.php');</script>");
  }
 ?>
