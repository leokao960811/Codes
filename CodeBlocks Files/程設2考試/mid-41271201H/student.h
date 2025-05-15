#ifndef STUDENT_H
#define STUDENT_H

constexpr int StuMaxCourses=100;
constexpr int UnivMaxStudents=100;

struct Student
{
    char id[10]={};
    char courses[StuMaxCourses][30]={};
    int sz=0;

};

struct University
{
    Student stu[UnivMaxStudents];
    int sz=0;
};

bool AddCourse(Student *stu, const char course[]);

Student* AddStudent(University *univ, const char stu_id[]);
Student* FindStudent(University *univ, const char stu_id[]);

#endif
