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
<h1>Your account has been created</h1>

<%
	String a1 = request.getParameter("newroll");
	String a2 = request.getParameter("newpwd");
	
	Home.addAccount( a1, a2);

%>
<a href=index.html>Go to login page </a>

</body>
</html>
