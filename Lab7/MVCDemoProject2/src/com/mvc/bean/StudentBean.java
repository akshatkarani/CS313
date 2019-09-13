package com.mvc.bean;

public class StudentBean
{
	private String id;
	private String name;
	private String dept_name;

	public StudentBean() {}

	public StudentBean(String id, String name, String dept_name)
	{
	    this.id=id;
	    this.name=name;
	    this.dept_name=dept_name;

	}

	public String getDept_name()
	{
	    return dept_name;
	}

	public void setDept_name(String dept_name)
	{
	    this.dept_name = dept_name;
	}

	public String getName()
	{
	    return name;
	}

	public void setName(String name)
	{
	    this.name = name;
	}

	public String getId()
	{
	    return id;
	}

	public void setId(String id)
	{
	    this.id = id;
	}

}
