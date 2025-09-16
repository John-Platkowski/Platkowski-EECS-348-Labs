<html>
<body>

<?php
  $size = $_GET["size"]; 
  for ($i = 0; $i < $size; $i++)
  {
    if ($i == 0)
    {
      for ($k = 0; $k < $size; $k++)
      {
        print " " . $k . " ";
      }
      print "\n";
    }
    print "[" . $i . "]\n";
    for ($j = 0; $j < $size; $j++)
    {
      print $i * $j;
    }
    print "[" . $i . "]\n";
  }
?>
<br>

</body>
</html>
