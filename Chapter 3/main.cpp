#include <stdio.h>

typedef struct
{
    double w; // 重量
    double v; // 价值
} Object;

double opt_value = 0.0; // 最优值

// 本题要求实现
double Knapsack01(double W, Object s[], int x[], double f, int i, int n, int opt[]);

// 解析一行数字，返回数量
int parseLine(char *line, double arr[])
{
    int count = 0;
    char *ptr = line;
    double tmp;
    while (sscanf(ptr, "%lf", &tmp) == 1)
    {
        arr[count++] = tmp;
        // 移动指针到下一个数字
        while (*ptr != ' ' && *ptr != '\0' && *ptr != '\n')
            ptr++;
        while (*ptr == ' ')
            ptr++; // 跳过空格
    }
    return count;
}

int main()
{
    double W;
    scanf("%lf", &W);
    while (getchar() != '\n')
        ; // 清掉换行符

    char line[1000];
    double weightList[1100], valueList[1100];
    int n, m;

    // 读重量
    fgets(line, sizeof(line), stdin);
    n = parseLine(line, weightList);

    // 读价值
    fgets(line, sizeof(line), stdin);
    m = parseLine(line, valueList);

    Object s[1100];
    int x[1100] = {0};
    int opt[1100] = {0};
    for (int i = 0; i < n; i++)
    {
        s[i].w = weightList[i];
        s[i].v = valueList[i];
    }

    printf("%.2f\n", Knapsack01(W, s, x, 0.0, 0, n, opt));
    for (int i = 0; i < n; i++)
        printf("%d ", opt[i]);
    return 0;
}