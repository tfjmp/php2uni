<?php
function /*bool*/ isPrime(/*int*/ $n) {
 /*int*/ $i = 2;

 if ($n == 2) {
  return true;
 }

 while ($i <= $n/2) {
  if ($n % $i == 0) {
   return false;
  }
  $i++;
 }

 return true;
}

/*int*/ $n=0;
for (/*int*/ $i = 3; $i < 5000; $i++) {
  if (isPrime($i)) {
    $n = $i;
  }
}
echo $n;
?>
