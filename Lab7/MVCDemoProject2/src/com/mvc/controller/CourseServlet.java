package com.mvc.controller;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.mvc.bean.CourseBean;
import com.mvc.dao.CourseDao;

public class CourseServlet extends HttpServlet
{
	private static final long serialVersionUID = 1L;

	public CourseServlet() {}

	protected void doPost(HttpServletRequest request,
						  HttpServletResponse response) throws ServletException, IOException
	{
	    String studentID = request.getParameter("id");
	    System.out.println(studentID);

	    CourseDao courseDao = new CourseDao();

	    ArrayList<CourseBean> std = courseDao.getCourseInformation(studentID);
	    request.setAttribute("data", std);

	    RequestDispatcher rd =  request.getRequestDispatcher("Course.jsp");
	    rd.forward(request, response);
	}
}
