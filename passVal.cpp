#include <stdio.h>
#include <time.h>

int fun(int val) {
    printf("%d\n", val);
    return 0;
}


int main () {
    int n = 4;
    for (int i = 1;i <= 100; i++) {
        int  timeNow = time(0);
        long value =  7*10000000000 + (3000000000-timeNow);
        printf("zset tlove_party_anchor_total_score_rank_201812 %d %ld\n", i, value);
    }
    //fun(-n);
    return n;
}
