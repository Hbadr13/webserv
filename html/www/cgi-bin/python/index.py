import os
print("Centent-type: text/html\r\n")
print("\r\n")
html_content = """
<!DOCTYPE html>
<html>

<head>
    <title>COOKIES</title>
    <link rel='stylesheet' type='text/css' href='../../cookies/styleCookies.css'>
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
                <a href='../../index.html'>
                    <h2 class='logo'>WEBSERV</h2>
                </a>
            </div>
            <div class='menu'>
                <ul>
                    <li><a href='../../index.html'>HOME</a></li>
                    <li><a href='../../founders/founders.html'>FOUNDERS</a></li>
                    <li><a href='../../servies/servies.html'>SERVIES</a></li>
                    <li><a href='../../cookies/cookies.html'>COOKIES</a></li>
                    <li><a href='index.py'>CGI</a></li>
                </ul>
            </div>
            </div>
			<video controls>
			<source src='../../video/video.mp4' type='video/mp4'>
			Your browser does not support the video tag.
		  </video>
            </div>
</body>

</html>
"""
print(html_content)
