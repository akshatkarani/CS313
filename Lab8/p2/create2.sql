
create table account
	(user_id		varchar(20), 
	 password1               varchar(20),
	 primary key (user_id)
	);
create table reviews
	(user_id           varchar(20),
	 restaurant_id		varchar(5),  
	 user_review     	        varchar(100),
	 user_rating     	        numeric(4,2)
	);
