#include <stdio.h>
#include <stdlib.h>

// 链表节点
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 创建链表
Node *CreateList(int n)
{
    Node *head = NULL;
    Node *current = NULL;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->data = x;
        new_node->next = NULL;
        if (i == 0)
        {
            head = current = new_node;
        }
        else
        {
            current->next = new_node;
            current = current->next;
        }
    }
    return head;
}

// 打印链表
void PrintList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}

// 本题要求实现
void Remove(Node **head, int i)
{
    if (i < 1)
    {
        printf("position error\n");
        return;
    }
    if (*head == NULL)
    {
        printf("position error\n");
        return;
    }
    Node *temp = *head;
    Node *tp = temp;
    if (i == 1)
    {
        *head = tp->next;
        free(temp);
        return;
    }
    for (int j = 1; j < i; j++)
    {
        tp = temp;
        temp = tp->next;
        if (temp == NULL)
        {
            printf("position error\n");
            return;
        }
    }
    tp->next = temp->next;
    free(temp);
    return;
}

int main()
{
    int n;
    scanf("%d", &n);
    Node *lst = CreateList(n);

    int i;
    scanf("%d", &i);
    Remove(&lst, i);
    PrintList(lst);

    // 释放剩余链表内存
    Node *current = lst;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}