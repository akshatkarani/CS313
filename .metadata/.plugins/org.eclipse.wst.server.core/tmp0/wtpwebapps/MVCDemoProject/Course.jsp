<%@page import="com.mvc.bean.CourseBean"%> 
<%@page import="java.util.ArrayList"%> 
<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
  <head>
    <title>Course Information</title>
  </head>
<body>
  <% ArrayList<CourseBean> std = (ArrayList<CourseBean>)request.getAttribute("data");
    if(std.size() != 0){%>
    <table border ="1" width="500" align="center">

      <tr bgcolor="00FF7F"> 
        <th><b>Course ID</b></th> 
        <th><b>Course Title</b></th> 
        <th><b>Grade</b></th> 
      </tr> 
      <%for(CourseBean s:std){%>
        <tr>
          <td><%=s.getCourseID()%></td> 
          <td><%=s.getTitle()%></td> 
          <td><%=s.getGrade()%></td> 
        </tr>
      <%}%>
    </table>
    <%} else {%> No result found <%}%>
  <div style="text-align: right"><a href="Home.jsp">Back</a></div>

</body>
</html>
