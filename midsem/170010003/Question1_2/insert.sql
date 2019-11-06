-- Question 2.

delete from book;
delete from student;
delete from issue;

insert into book values ('100', 'Introduction to Algorithms', 'Eduational', 'Thomas Cormen');
insert into book values ('101', 'Hitchikers Guide to Galaxy', 'Fictional', 'Douglas Adams');
insert into book values ('102', 'A song of Ice and First', 'Fictional', 'George R R Martin');
insert into book values ('103', 'Mein Kampf', 'Autobiography', 'Adolf Hitler');

insert into student values ('1', 'Akshat Karani', 'Computer Science', 2017, 'Fall');
insert into student values ('2', 'Jay Garchar', 'Mechanical', 2017, 'Spring');
insert into student values ('3', 'Ameya Vadnere', 'Electrival', 2016, 'Fall');
insert into student values ('4', 'Ojas Raundale', 'Civil', 2018, 'Spring');

-- Date is of format Month Day Year
insert into issue values ('1', '101', '09-01-2018', '09-15-2018');
insert into issue values ('2', '100', '08/17/2018', '08/22/2018');
insert into issue values ('3', '102', '02/28/2019', '03/04/2019');
insert into issue values ('1', '101', '05/11/2017', '05/16/2017');
insert into issue values ('2', '103', '06/17/2018', '06/29/2018');
insert into issue values ('1', '102', '08/17/2019', '08/22/2019');
