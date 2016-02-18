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

<?php require_once('./test.php'); ?>

<p>
<?php
/*int*/ $x=3;
echo $x;
?>
</p>
<p>
<?php
$x+=4+4;
echo $x;
?>
</p>
<p>
<?php
my_function();
$foo = new MyClass;
$foo->setA(4);
echo $foo->getA();
?>
</p>
<p>
<?php
$bar = new MyClass;
$bar->setB(3.14);
echo $bar->getB();
?>
</p>

<h2><?php echo date(W3C); ?></h2>
<h2>Page created on <?php echo date(W3C, mktime(20, 1, 1, 2, 18, 2016)); ?></h2>
