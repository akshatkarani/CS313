package com.mvc.controller;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.mvc.bean.StudentBean;
import com.mvc.dao.StudentDao;

public class StudentServlet extends HttpServlet
{
	private static final long serialVersionUID = 1L;

	public StudentServlet() {}

	protected void doPost(HttpServletRequest request,
						  HttpServletResponse response) throws ServletException, IOException
	{
	    String studentID = request.getParameter("id");
	    System.out.println(studentID);

	    StudentDao studentDao = new StudentDao();

	    ArrayList<StudentBean> std = studentDao.getStudentInformation(studentID);
	    request.setAttribute("data", std);

	    RequestDispatcher rd =  request.getRequestDispatcher("Student.jsp");
	    rd.forward(request, response);
	}

}
