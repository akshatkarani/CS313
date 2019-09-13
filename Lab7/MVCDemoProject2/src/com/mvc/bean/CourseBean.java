package com.mvc.bean;

public class CourseBean
{
	private String course_id;
	private String title;
	private String grade;

	public CourseBean() {}

	public CourseBean(String course_id, String title, String grade)
	{
		this.course_id = course_id;
		this.title = title;
		this.grade = grade;
	}

	public void setCourseID(String course_id)
	{
	    this.course_id = course_id;
	}

	public String getCourseID()
	{
	    return this.course_id;
	}

	public void setTitle(String title)
	{
	    this.title = title;
	}

	public String getTitle()
	{
	    return this.title;
	}

	public void setGrade(String grade)
	{
	    this.grade = grade;
	}

	public String getGrade()
	{
	    return this.grade;
	}

}
