package servlets;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import Home.RestaurantDetails;

/**
 * Servlet implementation class ListRestaurants
 */
@WebServlet("/ListRestaurants")
public class ListRestaurants extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ListRestaurants() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		
		String locality = request.getParameter("rest");
		
		String user = request.getParameter("user");
		// System.out.println("restaurant "+name);
		
		List<RestaurantDetails> restaurantDetailList = new ArrayList<>();
		
		restaurantDetailList = Home.Home.getRestaurants(locality);

		System.out.println("restaurantDetailList: "+restaurantDetailList);
		
//		locality = "\"" + locality + "\"";
		
		List<String> restaurantNameList = new ArrayList<>();
		List<String> restaurantLocationList = new ArrayList<>();
		List<String> restaurantRatingList = new ArrayList<>();
		List<String> restaurantVotesList = new ArrayList<>();
		List<String> restaurantIdList = new ArrayList<>();
		
		for(int i=0;i<restaurantDetailList.size();i++){
			
//			String s1 ="\"" + restaurantDetailList.get(i).getRestaurantName() + "\"";
			String s1 =restaurantDetailList.get(i).getRestaurantName();

			restaurantNameList.add(s1);
			
			String s2 =restaurantDetailList.get(i).getLocation();
			restaurantLocationList.add(s2);
			
			String s3 =restaurantDetailList.get(i).getRating();
			restaurantRatingList.add(s3);
		
			String s4 =restaurantDetailList.get(i).getVotes();
			restaurantVotesList.add(s4);
			
			restaurantIdList.add(restaurantDetailList.get(i).getRestaurantId());
	
			}
	

		request.setAttribute("restaurantNameList", restaurantNameList);
		request.setAttribute("restaurantLocationList", restaurantLocationList);
		request.setAttribute("restaurantRatingList", restaurantRatingList);
		request.setAttribute("restaurantVotesList", restaurantVotesList);
		request.setAttribute("restaurantIdList", restaurantIdList);
		request.setAttribute("locality", locality);
		request.setAttribute("user", user);

		
		RequestDispatcher dispatcher = request.getRequestDispatcher("restaurantList.jsp");
		dispatcher.forward(request, response);
		
		
	}
	
	
}
