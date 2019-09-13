package com.mvc.util;

import java.sql.Connection;
import java.sql.DriverManager;

public class DBConnection
{
	public static Connection createConnection()
	{
		Connection con = null;
		String url = "jdbc:postgresql://localhost:5432/university";
		String username = "postgres";
		String password = "seventyfour";

	try
	{
		try
		{
			Class.forName("org.postgresql.Driver");
		}
		catch (ClassNotFoundException e)
		{
			e.printStackTrace();
		}

		con = DriverManager.getConnection(url, username, password);
		System.out.println("Printing connection object "+con);
	}
	catch (Exception e)
	{
		e.printStackTrace();
	}
	return con;
	}
}
