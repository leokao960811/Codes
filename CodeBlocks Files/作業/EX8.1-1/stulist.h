#ifndef STULIST_H
#define STULIST_H
#include "student.h"

constexpr int MaxNumStudents = 10;

struct List
{
    Student stu[MaxNumStudents];
    int size = 0;
};

bool AddStudent(List *list, Student s);
void Output(const List *list);
#endif
