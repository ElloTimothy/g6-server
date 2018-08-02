<?php
 $con = mysqli_connect('localhost','Eclz','07020780','info');
?> 
<html>
  <head>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load('current', {'packages':['corechart']});
      google.charts.setOnLoadCallback(drawChart);

      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['TIME', 'SUCCESS RATE', 'FAILURE RATE'],
                 <?php 
 $query = "select TIME,SUCCESS,FAILURE from processing";

 $exec = mysqli_query($con,$query);
 while($row = mysqli_fetch_array($exec)){

 echo "['".$row['TIME']."',".$row['SUCCESS'].",".$row['FAILURE']."],";
 }
 ?>
        ]);

        var options = {
          title: 'SERVER PERFORMANCE',
          curveType: 'function',
          legend: { position: 'bottom' }
        };

        var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));

        chart.draw(data, options);
      }
    </script>
  </head>
  <body>   
    <div style="position:relative;width:100%">
       <div id="curve_chart" style="position:absolute;right:0px;top:0px;width: 500px; height: 300px;"></div>
   
  </body>
</html>

