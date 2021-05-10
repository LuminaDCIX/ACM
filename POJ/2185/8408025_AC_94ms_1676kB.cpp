#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

char ver[80][10005], hor[10005][80];
int next[10005];
int r, c, x, y, ans;

void Getexthor() {
    int a, i = 0;
    next[0] = c;
    while(!strcmp(ver[i], ver[i + 1]) && i + 1 < c) i ++;
    next[1] = i;
    a = 1;
    if(a + i == c) x = a;
    for(i = 2; i < c; i ++) {
        if(next[i - a] + i < next[a] + a) next[i] = next[i - a];
        else {
            int j = next[a] + a - i;
            if(j < 0) j = 0;
            while(i + j < c && !strcmp(ver[i + j], ver[j])) j++;
            next[i] = j;
            a = i;
            if(!x && a + j == c) x = a;
        }
    }
    if(x == 0) x = c;
}

void Getextver() {
    int a, i = 0;
    next[0] = r;
    while(!strcmp(hor[i], hor[i + 1]) && i + 1 < r) i ++;
    next[1] = i;
    a = 1;
    if(a + i == r) y = a;
    for(i = 2; i < r; i ++) {
        if(next[i - a] + i < next[a] + a) {next[i] = next[i - a];}
        else {
            int j = next[a] + a - i;
            if(j < 0) j = 0;
            while(i + j < r && !strcmp(hor[i + j], hor[j])) j++;
            next[i] = j;
            a = i;
            if(!y && a + j == r) y = a;
        }
    }
    if(y == 0) y = r;
}
void input() {
    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; i ++) {
        scanf("%s", hor[i]);
        int n = strlen(hor[i]);
        for(int j = 0; j < n; j ++) {
            ver[j][i] = hor[i][j];
        }
    }
}

void solve() {
    Getexthor();
    Getextver();
    ans = x * y;
}

void output() {
    printf("%d\n", x * y);
}

int main() {
    input();
    solve();
    output();
}