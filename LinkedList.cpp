#include <stdio.h>
#include <stdlib.h>
#include <new.h>

struct ListNode
{
    char symbol;
    ListNode *next = nullptr;
};

ListNode *Create(char item)
{
    ListNode *Node=new (std::nothrow) ListNode;
    Node->symbol=item;

    return Node;
}

//Linked list traversing
void Print(const ListNode *head)
{
    while(head!=nullptr)
    {
        printf("%c ",head->symbol);
        head=head->next;
    }
}

ListNode *Push(ListNode *head, char item)
{
    ListNode* node=Create(item);

    node->next=head;
    return node;
}

ListNode *Pop(ListNode *head)
{
    if(head==nullptr) {return nullptr;}

    ListNode* temp=head;
    head=head->next;

    delete temp;

    return head;
}

void Release(ListNode **head)
{
    ListNode *cur=*head;
    while (cur!=nullptr)
    {
        ListNode* temp = cur;
        cur=cur->next;
        delete(temp);
    }
}

int Size(const ListNode *head)
{
    int size=0;
    while(head!=nullptr)
    {
        size+=1;
        head=head->next;
    }

    return size;
}

char Top(const ListNode *head)
{
    if(head!=nullptr)
    {
        return head->symbol;
    }
    else
    {
        return NULL;
    }
}

ListNode *Search(ListNode *head, char target)
{
    while(head!=nullptr)
    {
        if(head->symbol==target)
        {
            break;
        }
        head=head->next;
    }
    return head;
}

//ListNode *Insert(ListNode* head, ListNode* item, int loc)
//{
//    int i=0;
//    while(i<loc)
//    {
//        head=head->next;
//    }
//
//    item->next=head;
//
//}

ListNode *Remove(ListNode *head, char target)
{
    if(!head){return nullptr;}
    if(head->symbol==target) {return head->next;}

    ListNode* prev=head;
    ListNode* cur=head->next;
    while(cur)
    {
        if(cur->symbol==target)
        {
            prev->next=cur->next;
            delete cur;

            return head;
        }
        prev=cur;
        cur=cur->next;
    }
    return head;
}

void AddAtEnd(ListNode *head, char item)
{
    ListNode *node=Create(item);

    if(head==nullptr)
    {
        head=node;
        return;
    }
    while(head->next!=nullptr)
    {
        head=head->next;
    }

    head->next=node;
}

int main()
{
    ListNode *head = nullptr, *cur=nullptr;

    for(int i=0;i<5;i+=1)
    {
        cur=Create('A'+i);

        cur->next=head;
        head=cur;
//        Print(head);
//        printf("\n");
    }

    Print(head);
    printf("\n%d\n", Size(head));

//    if(Search(head,'A')!=nullptr)
//    {
//        printf("A is found.\n");
//    }

    Remove(head, 'D');
    Print(head);
    printf("\n%d\n", Size(head));

    head=Push(head, 'F');
    Print(head);
    printf("\n%d\n", Size(head));

    AddAtEnd(head, 'G');
    Print(head);
    printf("\n%d\n", Size(head));

    head=Pop(head);
    Print(head);
    printf("\n%d\n", Size(head));

    printf("\n%c\n", Top(head));

    Release(&head);


    return 0;
}
