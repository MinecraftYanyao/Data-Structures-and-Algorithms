#include <stdio.h>
#include <stdlib.h>
const int MAXLEN = 5000;

int isEqual(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
        {
            return 0;
        }
    }
    return 1;
}

void InsertionSortOnce(int a[], int l, int r)
{
    int i;
    for (i = 1; i <= r; i++)
    {
        if (a[i] < a[i - 1])
            break;
    }

    if (i > r)
        return;

    int key = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > key)
    {
        a[j + 1] = a[j];
        j--;
    }
    a[j + 1] = key;
}

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

int main()
{
    int n;
    scanf("%d", &n);
    int original[MAXLEN], intermediate[MAXLEN], A[MAXLEN];
    for (int i = 0; i < n; i++)
        scanf("%d", &original[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &intermediate[i]);

    int isInsertion = 1;

    int i;
    for (i = 1; i < n; i++)
    {
        if (intermediate[i] < intermediate[i - 1])
            break;
    }

    for (int j = i; j < n; j++)
    {
        if (intermediate[j] != original[j])
        {
            isInsertion = 0;
            break;
        }
    }

    if (isInsertion)
    {
        for (int i = 0; i < n; i++)
            A[i] = intermediate[i];

        InsertionSortOnce(A, 0, n - 1);
        printf("Insertion Sort\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
            A[i] = original[i];

        int step = 1;
        int found = 0;

        while (step < n && !found)
        {
            for (int i = 0; i < n; i += 2 * step)
            {
                int left = i;
                int right = (i + 2 * step - 1) < (n - 1) ? (i + 2 * step - 1) : (n - 1);
                int mid = (i + step - 1) < (n - 1) ? (i + step - 1) : (n - 1);

                if (mid < right)
                {
                    Merge(A, left, mid, right);
                }
            }

            if (isEqual(A, intermediate, n))
            {
                found = 1;
                step *= 2;
                for (int i = 0; i < n; i += 2 * step)
                {
                    int left = i;
                    int right = (i + 2 * step - 1) < (n - 1) ? (i + 2 * step - 1) : (n - 1);
                    int mid = (i + step - 1) < (n - 1) ? (i + step - 1) : (n - 1);
                    if (mid < right)
                    {
                        Merge(A, left, mid, right);
                    }
                }
            }
            step *= 2;
        }
        printf("Merge Sort\n");
    }

    for (int i = 0; i < n; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", A[i]);
    }
    return 0;
}