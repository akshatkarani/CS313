package com.mvc.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import com.mvc.bean.StudentBean;
import com.mvc.util.DBConnection;


public class StudentDao
{

	public ArrayList<StudentBean> getStudentInformation(String studentID)
	{
	    ArrayList<StudentBean> std = new ArrayList<StudentBean>();
		Connection con = null;
		ResultSet resultSet = null;
		PreparedStatement ps = null;
		try
		{
			con = DBConnection.createConnection();
			String query = "select * from student where id = ?";
			ps = con.prepareStatement(query);
			ps.setString(1, studentID);
			resultSet = ps.executeQuery();

			String id, name, dept_name;
			while(resultSet.next())
			{
				id = resultSet.getString("id");
				name = resultSet.getString("name");
				dept_name = resultSet.getString("dept_name");
				std.add(new StudentBean(id, name, dept_name));
				System.out.println(std);
				System.out.println(id + " " + name + " " + dept_name);
			}
		} catch(SQLException e)
		{
			e.printStackTrace();
		}
		return std;
	}
}
