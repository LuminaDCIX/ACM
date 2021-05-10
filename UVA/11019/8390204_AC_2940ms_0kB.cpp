#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;

int Match[1010][1010], N, r, c, x, y;
int tot = 0;
struct node {
    int nxt[26], fail, flag, last;
    void clear() {
        memset(nxt, 0, sizeof(nxt));
        fail = flag = last = 0;
    }
} nod[10005];
int line[10005][105], pos[10005];
int res = 0, head, tail, root;
char s[1010][1010], model[105][105];
queue<int> Q;

void init() {
    root = 0, tot = 1;
    nod[root].clear();
    memset(Match, 0, sizeof(Match));
    res = 0;
}


void insert(char *s, int v) {
    int now = root;
    int n = strlen(s);
    for(int i = 0; i < n; i ++) {
        int c = s[i] - 'a';
        if(nod[now].nxt[c] == 0) {nod[now].nxt[c] = tot++; nod[tot - 1].clear(); pos[tot - 1] = 0;}
        now = nod[now].nxt[c];
    } 
    nod[now].flag = 1;
    line[now][++pos[now]] = v;
}

void build() {
    for(int i = 0; i < 26; i ++) {
        if(nod[root].nxt[i] == 0) {continue;}
        int x = nod[root].nxt[i];
        nod[x].fail = root;
        nod[x].last = root;
        Q.push(x);
    }
    while(!Q.empty()) {
        int p = Q.front(); Q.pop();
        for(int i = 0; i < 26; i ++) {
            if(nod[p].nxt[i] == 0) {nod[p].nxt[i] = nod[nod[p].fail].nxt[i]; continue;}
            int x = nod[p].nxt[i];
            int j = nod[p].fail;
            while(j && nod[j].nxt[i] == 0) j = nod[j].fail;
            j = nod[j].nxt[i];
            nod[x].fail = j;
            nod[x].last = nod[j].flag? j: nod[j].last;
            Q.push(x);
        }
    }
    return;
}

void input() {
    scanf("%d%d", &r, &c);
    init();
    for(int i = 1; i <= r; i ++) {
        scanf("%s", s[i]);
    }
    return;
}

void print(int r, int c, int j) {
    if(j) {
        for(int k = 1; k <= pos[j] ; k ++) {
                if(r - line[j][k] + 1> 0)Match[r + 1 - line[j][k]][c] ++;
    }
    print(r, c, nod[j].last); 
    }
}

void query(char *s, int r) {
    int now = root;
    int n = strlen(s);
    for(int i = 0; i < n; i ++) {
        int c = s[i] - 'a';
        now = nod[now].nxt[c];
        if(nod[now].flag) print(r, i - y + 2, now);
        else if(nod[now].last) print(r, i - y + 2, nod[now].last);
    }
    return;
}

void solve() {
    scanf("%d%d", &x, &y);
    for(int i = 1; i <= x; i ++) {
        scanf("%s", model[i]);
        insert(model[i], i);//query(model[i], j, i);
    }
    build();
    for(int i = 1; i <= r; i ++) query(s[i], i);
    for(int i = 1; i <= r; i ++)
        for(int j = 1; j <= c; j ++) if(Match[i][j] == x) res++;
}

int main() {
    scanf("%d", &N);
    while(N--) {
        input();
        solve();
        printf("%d\n", res);
    }
    return 0;
}