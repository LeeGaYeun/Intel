select * from person;


select name from person;

select a.ID,Name,Phone,Grade,Kor,ENg
	from person a inner join student b on a.Id = b.id