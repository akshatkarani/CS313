package servlets;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("BookServlet")
public class Book extends HttpServlet{
	
	private static final long serialVersionUID = 1L;
	
	static Connection getConnection() {
		String dbURL = "jdbc:postgresql://localhost:5432/library";
		String dbUser = "postgres";
		String dbPass = "seventyfour";
		Connection connection=null;
		try {
			Class.forName("org.postgresql.Driver");
			connection = DriverManager.getConnection(dbURL, dbUser, dbPass);
		} catch(ClassNotFoundException cnfe){
			System.out.println("JDBC Driver not found");
		} catch(SQLException sqle){
			System.out.println("Error in getting connetcion from the database");
		}

		return connection;
	}

	static void closeConnection(Connection connection) {
		try {
			connection.close();
		} catch(SQLException sqle) {
			System.out.println("Error in close database connetcion");
		}
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		String book_id = request.getParameter("book_id");
		String title = request.getParameter("title");
		Connection conn = Book.getConnection();
		try {
			PreparedStatement ps1= conn.prepareStatement(
					"select book_id from book where book_id=? and title=?");
			ps1.setString(1, book_id);
			ps1.setString(2, title);
			ResultSet rs1 = ps1.executeQuery();
			
			while (rs1.next()) {
				book_id = rs1.getString("book_id");
			}
			
			PreparedStatement ps2 = conn.prepareStatement(
					"select student_id, name, (issue.date_returned - issue.date_issue) as length " +
					"from issue natural join student where issue.book_id=?");
			ps2.setString(0, book_id);
			ResultSet rs2 = ps2.executeQuery();
			
			List<List<String>> out = new ArrayList<List<String>>();
			
			while (rs2.next()) {
				List<String> temp = new ArrayList<String>();
				temp.add(rs2.getString("student_id"));
				temp.add(rs2.getString("name"));
				temp.add(rs2.getString("length"));
				
				out.add(temp);
			}
			
			request.setAttribute("result", out);
			RequestDispatcher rd =  request.getRequestDispatcher("Home.jsp");
			rd.forward(request, response);
			
		} catch(SQLException sqle) {
			System.out.println("SQL exception");
		} finally {
			closeConnection(conn);
		}
	}
}
