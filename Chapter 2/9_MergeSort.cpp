#include <stdio.h>
#include <stdlib.h>
const int MAXLEN = 5000 + 10;

// 本题要求实现
void Merge(int a[], int l, int mid, int r)
{
    int A[MAXLEN];
    for (int k = l; k <= r; k++)
        A[k] = a[k];

    int i = l, j = mid + 1, k = l;

    while (i <= mid && j <= r)
    {
        if (A[i] <= A[j])
            a[k++] = A[i++];
        else
            a[k++] = A[j++];
    }
    while (i <= mid)
        a[k++] = A[i++];
    while (j <= r)
        a[k++] = A[j++];
}
void MergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        MergeSort(a, l, mid);
        MergeSort(a, mid + 1, r);
        Merge(a, l, mid, r);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[MAXLEN];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    MergeSort(a, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}