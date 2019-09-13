create table course (crcode varchar, title varchar, dept varchar, credits int, teacher varchar);

insert into course(crcode, title, dept, credits, teacher) 
	values ('CS313', 'Database Management Lab', 'Computer Science', 3, 'NL Sarda');
insert into course(crcode, title, dept, credits, teacher) 
	values ('CS301', 'Computer Architecture', 'Computer Science', 6, 'Rajshekar');
insert into course(crcode, title, dept, credits, teacher) 
	values ('EE401', 'Pattern Recognition', 'Electrical', 6, 'Mahadeva Prasana');
insert into course(crcode, title, dept, credits, teacher) 
	values ('CS311', 'Computer Architecture Lab', 'Computer Science', 3, 'Rajshekar');
insert into course(crcode, title, dept, credits, teacher) 
	values ('CS403', 'Graph Theory', 'Computer Science', 6, 'Sagnik Sen');
insert into course(crcode, title, dept, credits, teacher) 
	values ('CS303', 'Database Management', 'Computer Science', 6, 'NL Sarda');
insert into course(crcode, title, dept, credits, teacher) 
	values ('HS303', 'Philosophy', 'Humanities', 6, 'Jolly Thoman');

create table student(rollno int, name varchar, hostelno int, cpi float, dept varchar);

insert into student values(170010001, 'Jay Bhai', 1, 8.3, 'Computer Science');
insert into student values(170010002, 'Ameya Vadnere', 3, 8.25, 'Computer Science');
insert into student values(170010003, 'Akshat Karani', 3, 9.31, 'Computer Science');
insert into student values(170020001, 'Hritik Kumar', 2, 7.69, 'Electrical');
insert into student values(170020002, 'Pheku', 3, 10, 'Electrical');
insert into student values(170020003, 'Divya', 1, 6.77, 'Computer Science');
insert into student values(170030001, 'Anna', 9, 7.88, 'Mechanical');

create table study(crcode varchar, rollno int, grade int);

insert into study values('CS313', 170010001, 8);
insert into study values('CS313', 170010002, 9);
insert into study values('CS313', 170010003, 8);
insert into study values('CS313', 170020001, 8);
insert into study values('CS313', 170020002, 6);
insert into study values('CS313', 170020003, 7);
insert into study values('CS313', 170030001, 10);

insert into study values('CS301', 170010001, 8);
insert into study values('CS301', 170010002, 9);
insert into study values('CS301', 170010003, 8);
insert into study values('CS301', 170020001, 7);
insert into study values('CS301', 170020002, 7);
insert into study values('CS301', 170020003, 8);
insert into study values('CS301', 170030001, 9);

insert into study values('EE401', 170010001, 9);
insert into study values('EE401', 170010002, 8);
insert into study values('EE401', 170010003, 10);
insert into study values('EE401', 170020001, 8);
insert into study values('EE401', 170020002, 7);
insert into study values('EE401', 170020003, 8);
insert into study values('EE401', 170030001, 8);

insert into study values('CS311', 170010001, 8);
insert into study values('CS311', 170010002, 9);
insert into study values('CS311', 170010003, 8);
insert into study values('CS311', 170020001, 8);
insert into study values('CS311', 170020002, 8);
insert into study values('CS311', 170020003, 7);
insert into study values('CS311', 170030001, 10);

insert into study values('HS303', 170010001, 9);
insert into study values('HS303', 170010002, 9);
insert into study values('HS303', 170010003, 8);
insert into study values('HS303', 170020001, 8);
insert into study values('HS303', 170020002, 7);
insert into study values('HS303', 170020003, 9);
insert into study values('HS303', 170030001, 8);

insert into study values('CS403', 170010001, 9);
insert into study values('CS403', 170010002, 9);
insert into study values('CS403', 170010003, 8);
insert into study values('CS403', 170020001, 8);
insert into study values('CS403', 170020002, 9);
insert into study values('CS403', 170020003, 6);
insert into study values('CS403', 170030001, 10);