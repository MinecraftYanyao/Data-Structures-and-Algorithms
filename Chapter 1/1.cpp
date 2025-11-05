#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

long long GCD(long long x, long long y){
    for(long long i=min(x,y);i>=1;i--){
        if(x%i==0&&y%i==0){
            return i;
        };
    };
    return 1;

}

int main() {
    long long x, y;
    scanf("%lld %lld", &x, &y);
    printf("%lld\n", GCD(x, y));
    return 0;
}