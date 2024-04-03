<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<?php
$name = $_GET['formular'];
?>
<body>
    <form method="GET">
        <input type="text" name="formular">
        <input type="submit" />
    </form>
    <script>
        var retval = <?php echo($name) ?>
        document.write(retval)
    </script>
</body>
</html>