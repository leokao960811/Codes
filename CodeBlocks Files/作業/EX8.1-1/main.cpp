#include <stdio.h>
#include "student.h"
#include "stulist.h"

int main()
{
    List list;

    Student s;
    while (Input(&s)) // �Y��J������
    {
        AddStudent(&list, s); // �s�W�ǥ�
    }

    Output(&list); // ��X�Ҧ��ǥ�
}
