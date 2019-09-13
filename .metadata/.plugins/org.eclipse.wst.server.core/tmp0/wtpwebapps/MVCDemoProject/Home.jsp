
<%@page import="com.mvc.bean.StudentBean"%>
<%@page import="java.util.ArrayList"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Home Page</title>
<style>
* {
  box-sizing: border-box;
}

.column {
  float: left;
  width: 33.33%;
  padding: 5px;
}

/* Clearfix (clear floats) */
.row::after {
  content: "";
  clear: both;
  display: table;
}

/* Responsive layout - makes the three columns stack on top of each other instead of next to each other */
@media screen and (max-width: 500px) {
  .column {
    width: 100%;
  }
}

input[type=button], input[type=submit], input[type=reset] {
  background-color: #4CAF50;
  border: none;
  color: white;
  padding: 12px 25px;
  text-decoration: none;
  margin: 4px 2px;
  cursor: pointer;
  font-weight:bold;
  font-size:13px;
}
input[type=text] {
  width: 70%;
  padding: 12px 20px;
  margin: 8px 0;
  box-sizing: border-box;
  border: 1px solid #555;
  outline: none;
}

input[type=text]:focus {
  background-color: lightblue;
}
</style>

</head>
<body>

	<center>
		<h2 style="color:purple; font-weight:bold">Home Page</h2>
		<h3 style="color:blue; font-weight:bold">Welcome</h3>
	</center>
	<p style="text-align:center;"><img src="images/icons/portal.jpg" height="350px" width="700px"></p>
	<div class="row">
  <div class="column">
    <img src="images/icons/student_info.jpg" height="180px" width="200px">
    <form name="form" action="StudentServlet" method="post">
	
	<h3 style="color:SlateBlue; font-weight:bold">Get Student Info</h3><input type="text" name="id" placeholder="Enter student id"/> 
	<br><input type="submit" value="Submit"></input><input type="reset" value="Reset"></input>
	</form>
  </div>
  <div class="column">
    <img src="images/icons/course_info.jpg" height="180px" width="200px">
    <form name="form" action="CourseServlet" method="post">

		<h3 style="color:SlateBlue; font-weight:bold">Get Course Info</h3><input type="text" name="id" placeholder="Enter student id"/> 
		<br><input type="submit" value="Submit"></input><input type="reset" value="Reset"></input>
	</form>
  </div>
  <div class="column">
    <img src="images/icons/advisor.jpg" height="180px" width="200px">
    <form name="form" action="AdvisorServlet" method="post">

		<h3 style="color:SlateBlue; font-weight:bold">Get Advisor Info</h3> <input type="text" name="id" placeholder="Enter student id"/> 
		<br><input type="submit" value="Submit"></input><input type="reset" value="Reset"></input>
	</form>
  </div>
</div>
	<!-- Refer to the video to understand how this works -->
	

	

	
<br><br>

</body>
</html>


