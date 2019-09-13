package com.mvc.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import com.mvc.bean.CourseBean;
import com.mvc.util.DBConnection;

public class CourseDao
{
	public ArrayList<CourseBean> getCourseInformation(String studentID)
	{
		ArrayList<CourseBean> std = new ArrayList<CourseBean>();
		Connection con = null;
		ResultSet resultSet = null;
		PreparedStatement ps = null;
		try
		{
			con = DBConnection.createConnection();
			String query = "select course_id, grade, title from takes natural join course where takes.id = ?";
			ps = con.prepareStatement(query);
			ps.setString(1, studentID);
			resultSet = ps.executeQuery();

			String course_id, grade, title;
			while(resultSet.next())
			{
				course_id = resultSet.getString("course_id");
				grade = resultSet.getString("grade");
				title = resultSet.getString("title");
				std.add(new CourseBean(course_id, title, grade));
				System.out.println(std);
				System.out.println(course_id + " " + title + " " + grade);
			}
		} catch (SQLException e)
		{
			e.printStackTrace();
		}
		return std;
	}
}
