
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class studentServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws IOException, ServletException {

		response.setContentType("text/html;charset=UTF-8");
		String id = request.getParameter("id");
		PrintWriter out = response.getWriter();

		Connection conn = null;
		Statement  stmt = null;
		try {
			out.println("<!DOCTYPE html>");
			out.println("<html>");
			out.println("<head><title>Qurey Servlet</title></head>");
			out.println("<body>");
			Class.forName("org.postgresql.Driver");
			String query="select * from student where id=?";
			conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/university", "postgres", "123456");
			PreparedStatement ps = conn.prepareStatement(query);
			ps.setString(1, id);
			ResultSet rset = ps.executeQuery();
			int count=0;
			while(rset.next()) {
				out.println("<p>" + rset.getString("id") + ", "
						+ rset.getString("name") + "</p>");
				++count;
			}
			out.println("<p>==== " + count + " rows found =====</p>");
			out.println("</body></html>");
		} catch (SQLException ex) {
			ex.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			out.close();
			try {
				if (stmt != null) stmt.close();
				if (conn != null) conn.close();  // return to pool
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
		}
	}
}

