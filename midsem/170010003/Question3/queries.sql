-- Question 3. a)

select student_id, name from student
where student_id not in (select distinct student_id from issue);

-- Question 3. b)
select student_id, name from student natural join
(select student_id from issue where date_returned - date_issue > 10) as t;