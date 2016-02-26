<!DOCTYPE html>
<html>
<?php
  require 'elements/html_head.php'
?>
<body>
<?php
  require 'elements/header.php'
?>
<p>Hello <?php echo $_GET["hello"]; ?> from <?php echo $_GET["from"]; ?>.</p>
<?php
  require 'elements/footer.php'
?>
</body>
</html>
