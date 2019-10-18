<%@page import="Home.Home"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.util.*" %>
<%@ page import="Home.Home" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>


<style type="text/css">
		
	body { margin-top: 5%; margin-right: 10%; margin-left: 10%;
		background-image: url("wall5.jpg");
  	background-size: 100% 100%;
  background-attachment:fixed; }
 </style>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Account</title>
</head>
<body>
<font color="white">
<center>


<%
	String a1 = request.getParameter("roll");
	String a2 = request.getParameter("pwd");
	
	int rr = Home.checkPassword( a1, a2);
	
	//out.print(rr);
	if(rr==1){
		
		out.print("<h1>Your are logged in as "+a1+"</h1>");
		out.print("<form action =\"home.jsp\" method=\"post\" ><input type=\"hidden\" name=\"user\" value="+a1+"><input type=submit value=\"Search restaurant\" ></form>");
		
	}
	else{
		
		
		out.print("<h1>Wrong username or password </h1>");
		out.print("<a href=index.html>Go to login page </a>");
		
	}

%>


</body>
</html>
