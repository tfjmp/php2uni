
<?php
  function /*int*/ nb_visitor(){
    /*string*/ $str = $_SERVER["nb_visitor"];
    if($str==""){
      $_SERVER["nb_visitor"]="1";
      return 1;
    }
    /*int*/ $nb = intval($str);
    $nb++;
    $_SERVER["nb_visitor"]=strval($nb);
    return $nb;
  }
?>

<footer>
<hr/>

Computer Laboratory, University of Cambridge<br/>
Department of Computer Science, University of Otago<br />
<br />
<br />
Server vesion: <?php echo $_SERVER["SERVER_SOFTWARE"] ?><br />
Server time: <?php echo date(W3C); ?><br />
Number of visitors: <?php echo nb_visitor(); ?><br />
</footer>
