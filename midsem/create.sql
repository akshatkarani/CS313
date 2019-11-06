-- Question 1.

drop table book;
drop table student;
drop table issue;

create table book
	(book_id	varchar(20),
	 title		varchar(200),
	 category	varchar(20),
	 author 	varchar(50),
	 primary key (book_id)
	);

create table student
	(student_id	varchar(20),
	 name		varchar(20),
	 dept_name	varchar(20),
	 year 		numeric(4,0),
	 semester 	varchar(6),
	 primary key (student_id)
	);

create table issue
	(student_id		varchar(20),
	 book_id		varchar(20),
	 date_issue		date,
	 date_returned 	date,
	 primary key (student_id, book_id, date_issue),
	 foreign key (student_id) references student,
	 foreign key (book_id) references book
	);