/*本题要求实现一个程序，给定一个链表list和一个整数x，如果list中包含x，则输出x的值，若list不包含x，则按特定格式输出，具体格式见样例。

【输入形式】

输入第1行有一个整数n（n<=1000），表示链表长度。第2~n+1行，每行一个整数，表示链表中的每个元素。第n+2行为整数x。
【输出形式】

如果找到x所在节点，输出节点的值，否则，输出未找到。具体格式见样例。*/

#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
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

// 本题要求实现
Node *Search(Node *head, int x)
{
    while (head != NULL)
    {
        if (head->data == x)
            return head;
        head = head->next;
    }
    return head;
}

// 释放链表内存
void FreeList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void SelectSort(Node **head)
{
    Node *key = *head, *tp = NULL, *minpos = NULL;
    int temp;
    for (; key != NULL; key = key->next)
    {
        minpos = key;
        tp = key->next;
        for (; tp != NULL; tp = tp->next)
        {
            if (tp->data < minpos->data)
            {
                minpos = tp;
            }
        }
        temp = key->data;
        key->data = minpos->data;
        minpos->data = temp;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    Node *lst = CreateList(n);

    int x;
    scanf("%d", &x);
    Node *p = Search(lst, x);
    if (p != NULL)
    {
        printf("%d\n", p->data);
    }
    else
    {
        printf("%d is not found!\n", x);
    }

    FreeList(lst); // 释放内存
    return 0;
}