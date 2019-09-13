package com.mvc.dao;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import com.mvc.bean.LoginBean;
import com.mvc.util.DBConnection;

public class LoginDao
{
	public String authenticateUser(LoginBean loginBean)
	{
		String userName = loginBean.getUserName();
		String password = loginBean.getPassword();
		Connection con = null;
		Statement statement = null;
		ResultSet resultSet = null;
		String userNameDB = "";
		String passwordDB = "";
		try
		{
			con = DBConnection.createConnection();
			statement = con.createStatement();
			resultSet = statement.executeQuery("select name,password from users");
			while(resultSet.next())
			{
				userNameDB = resultSet.getString("name");
				System.out.println(userNameDB);
				passwordDB = resultSet.getString("password");
				System.out.println(passwordDB);
				if(userName.equals(userNameDB) && password.equals(passwordDB))
				{
					return "SUCCESS";
				}
			}
		}
		catch(SQLException e)
		{
			e.printStackTrace();
		}
		return "Invalid user credentials";
	}
}