#include <stdio.h>
#include <stdlib.h>
#include <new.h>

struct ListNode
{
    char symbol;
    ListNode *next=nullptr;
};

struct Stack{
    ListNode *head=nullptr;
};

ListNode *Create(char item)
{
    ListNode *Node=new (std::nothrow) ListNode;
    Node->symbol=item;

    return Node;
}

bool isEmpty(Stack* stack) {
    return stack->head == NULL;
}

void Push(Stack *stack, char data)
{
    ListNode *Node=Create(data);
    if(Node==nullptr)
    {
        printf("Allocation for node failed.");
        return;
    }
    Node->next=stack->head;
    stack->head=Node;
}

void Pop(Stack *stack)
{
    if(isEmpty(stack))
    {
        printf("Stack is empty.");
    }
    else
    {
        ListNode *temp=stack->head;
        stack->head=stack->head->next;
        delete(temp);
    }
}

void Print(const Stack *stack)
{
    ListNode *cur=stack->head;
    while(cur!=nullptr)
    {
        printf("%c ",cur->symbol);
        cur=cur->next;
    }
}

void Release(Stack *stack)
{
    ListNode *cur=stack->head;
    while (cur!=nullptr)
    {
        ListNode* temp = cur;
        cur=cur->next;
        delete(temp);
    }
    delete(cur);
}

//void Empty(Stack *stack)
//{
//
//}

char Top(Stack *stack)
{
    if(!isEmpty(stack))
    {
        return stack->head->symbol;
    }
    else
    {
        return ' ';
    }
}

int Size(const Stack *stack)
{
    ListNode *cur=stack->head;
    int size=0;
    while(cur!=nullptr)
    {
        size+=1;
        cur=cur->next;
    }

    return size;
}

int main()
{

    Stack stack;

    for(int i=0;i<5;i+=1)
    {
        Push(&stack,'A'+i);
    }

    Print(&stack);


    printf("\n%d",Size(&stack));
    printf("\n%c",Top(&stack));

    Release(&stack);


    return 0;
}
