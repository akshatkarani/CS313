<%@page import="com.mvc.bean.AdvisorBean"%> 
<%@page import="java.util.ArrayList"%> 
<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
  <head>
    <title>Advisor Information</title>
  </head>
<body>
  <% ArrayList<AdvisorBean> std = (ArrayList<AdvisorBean>)request.getAttribute("data");
    if(std.size() != 0){%>
    <table border ="1" width="500" align="center">

      <tr bgcolor="00FF7F"> 
        <th><b>Student ID</b></th> 
        <th><b>Advisor ID</b></th> 
        <th><b>Advisor Name</b></th> 
      </tr> 
      <%for(AdvisorBean s:std){%>
        <tr>
          <td><%=s.getStudentID()%></td> 
          <td><%=s.getAdvisorID()%></td> 
          <td><%=s.getName()%></td> 
        </tr>
      <%}%>
    </table>
    <%} else {%> No result found <%}%>
  <div style="text-align: right"><a href="Home.jsp">Back</a></div>

</body>
</html>
