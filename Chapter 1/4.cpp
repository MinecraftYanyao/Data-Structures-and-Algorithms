#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

const int MAXLEN = 1e5 + 10;
// 本题要求实现
void max_burst_location(int n, int h, int balloons[], int *pos, int *count){
    int min_pos=balloons[0]-h;
    int max_pos=balloons[n-1]-h;
    if(balloons[n-1]-balloons[0]<=h){
        if(balloons[0]-h<-1e6){
            *count=n;
            *pos=0-1e6;
            return;
        }
        *count=n;
        *pos=max_pos;
        return;
    }
    for(max_pos;min_pos<max_pos;max_pos--){
        int temp_count=0;
        for(int i=n-1;i>=0&&balloons[i]-max_pos>=0;i--){
            if(balloons[i]-max_pos<=h)
                temp_count+=1;
        }
        if(temp_count>=*count){
            *count=temp_count;
            *pos=max_pos;
        }
    }
    return;
}

int main() {
    int n, h;
    scanf("%d %d", &n, &h);

    int balloons[MAXLEN ];
    for (int i = 0; i < n; i++) {
        scanf("%d", &balloons[i]);
    }
    
    int position, count;
    max_burst_location(n, h, balloons, &position, &count);

    printf("%d %d", position, count);
    return 0;
}