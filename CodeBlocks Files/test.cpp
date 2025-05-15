#include <stdio.h>
#include <stdlib.h>
#include <new.h>

struct ListNode
{
    char symbol;
    ListNode *next = nullptr;
};

//Linked list traversing
void Print(const ListNode *head)
{

    while(head!=nullptr)
    {
        printf("%c ",head->symbol);
        head=head->next;
    }
}

ListNode *Search(ListNode *cur, char target)
{
    while(cur!=nullptr)
    {
        if(cur->symbol==target)
        {
            break;
        }
        cur=cur->next;
    }
    return cur;
}

//ListNode *Insert()
//{
//
//}

int main()
{
    ListNode *head = nullptr, *cur=nullptr;

    for(int i=0;i<5;i+=1)
    {
        cur=new (std::nothrow) ListNode;
        cur->symbol='A'+i;

        cur->next=head;
        head=cur;

//        Print(head);
//        printf("\n");
    }

    Print(head);


//    while (head!=nullptr)
//    {
//        cur=head;
//        head=head->next;
//        Print(head);
//        printf("\n");
//
//        delete(cur);
//    }

    return 0;
}
