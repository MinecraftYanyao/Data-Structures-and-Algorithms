#include <stdio.h>
#include <stdlib.h>

// 链表节点
typedef struct ListNode
{
    int data;
    struct ListNode *next;
} ListNode;

// 本题要求实现
int Find(ListNode *head, int m, int *err)
{
    if (head == NULL)
    {
        *err = 1;
        return 0;
    }

    if (m <= 0)
    {
        *err = 1;
        return 0;
    }
    ListNode *fast = head, *slow = head;
    *err = 0;
    for (int i = 1; i < m; i++)
    {
        fast = fast->next;
        if (!fast)
        {
            *err = 1;
            return 0;
        }
    }
    while (fast->next)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow->data;
}

// 释放链表
void FreeList(ListNode *head)
{
    ListNode *current = head;
    while (current)
    {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    int m, n;
    scanf("%d", &m);

    // 先读取链表数据长度
    int data[1000];
    n = 0;
    while (scanf("%d", &data[n]) == 1)
    {
        n++;
        if (getchar() == '\n')
            break; // 读到行尾停止
    }

    // 创建链表
    ListNode *head = NULL;
    ListNode *current = NULL;
    for (int i = 0; i < n; i++)
    {
        ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
        new_node->data = data[i];
        new_node->next = NULL;
        if (!head)
        {
            head = current = new_node;
        }
        else
        {
            current->next = new_node;
            current = current->next;
        }
    }

    int err;
    int result = Find(head, m, &err);
    if (err)
    {
        printf("ERROR\n");
    }
    else
    {
        printf("%d\n", result);
    }

    FreeList(head);
    return 0;
}