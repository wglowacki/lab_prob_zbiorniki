use schoolDatabase


IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='classrooms') 
begin
	DROP TABLE classrooms;
end


IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='subjects') 
begin
	DROP TABLE subjects;
end

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='building') 
begin
	DROP TABLE building;
end

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='students') 
begin
	DROP TABLE students;
end

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='payment') 
begin
	DROP TABLE payment;
end

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='attendance') 
begin
	DROP TABLE attendance;
end

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='exam_result') 
begin
	DROP TABLE exam_result;
end


IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='parents') 
begin
	DROP TABLE parents;
end

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='grades') 
begin
	DROP TABLE grades;
end

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES where TABLE_NAME='teachers') 
begin
	DROP TABLE teachers;
end

--TABLE grades
CREATE TABLE exam_result
(
   id INT NOT NULL,
   grade_name VARCHAR(20) NOT NULL,
   CONSTRAINT grade_pk PRIMARY KEY (id),
   CONSTRAINT grade_unique UNIQUE(grade_name)
)
insert into exam_result values(1, 'NIEDOSTATECZNY')
insert into exam_result values(2, 'DOPUSZCZAJACY')
insert into exam_result values(3, 'DOSTATECZNY')
insert into exam_result values(4, 'DOBRY')
insert into exam_result values(5, 'BARDZO DOBRY')
insert into exam_result values(6, 'CELUJACY')

--TABLE students
CREATE TABLE students
(
   pesel INT NOT NULL,
   name VARCHAR(50) NOT NULL,
   surname VARCHAR(50) NOT NULL,
   classroom_id INT NOT NULL,
   CONSTRAINT student_pk PRIMARY KEY (pesel)
)

insert into students values(4, 'Wojciech', 'Glowacki', 1)
insert into students values(935259, 'Dariusz', 'Cionek', 2)
insert into students values(615259, 'Sonia', 'Sowula', 3)
insert into students values(435251, 'Karolina', 'Jedzrzejczyk', 1)
insert into students values(932252, 'Jacek', 'Bak', 2)
insert into students values(950353, 'Tomasz', 'Tomaszewski', 3)
insert into students values(950524, 'Janusz', 'Bednarek', 1)
insert into students values(925266, 'Konrad', 'William', 2)
insert into students values(325277, 'Delle', 'Alli', 3)
insert into students values(978253, 'Wojciech', 'Mann', 1)
insert into students values(235156, 'Ela', 'Kolt', 2)
insert into students values(846582, 'Karol', 'Kapusta', 3)
insert into students values(258653, 'Monika', 'Macka', 1)
insert into students values(286835, 'Jan', 'Wiadro', 2)

--TABLE attendance
CREATE TABLE attendance
(
	attendance_id					INT				NOT NULL,
	date							DATE			NOT NULL,
	student_id						INT   		NOT NULL,
	student_status					BIT,
	CONSTRAINT attendace_pk			PRIMARY KEY(attendance_id),
	CONSTRAINT student_id_fk FOREIGN KEY (student_id) REFERENCES students(pesel),
)

--TABLE teacher
CREATE TABLE teachers
(
   teacher_id					  INT			NOT NULL,
   name							  VARCHAR(50)			NOT NULL,
   surname						  VARCHAR(50)			NOT NULL,
   class_level					  INT					NOT NULL,
   CONSTRAINT teacher_pk		  PRIMARY KEY (teacher_id),
)
insert into teachers values(2314, 'Ewa', 'Rzonca', 3)
insert into teachers values(6146, 'Monika', 'Dranka', 1)
insert into teachers values(8576, 'Mateusz', 'Koper', 2)

--TABLE classroom
CREATE TABLE classroom
(
	classroom_id				INT				NOT NULL,
	academic_year				VARCHAR(12)		NOT NULL,
	teacher_id					INT				NOT NULL,
	CONSTRAINT classroom_id_pk PRIMARY KEY (classroom_id),
	
)

insert into classroom values(63, '2017/18', 3)

--TABLE grade
CREATE TABLE grades
(
	grade_id					INT				NOT NULL,
	name						VARCHAR(25)		NOT NULL,
	CONSTRAINT grade_id_pk PRIMARY KEY (grade_id)
)

--TABLE subjects
CREATE TABLE subjects
(
	subject_id					INT				NOT NULL ,
	sub_name						VARCHAR(20)		NOT NULL,
	teacher_id					INT				NOT NULL,
	CONSTRAINT subject_id_pk PRIMARY KEY (subject_id)
)

insert into subjects values(1, 'matematyka', 2)
insert into subjects values(2, 'biologia', 1)

go
create trigger tr_delete on students
for delete
as
begin
	delete.students where students.classroom_id = (select classroom_id from deleted)
end


SELECT name as 'Nazwisko', surname as 'Imie' FROM [schoolDB].[dbo].[students]
