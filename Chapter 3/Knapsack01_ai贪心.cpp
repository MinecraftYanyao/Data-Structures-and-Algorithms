#include <stdio.h>
#include <stdlib.h> // 用于 qsort
#include <string.h> // 用于 memcpy

// 扩展结构体，用于排序时保留原始索引
typedef struct
{
    double w;           // 重量
    double v;           // 价值
    double ratio;       // 单位重量价值 (v/w)
    int original_index; // 原始位置
} Item;

double opt_value = 0.0; // 全局最优值
int final_opt[1100];    // 全局最优解方案

// qsort 的比较函数，按单位重量价值降序排序
int compare_items(const void *a, const void *b)
{
    Item *item_a = (Item *)a;
    Item *item_b = (Item *)b;
    if (item_a->ratio < item_b->ratio)
        return 1;
    if (item_a->ratio > item_b->ratio)
        return -1;
    return 0;
}

/**
 * @brief 计算上界函数 (用于最优性剪枝)
 * @param i 当前物品索引
 * @param n 物品总数
 * @param W 背包总容量
 * @param current_w 当前已装入重量
 * @param current_v 当前已装入价值
 * @param items 已经按性价比排好序的物品数组
 * @return 从当前状态出发可能达到的理论最大价值
 */
double bound(int i, int n, double W, double current_w, double current_v, Item items[])
{
    double remaining_w = W - current_w;
    double upper_bound = current_v;
    int k = i;
    // 贪心填充剩余容量
    while (k < n && items[k].w <= remaining_w)
    {
        remaining_w -= items[k].w;
        upper_bound += items[k].v;
        k++;
    }
    // 如果背包未满，用下一个物品的片段填满
    if (k < n)
    {
        upper_bound += items[k].ratio * remaining_w;
    }
    return upper_bound;
}

/**
 * @brief 带有剪枝的回溯递归核心函数
 * @param i 当前物品索引
 * @param n 物品总数
 * @param W 背包总容量
 * @param current_w 当前已装入重量
 * @param current_v 当前已装入价值
 * @param items 排好序的物品数组
 * @param x 当前解路径
 */
void backtrack(int i, int n, double W, double current_w, double current_v, Item items[], int x[])
{
    // 基本情况：所有物品都已考虑
    if (i == n)
    {
        if (current_v > opt_value)
        {
            opt_value = current_v;
            // memcpy(final_opt, x, n * sizeof(int));
            for (int k = 0; k < n; k++)
                final_opt[k] = x[k];
        }
        return;
    }

    // 分支1：尝试装入第i个物品
    // 可行性剪枝：只有当装得下时才考虑
    if (current_w + items[i].w <= W)
    {
        x[i] = 1;
        backtrack(i + 1, n, W, current_w + items[i].w, current_v + items[i].v, items, x);
    }

    // 分支2：不装入第i个物品
    // 最优性剪枝：只有当“不装”这条路仍有可能超越当前最优解时才探索
    if (bound(i + 1, n, W, current_w, current_v, items) > opt_value)
    {
        x[i] = 0;
        backtrack(i + 1, n, W, current_w, current_v, items, x);
    }
}

/**
 * @brief 题目要求的接口函数，作为启动器
 */
double Knapsack01(double W, Object s[], int n, int opt[])
{
    Item items[1100];
    int x[1100] = {0}; // 临时解向量

    // 1. 预处理：计算性价比，保存原始索引
    for (int i = 0; i < n; i++)
    {
        items[i].w = s[i].w;
        items[i].v = s[i].v;
        items[i].ratio = (s[i].w > 0) ? (s[i].v / s[i].w) : 0;
        items[i].original_index = i;
    }

    // 2. 按性价比降序排序
    qsort(items, n, sizeof(Item), compare_items);

    // 3. 初始化全局变量并启动回溯
    opt_value = 0.0;
    backtrack(0, n, W, 0.0, 0.0, items, x);

    // 4. 结果恢复：将排序后的解(final_opt)映射回原始顺序(opt)
    for (int i = 0; i < n; i++)
    {
        // final_opt[i] 对应的是排序后第i个物品的选择
        // items[i].original_index 是这个物品的原始位置
        opt[items[i].original_index] = final_opt[i];
    }

    return opt_value;
}

// --- main函数部分保持不变，但为了完整性在此贴出 ---
int parseLine(char *line, double arr[])
{
    int count = 0;
    char *ptr = line;
    double tmp;
    while (sscanf(ptr, "%lf", &tmp) == 1)
    {
        arr[count++] = tmp;
        while (*ptr != ' ' && *ptr != '\0' && *ptr != '\n')
            ptr++;
        while (*ptr == ' ')
            ptr++;
    }
    return count;
}

int main()
{
    double W;
    scanf("%lf", &W);
    while (getchar() != '\n')
        ;

    char line[1000];
    double weightList[1100], valueList[1100];
    int n, m;

    fgets(line, sizeof(line), stdin);
    n = parseLine(line, weightList);

    fgets(line, sizeof(line), stdin);
    m = parseLine(line, valueList);

    Object s[1100];
    int opt[1100] = {0};
    for (int i = 0; i < n; i++)
    {
        s[i].w = weightList[i];
        s[i].v = valueList[i];
    }

    // 调用入口函数，注意参数已简化
    printf("%.2f\n", Knapsack01(W, s, n, opt));
    for (int i = 0; i < n; i++)
        printf("%d ", opt[i]);

    getchar(); // 等待按键，防止终端秒退
    return 0;
}