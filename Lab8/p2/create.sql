create table restaurant
	(restaurant_id           varchar(5),
	 restaurant_name		varchar(50), 
	 location		varchar(130), 
	 menu     	        varchar(80),
	 rating     	        numeric(4,2),
	 phone_no		varchar(20),
	 cost	        	money,
	 primary key (restaurant_id)
	);
create table locality
	(locality		varchar(20), 
	 restaurant_id           varchar(5),
	 primary key (restaurant_id)
	);
