<?php
  require_once('./test.php');
  echo 'test';

  class MyClass{
     /*int*/ $a;
     /*double*/ $b;

    function /*int*/ getA(){
      return $this->a;
    }

    function /*double*/ getB(){
      return $this->b;
    }

    function /*void*/ setA(/*int*/ $v){
      $this->a=$v;
    }

    function /*void*/ setB(/*double*/ $v){
      $this->b=$v;
    }
  }
?>

<?php
function /*void*/ my_function(){
  /*int*/ $v=4;
  echo $v;
}
?>

<?php
require_once('./test.php');


/*int*/ $x=3;
echo $x;
$x+=4+4;
echo $x;
my_function();
$foo = new MyClass;
$foo->setA(4);
echo $foo->getA();
$bar = new MyClass;
$bar->setB(3.14);
echo $bar->getB();
?>
