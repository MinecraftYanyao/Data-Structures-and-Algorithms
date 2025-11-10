#include <stdio.h>

int partition(int a[], int low, int high)
{
    int key = a[low];
    while (low < high)
    {
        while (low < high && a[high] >= key)
        {
            high--;
        }
        a[low] = a[high];
        while (low < high && a[low] <= key)
        {
            low++;
        }
        a[high] = a[low];
    }
    a[low] = key;
    return low;
}
// 本题要求实现
void QuickSort(int a[], int l, int r)
{
    if (l < r)
    {
        int pos = partition(a, l, r);
        QuickSort(a, l, pos - 1);
        QuickSort(a, pos + 1, r);
    }
}

const int MAXLEN = 5000 + 10;
int main()
{
    int n;
    scanf("%d", &n);
    int a[MAXLEN];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    QuickSort(a, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}