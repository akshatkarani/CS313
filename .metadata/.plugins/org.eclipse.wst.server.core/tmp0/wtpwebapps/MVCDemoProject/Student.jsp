<%@page import="com.mvc.bean.StudentBean"%> 
<%@page import="java.util.ArrayList"%> 
<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
  <head>
    <title>Student Information</title>
  </head>
<body>
    <% ArrayList<StudentBean> std = (ArrayList<StudentBean>)request.getAttribute("data");
    if(std.size() != 0){%>
    <table border ="1" width="500" align="center">

      <tr bgcolor="00FF7F"> 
        <th><b>Student id</b></th> 
        <th><b>Student Name</b></th> 
        <th><b>Dept Name</b></th> 
      </tr> 
      <%for(StudentBean s:std){%>
        <tr>
          <td><%=s.getId()%></td> 
          <td><%=s.getName()%></td> 
          <td><%=s.getDept_name()%></td> 
        </tr>
      <%}%>
    </table>
    <%} else {%> Student not found <%}%>
  <div style="text-align: right"><a href="Home.jsp">Back</a></div>

</body>
</html>

