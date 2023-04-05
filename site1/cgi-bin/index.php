<?php

$html = "

<!DOCTYPE html>
<html>

<head>
    <title>COOKIES</title>
    <link rel='stylesheet' type='text/css' href='../STYLE/styleCookies.css'>
	<style>
	video {
	  display: block;
	  margin: 0 auto;
	  max-width: 100%;
	  height: auto;
	}
  </style>
</head>

<body>
    <div class='main'>
        <div class='navbar'>
            <div class='icon'>
                <a href='../index.html'>
                    <h2 class='logo'>WEBSERV</h2>
                </a>
            </div>
            <div class='menu'>
                <ul>
                    <li><a href='../index.html'>HOME</a></li>
                    <li><a href='../FOUNDERS/founders.html'>FOUNDERS</a></li>
                    <li><a href='../SERVIES/servies.html'>SERVIES</a></li>
                    <li><a href='../COOKIES/cookies.html'>COOKIES</a></li>
                    <li><a href='index.php'>CGI</a></li>
                </ul>
            </div>
            </div>
			<video controls>
			<source src='video.mp4' type='video/mp4'>
			Your browser does not support the video tag.
		  </video>
            </div>
</body>

</html>";

echo $html;
?>