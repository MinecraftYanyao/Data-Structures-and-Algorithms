#include <stdio.h>

// 本题要求实现
void ShellSort(int a[], int l, int r)
{
    for (int gap = r / 2; gap >= 1; gap /= 2)
    {
        for (int i = gap; i <= r; i++)
        {
            int key = a[i];
            int j = i - gap;
            while (j >= 0 && a[j] > key)
            {
                a[j + gap] = a[j];
                j -= gap;
            }
            a[j + gap] = key;
        }
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

    ShellSort(a, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}