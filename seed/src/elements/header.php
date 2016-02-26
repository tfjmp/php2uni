<?php
function /*string*/ random_colour(){
  srand(time());
  /*int*/ $rand = rand() >> 8;
  return "#" + dechex($rand);
}
?>
<header>
<h1 style="font-family:'Ubuntu', sans-serif; color:<?php echo random_colour(); ?>;">PHP2Uni</h1>
</header>
