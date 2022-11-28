<%@ page language="java" contentType="text/html; charset=UTF-8"	pageEncoding="UTF-8"%>
<%@ page import="java.util.*" %>
 
<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<script type="text/javascript">
window.onload = function() { 
 
var dataPoints = [];
 
var chart = new CanvasJS.Chart("chartContainer", {
	animationEnabled: true,
	theme: "light2",
 	zoomEnabled: true,
	title: {
		text: "temperature"
	},
	axisY: {
		title: "temp",
		titleFontSize: 24
	},
	data: [{
		type: "spline",
		yValueFormatString: "#,##0.0## 'C",
		xValueType: "Time",
		dataPoints: dataPoints
	}]
});

var xValue = dataPoints.length;
//var yValue = dataPoints[dataPoints.length - 1].y;

var updateInterval = 5000;
setInterval(function () { $.getJSON("json.jsp", updateData) }, updateInterval);

function addData(data) {
	for (var i = 0; i < data.length; i++) {
		dataPoints.push({
			x: xValue,
			y: data[i].temp
		});
		xValue++;
	}
	
	chart.render();
};
function updateData(data) {
	dataPoints.push({
		x: xValue,
		y: data[0].temp
	});
	xValue++;
	chart.render();
};

$.getJSON("json.jsp", addData);
//setInterval($.getJSON("json.jsp", addData), updateInterval);
 
}
</script>
</head>
<body>
<div id = "box">
	<div id="chartContainer" style="height: 370px; width: 100%;"></div>
</div>

<script src="https://canvasjs.com/assets/script/jquery-1.11.1.min.js"></script>
<script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
</body>
</html>