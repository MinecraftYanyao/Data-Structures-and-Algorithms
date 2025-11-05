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

// 本题要求实现。
int Insert(Node **head, int i, int x)
{
    if (i < 1)
        return 0;
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = x;
    if (i == 1)
    {
        newNode->next = *head;
        *head = newNode;
        return 1;
    }
    Node *temp = *head;
    for (int j = 1; j < i - 1; j++)
    {
        if (temp == NULL)
        {
            free(newNode);
            return 0;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        free(newNode);
        return 0;
    }

    // 插入新节点
    newNode->next = temp->next;
    temp->next = newNode;
    return 1;
}

int main()
{
    int n;
    scanf("%d", &n);
    Node *lst = CreateList(n);

    int i, x;
    scanf("%d %d", &i, &x);
    if (Insert(&lst, i, x))
    {
        PrintList(lst);
    }
    else
    {
        printf("position error\n");
    }

    // 释放链表内存
    Node *current = lst;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}