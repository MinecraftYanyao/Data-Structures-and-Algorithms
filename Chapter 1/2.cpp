#include <stdio.h>

// 本题要求实现
long long SumUp(int n){
    long long sum=2;
    int j=2,i=2;
    while (i<=n*n){
        sum+=i;
        i++;
    }
    while (j<=n){
        sum+=j;
        j++;    
    }
    return sum;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", SumUp(n));
    return 0;
}