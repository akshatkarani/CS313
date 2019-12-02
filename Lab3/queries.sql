select dept_name, count(dept_name) as instructor_count, student_count 
from 
(
	select student.dept_name, count(student.dept_name) as student_count
	from student
	group by student.dept_name
) as f
natural join instructor 
group by dept_name, student_count 
order by instructor_count desc;

-------------------------------------------------------
select q1.ID
from
	(select ID, semester, year
	 from takes
	 where course_id in
	 	(select course_id
		 from course
		 where dept_name='Music')
	) as q1,
	(select ID, semester, year
	 from takes
	 where course_id in
	 	(select course_id
		 from course
		 where dept_name='Comp. Sci')
	) as q2
where q1.semester=q2.semester and q1.year=q2.year;
-------------------------------------------------------

select * from student where (ID) in
(select ID from takes where course_id = '802' and grade='B+');
------------------------------------------------------------

select a.id, a.dept_name, b.cnt from
(	select ID,  dept_name
	from takes natural join course where semester='Spring'
) as a
natural join
(	select dept_name, count(dept_name) as cnt from takes natural join course group by cnt);


select id, dept_name, count(dept_name) as cnt
from
(
	select id, dept_name
	from takes natural join course
	where semester='Spring' order by id
) as f
group by id, dept_name;