package com.mvc.bean;

public class AdvisorBean
{
	private String studentID;
	private String advisorID;
	private String name;

	public AdvisorBean() {}

	public AdvisorBean(String studentID, String advisorID, String name)
	{
		this.studentID = studentID;
		this.advisorID = advisorID;
		this.name = name;
	}

	public void setStudentID(String studentID)
	{
		this.studentID = studentID;
	}

	public String getStudentID()
	{
		return this.studentID;
	}

	public void setAdvisorID(String advisorID)
	{
		this.advisorID = advisorID;
	}

	public String getAdvisorID()
	{
		return this.advisorID;
	}

	public void setName(String name)
	{
		this.name = name;
	}

	public String getName()
	{
		return this.name;
	}
}
