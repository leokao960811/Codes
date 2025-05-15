#ifndef STUDENT_H
#define STUDENT_H

constexpr int MaxNameLen = 20;
struct Student
{
    int id = 0;
    char name[MaxNameLen+1] = {};
    double score = 0;
};

bool Input(Student *s);
void Output(Student s);
#endif

