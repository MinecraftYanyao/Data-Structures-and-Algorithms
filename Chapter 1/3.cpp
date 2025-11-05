#include <stdio.h>
using namespace std;
// 本题要求
long long SumProducts(int n, int m){
    long long result=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            result=result+i*j;
        }
    }
    return result;
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%lld\n", SumProducts(n, m));
    return 0;
}