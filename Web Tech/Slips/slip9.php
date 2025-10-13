<?php
    $str = $_GET['str'];
    $sep = $_GET['sep'];
    $option = $_GET['op'];
    switch($option)
    {
        case 'a':
            $arr = explode($sep,$str);
            foreach($arr as $s){
                echo "$s <br>";
            }
            break;
        case 'b':
            $cnt = substr_count($str,$sep);
            $n = str_replace($sep,"/",$str,$cnt);
            echo "The new string is : $n <br>";
            break;
        case 'c':
            $arr = explode($sep,$str);
            $cnt = count($arr);
            echo "The Last Word of the string is : ".$arr[$cnt-1];
            break;

    }
?>