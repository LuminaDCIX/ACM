#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

char StrA[5010], StrB[5010];
int N, BeginA['Z' + 10], BeginB['Z' + 10], EndA['Z' + 10], EndB['Z'+ 10], Begin['Z' + 10], End['Z' + 10];
int DP[5010][5010][2];

int main(){
    scanf("%d", &N);
    while(N --){
        memset(BeginA, 0x3f3f, sizeof(BeginA));
        memset(BeginB, 0x3f3f, sizeof(BeginB));
        memset(EndA, -1, sizeof(EndA));
        memset(EndB, -1, sizeof(EndB));
        scanf("%s%s", StrA, StrB);
        int lenA = strlen(StrA);
        for(int i = 0; i < lenA; i ++){
            DP[i][0][0] = DP[i][0][1] = 0;
            if(BeginA[StrA[i]] == 0x3f3f3f3f) BeginA[StrA[i]] = i;
            EndA[StrA[i]] = i;
        }
        DP[lenA][0][0] = DP[lenA][0][1] = 0;
        int lenB = strlen(StrB);
        for(int i = 0; i < lenB; i ++){
            DP[0][i][0] = DP[0][i][1] = 0;
            if(BeginB[StrB[i]] == 0x3f3f3f3f) BeginB[StrB[i]] = i;
            EndB[StrB[i]] = i;
        }
        DP[0][lenB][0] = DP[0][lenB][1] = 0;
        for(int i = 0; i <= lenA; i ++) 
            for(int j = 0; j <= lenB; j ++) {
                if(i == 0 && j == 0) continue;
                int pre = 0, post = 0, markpre = 0, markpost = 0;
                if(i == 0) pre = 0x3f3f3f;
                else {
                    if(i - 1 == BeginA[StrA[i - 1]] && j - 1 < BeginB[StrA[i - 1]]) markpre++;
                    if(i - 1 == EndA[StrA[i - 1]] && j - 1 >= EndB[StrA[i - 1]]) markpre--;
                    pre = DP[i - 1][j][0] + markpre + DP[i - 1][j][1];
                }
                if(j == 0) post = 0x3f3f3f;
                else {
                    if(j - 1 == BeginB[StrB[j - 1]] && i - 1 < BeginA[StrB[j - 1]]) markpost++;
                    if(j - 1 == EndB[StrB[j - 1]] && i - 1 >= EndA[StrB[j - 1]]) markpost--;
                    post = DP[i][j - 1][0] + markpost + DP[i][j - 1][1]; 
                }
                if(pre < post) {
                    DP[i][j][0] = pre;
                    DP[i][j][1] = markpre + DP[i - 1][j][1];
                }
                if(post < pre) {
                    DP[i][j][0] = post;
                    DP[i][j][1] = markpost + DP[i][j - 1][1]; 
                }
                if(post == pre) {
                    DP[i][j][0] = pre;
                    DP[i][j][1] = min(markpre + DP[i - 1][j][1], markpost + DP[i][j - 1][1]);
                }

                //cout << i << " " << j << " " << DP[i][j][0] << " " << DP[i][j][1] << endl;
            }
            printf("%d\n", DP[lenA][lenB][0]);
    }
    return 0;
}
/*


*/