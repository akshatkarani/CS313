
 <%@ page language="java" contentType="text/html; charset=ISO-8859-1"
pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Login</title>
<script> 
function validate()
{ 
var username = document.form.username.value; 
var password = document.form.password.value;
if (username==null || username=="")
{ 
alert("Username cannot be blank"); 
return false; 
}
else if(password==null || password=="")
{ 
alert("Password cannot be blank"); 
return false; 
} 
}
</script> 
</head>
<body>
<div style="text-align:center"><h1>Login application in Java using MVC and Postgres </h1> </div>
<br>
<form name="form" action="LoginServlet" method="post" onsubmit="return validate()">
<!-- Do not use table to format fields. As a good practice use CSS -->
<table align="center">
<tr>
<td>Username</td>
<td><input type="text" name="username" /></td>
</tr>
<tr>
<td>Password</td>
<td><input type="password" name="password" /></td>
</tr>
<tr> <!-- refer to the video to understand request.getAttribute() -->
<td><span style="color:red"><%=(request.getAttribute("errMessage") == null) ? ""
: request.getAttribute("errMessage")%></span></td>
</tr>
<tr>
<td></td>
<td><input type="submit" value="Login"></input><input
type="reset" value="Reset"></input></td>
</tr>
</table>
</form>
</body>
</html>