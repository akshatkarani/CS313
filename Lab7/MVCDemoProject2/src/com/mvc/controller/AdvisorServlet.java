package com.mvc.controller;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.mvc.bean.AdvisorBean;
import com.mvc.dao.AdvisorDao;

public class AdvisorServlet extends HttpServlet
{
	private static final long serialVersionUID = 1L;

	public AdvisorServlet() {}

	protected void doPost(HttpServletRequest request,
						  HttpServletResponse response) throws ServletException, IOException
	{
	    String studentID = request.getParameter("id");
	    System.out.println(studentID);

	    AdvisorDao advisorDao = new AdvisorDao();

	    ArrayList<AdvisorBean> std = advisorDao.getAdvisorInformation(studentID);
	    request.setAttribute("data", std);

	    RequestDispatcher rd =  request.getRequestDispatcher("Advisor.jsp");
	    rd.forward(request, response);
	}
}
