<%@page import="com.mvc.bean.BookBean"%>
<%@page import="java.util.ArrayList"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

<html>
<head>
<title>Home Page</title>

<style>

  * {
    box-sizing: border-box;
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

  <div>
    <form name="form" action="BookServlet" method="post">
      <h3 style="color:SlateBlue; font-weight:bold">Get Book Info</h3>
      <input type="text" name="book_id" placeholder="Enter book id"/>
      <input type="text" name="title" placeholder="Enter book title"/>
    </form>
  </div>

</body>
</html>


