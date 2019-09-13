select course_id, dept_name as course_d, prereq_id, prereq_d
from course natural join
(
	select prereq.course_id, prereq_id, dept_name as prereq_d
	from course join prereq on prereq.prereq_id=course.course_id
) as t1
where dept_name='Physics' and t1.prereq_d!='Physics';


-------------------------------------------------------------------------------------------


select A.course_id as main_course, A.prereq_id as main_prereq, B.prereq_id as second_prereq
from prereq A join prereq B on A.prereq_id=B.course_id;


-------------------------------------------------------------


select ID, name
from teaches natural join section natural join instructor
where time_slot_id='A';


-------------------------------------------------------------


select distinct ID from student natural join
(
	select ID, dept_name as course_dept
	from takes natural join course
	where grade='A+' and dept_name!='English'
) as t1
where dept_name='English';
/*answer is 78*/


------------------------------------------------------------


select ID as fac_id, count(course_id), sum(credits)
from teaches natural join section natural join course
where year=2010 or year=2011 group by ID;


-----------------------------------------------------------


with course_build_dept(course_id, sec_id, semester, year) as 
(
	select course_id, sec_id, semester, year
	from section natural join course
	where dept_name='Comp. Sci.' and building='Main'
)
select distinct course_id, name
from takes natural join student natural join course_build_dept
where dept_name='Physics';

/*or-or-or-or-or-or-or-or-or-or-or-or-or-or-or-or-or-or-or-or-*/

with course_build_dept(course_id, sec_id, semester, year) as 
(
	select course_id, sec_id, semester, year
	from section natural join course
	where dept_name='Comp. Sci.' and building='Main'
),
student_dept_takes(ID, name, course_id, sec_id, semester, year) as
(
	select ID, name, course_id, sec_id, semester, year
	from student natural join takes
	where dept_name='Physics'
)
select distinct course_id, name
from student_dept_takes natural join course_build_dept;


--------------------------------------------------------------

with building_instructor(ID, course_id, sec_id, semester, year, course_building) as 
(
	select ID, course_id, sec_id, semester, year, building
	from
	(
		select ID, count(building) as count_building_used
		from section natural join teaches
		group by ID	
	) as  t1 natural join teaches natural join section
	where count_building_used=1
),
building_dept_courses(ID, course_building, dept_building) as
(
	select ID, course_building, building
	from building_instructor natural join course natural join department
)
select ID, name
from building_dept_courses natural join instructor
where course_building=dept_building
order by id;

