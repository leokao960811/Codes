#include <stdio.h>
#include "student.h"
#include "stulist.h"

int main()
{
    List list;

    Student s;
    while (Input(&s)) // 若輸入完整資料
    {
        AddStudent(&list, s); // 新增學生
    }

    Output(&list); // 輸出所有學生
}
