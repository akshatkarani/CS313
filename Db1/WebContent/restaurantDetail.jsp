<%@page import="Home.Home"%>
<%@page import="Home.RestaurantDetails"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>



<% 

	RestaurantDetails Object = new RestaurantDetails();
	
	String id = request.getParameter("id");
	System.out.println("restaurnrtDE"+id);
	
	String user = request.getParameter("user");
	
	String locality = Home.getlocality(id);
		
	Object = Home.getAllDetails(id);
	
	String name = Object.getRestaurantName();
	String location = Object.getLocation();
	String menuLink = Object.getMenu();
	String cost = Object.getCost();
	String rating = Object.getRating();
	String phone = Object.getPhone();
	
	// String location = name+","+locality+","+"Mumbai";
	String address ="https://maps.google.com/maps?q="+name+","+location+"&ie=UTF8&t=&z=17&iwloc=B&output=embed";
	address = "\"" + address+ "\"";
	
	
	out.print("<h2 align=\"center\"><i>"+name+"</i></h2><br><br>");
	
	out.print("<div align=\"center\">");
	out.print("<iframe width=\"1500\" height=\"300\"");
	out.print("src="+address+" frameborder=\"0\" scrolling=\"no\" marginheight=\"0\" marginwidth=\"0\" >");
	out.print("</iframe>");
	out.print("</div> <br><br>");
	//System.out.println(Object.getLocation());
	
	out.print("<div height=\"750\" width=\"1200\">");
	
		
	
	out.print("<div height=\"750\" width=\"500\" style=\"float:left; \" >");
	
 	out.print("<table align=\"right\">");
	out.print("<tr><td><font color=\"grey\" size=\"4\">Phone Number</font></td></tr>");
	out.print("<tr><td>"+phone+"</td></tr><tr></tr><tr></tr>");
	
	out.print("<tr><td><font color=\"grey\" size=\"4\">Location</font></td></tr>");
	out.print("<tr><td>"+location+"</td></tr><tr></tr><tr></tr>");
	
	out.print("<tr><td><font color=\"grey\" size=\"4\">Cost per Person</font></td></tr>");
	out.print("<tr><td>"+cost+"</td></tr><tr></tr><tr></tr>");
	
	out.print("<tr><td><font color=\"grey\" size=\"4\">Rating</font></td></tr>");
	out.print("<tr><td>"+rating+"</td></tr><tr></tr><tr></tr>");
	
	
	out.print("</table><br><br><br><br>"); 
	
	out.print("<br><br><br><br><h3 align=\"center\">Submit your Review & Rating</h3><br>");
	
	out.print("<div align=\"center\">");
	out.print("<form action=\"Reviews\" id=\"usrform\" method=\"post\">");
	out.print( "<input type=\"radio\" name=\"rating\" value=\"1\" checked> 1 <br>");
	out.print( "<input type=\"radio\" name=\"rating\" value=\"2\" > 2 <br>");
	out.print( "<input type=\"radio\" name=\"rating\" value=\"3\" > 3 <br>");
	out.print( "<input type=\"radio\" name=\"rating\" value=\"4\" > 4 <br>");
	out.print( "<input type=\"radio\" name=\"rating\" value=\"5\" > 5 <br>");
	out.print("<input type=\"hidden\" name=\"user\" value="+user+">");
	out.print("<input type=\"hidden\" name=\"restaurantID\" value="+id+">");

	out.print("</form>");	
	
	out.print("<textarea rows=\"4\" cols=\"50\" name=\"review\" form=\"usrform\"></textarea><br>");
	
	out.print("<button type=\"submit\" form=\"usrform\" value=\"Submit\">Submit</button>");
	
	out.print("</div>");
	
	out.print("</div>");

	
	out.print("<div width=\"700\" height=\"750\" style=\"float:right; \" >");
	out.print("<table>");
	out.print("<tr><td><h2>Menu</h2></td></tr>");
	out.print("<tr><td><iframe align =\"center\"width=\"700\" height=\"750\"");
	out.print("src="+menuLink+" frameborder=\"0\" scrolling=\"no\" marginheight=\"0\" marginwidth=\"0\" >");
	out.print("</iframe></td></tr>");
	out.print("</div>");
	
	
	out.print("</div>");

%>


</body>
</html>