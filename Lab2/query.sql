select * from student where cpi>9 and hostelno=3;
select * from course where dept = 'Electrical' and teacher = 'Mahadeva Prasana';
select distinct name from student join study on student.rollno = study.rollno where grade=10 and student.cpi<9;

select distinct rollno, name from student natural join study natural join course 
where student.dept='Computer Science' and course.dept='Computer Science' and study.grade<8;

