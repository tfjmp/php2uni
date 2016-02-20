<!DOCTYPE html>
<html>
<?php
  require 'elements/html_head.php'
?>
<body>
<?php
  require 'elements/header.php'
?>

<p>We know make a small demonstration.</p>

<?php
function /*void*/ my_function(){
  /*string*/ $v="We called a function!";
  echo $v;
}
?>

<p><?php my_function(); ?></p>

<?php
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
$foo = new MyClass;
$foo->setA(4);
$foo->setB(3.14);
?>

<p>And toyed with a class <?php echo $foo->getA(); ?>
  , and more <?php echo $foo->getB(); ?>
  , and more <?php echo $foo->getA()+$foo->getB(); ?>
</p>

<p><a href="/hello?hello=world&from=index">Get parameter example.</a></p>

<?php
  require 'elements/footer.php'
?>
</body>
</html>
