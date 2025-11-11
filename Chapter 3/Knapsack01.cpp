#include <stdio.h>
#include <algorithm>
using namespace std;

typedef struct
{
    double w; // 重量
    double v; // 价值
} Object;

double opt_value = 0.0; // 最优值

// 本题要求实现
/**
 * @brief 使用回溯法（分支递归）解决0/1背包问题
 * @param W 背包总容量
 * @param s 物品数组
 * @param x 当前的解向量（记录当前路径的选择）
 * @param i 当前正在考虑的物品索引
 * @param n 物品总数
 * @param opt 用于存储最终的最优解向量
 */
void solve_knapsack_recursive(double W, Object s[], int x[], int i, int n, int opt[])
{
    // 基本情况：已经考虑完所有物品
    if (i == n)
    {
        double current_value = 0;
        double current_weight = 0;
        for (int k = 0; k < n; k++)
        {
            if (x[k] == 1)
            {
                current_value += s[k].v;
                current_weight += s[k].w;
            }
        }

        // 如果当前解是一个可行解（重量不超过W）并且价值更高
        if (current_weight <= W && current_value > opt_value)
        {
            opt_value = current_value; // 更新全局最优值
            // memcpy(opt, x, n * sizeof(int)); // 更新最优解路径
            for (int k = 0; k < n; k++)
            {
                opt[k] = x[k];
            }
        }
        return; // 结束当前路径的探索
    }

    // 分支1：不选择第i个物品
    x[i] = 0;
    solve_knapsack_recursive(W, s, x, i + 1, n, opt);

    // 分支2：选择第i个物品
    x[i] = 1;
    solve_knapsack_recursive(W, s, x, i + 1, n, opt);

    // (回溯)函数返回后，x[i] 的状态会在上一层调用中被重新设置，无需手动恢复
}

/**
 * @brief 题目要求的接口函数，作为启动递归的入口
 *        它调用真正的递归工作函数，并返回最终结果。
 */
double Knapsack01(double W, Object s[], int x[], int n, int opt[])
{
    // 调用真正的递归回溯函数来填充 opt_value 和 opt 数组
    // 从第0个物品开始决策
    solve_knapsack_recursive(W, s, x, 0, n, opt);

    // 返回找到的全局最优值
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

    printf("%.2f\n", Knapsack01(W, s, x, n, opt));
    for (int i = 0; i < n; i++)
        printf("%d ", opt[i]);
    return 0;
}