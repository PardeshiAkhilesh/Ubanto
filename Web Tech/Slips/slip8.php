<?php
    $a = $_GET['str1'];
    $b = $_GET['str2'];

    $pos = strpos($a,$b);
    if($pos==0)
        echo "the small string is appears at the start of the large string<br>";
    else
    {
        echo "the small string does not appear at the start of the string <br>";
    }
    $pos = strpos($a,$b);
    
    echo "The small String appears at possition : $pos <br>";

    $case = strcasecmp($a,$b);
    if($case==0)
        echo "Both are equal <br>";
    else if($case>0)
        echo "First String Bigger that seonce";
    else
        echo "First is smaller than second";
?>