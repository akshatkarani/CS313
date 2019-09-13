package com.mvc.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import com.mvc.bean.AdvisorBean;
import com.mvc.util.DBConnection;

public class AdvisorDao
{
	public ArrayList<AdvisorBean> getAdvisorInformation(String s_id)
	{
		ArrayList<AdvisorBean> std = new ArrayList<AdvisorBean>();
		Connection con = null;
		ResultSet resultSet = null;
		PreparedStatement ps = null;
		try
		{
			con = DBConnection.createConnection();
			String query = "select s_id, i_id, name " +
						   "from advisor inner join instructor " +
						   "on advisor.i_id = instructor.ID " +
						   "where advisor.s_id = ?";
			ps = con.prepareStatement(query);
			ps.setString(1, s_id);
			resultSet = ps.executeQuery();

			String studentID, advisorID, name;
			while(resultSet.next())
			{
				studentID = resultSet.getString("s_id");
				advisorID = resultSet.getString("i_id");
				name = resultSet.getString("name");
				std.add(new AdvisorBean(studentID, advisorID, name));
				System.out.println(std);
				System.out.println(studentID + " " + advisorID + " " + name);
			}
		} catch (SQLException e)
		{
			e.printStackTrace();
		}
		return std;
	}
}
