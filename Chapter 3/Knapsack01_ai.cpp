#include <stdio.h>

typedef struct
{
    double w; // 重量
    double v; // 价值
} Object;

double opt_value = 0.0; // 最优值

// 本题要求实现
double Knapsack01(double W, Object s[], int x[], double f, int i, int n, int opt[])
{
    // 计算当前已选物品的总重量 (items from 0 to i-1)
    // 注意：这是一个效率较低的操作，但在给定的函数签名下是必需的。
    double current_w = 0;
    for (int k = 0; k < i; k++)
    {
        if (x[k] == 1)
        {
            current_w += s[k].w;
        }
    }

    // 基本情况：已经考虑完所有物品 (i == n)
    if (i == n)
    {
        // 如果当前的总价值f超过了已知的最优值opt_value
        if (f > opt_value)
        {
            // 更新最优值
            opt_value = f;
            // 保存当前的最优解方案
            for (int k = 0; k < n; k++)
            {
                opt[k] = x[k];
            }
        }
        return opt_value;
    }

    // 递归步骤

    // 决策1：不将物品i放入背包
    x[i] = 0;
    Knapsack01(W, s, x, f, i + 1, n, opt);

    // 决策2：如果物品i可以放入背包，则尝试放入
    if (current_w + s[i].w <= W)
    {
        x[i] = 1;
        // 递归调用，价值增加 s[i].v
        Knapsack01(W, s, x, f + s[i].v, i + 1, n, opt);
    }

    // 对于初始调用(i=0)，在探索完所有可能性后，opt_value将包含最终结果。
    // 对于递归调用，返回值实际上被忽略了，但为了函数签名一致，我们返回当前的最优值。
    return opt_value;
}

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
