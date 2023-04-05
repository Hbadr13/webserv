<?php

setcookie("user", "ebouabba" , time() + 60 * 60 * 24 * 30, "/");
setcookie("user1", "ebouabba1" , time() + 60 * 60 * 24 * 30, "/");
setcookie("user2", "ebouabba2" , time() + 60 * 60 * 24 * 30, "/");

// header("Centent-type: text/html");


$html = "</html><!DOCTYPE html>
<html>
    <body>
        
    <h1>My first PHP page</h1>
    
    
</body>
</html>";
echo $html;
?>
