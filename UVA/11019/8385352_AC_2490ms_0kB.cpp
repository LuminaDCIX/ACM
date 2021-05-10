#include <cstdio>  
#include <cstring>  
#include <queue>  
using namespace std;  
  
const int MAXNODE = 10005;  
const int SIGMA_SIZE = 127;  
const int N = 1005;  
const int M = 105;  
  
struct AutoMac {  
  
    int ch[MAXNODE][SIGMA_SIZE];  
    int val[MAXNODE][105];  
    int vn[MAXNODE];  
    int next[MAXNODE];  
    int last[MAXNODE];  
    int sz;  
  
    int n, m, x, y;  
    char nm[N][N], xy[M];  
    int rc[N][N];  
  
    void init() {  
    sz = 1;  
    memset(ch[0], 0, sizeof(ch[0]));  
    }  
  
    int idx(char c) {  
    return c;  
    }  
  
    void insert(char *s, int v) {  
    int u = 0;  
    int n = strlen(s);  
    for (int i = 0; i < n; i++) {  
        int c = idx(s[i]);  
        if (!ch[u][c]) {  
        memset(ch[sz], 0, sizeof(ch[sz]));  
        memset(val[sz], 0, sizeof(val[sz]));  
        vn[sz] = 0;  
        ch[u][c] = sz++;  
        }  
        u = ch[u][c];  
    }  
    val[u][vn[u]++] = v;  
    }  
  
    void getnext() {  
    next[0] = 0;  
    queue<int> Q;  
    for (int c = 0; c < SIGMA_SIZE; c++) {  
        int u = ch[0][c];  
        if (u) {next[u] = 0; Q.push(u); last[u] = 0;}  
    }  
    while (!Q.empty()) {  
        int r = Q.front(); Q.pop();  
        for (int c = 0; c < SIGMA_SIZE; c++) {  
        int u = ch[r][c];  
        if (!u) {  
            ch[r][c] = ch[next[r]][c];  
            continue;  
        }  
        Q.push(u);  
        int v = next[r];  
        while (v && !ch[v][c]) v = next[v];  
        next[u] = ch[v][c];  
        last[u] = val[next[u]] ? next[u] : last[next[u]];  
        }  
    }  
    }  
  
    void print(int r, int c, int j) {  
    if (j) {  
        for (int i = 0; i < vn[j]; i++) {  
        if (r - val[j][i] >= 0)  
            rc[r - val[j][i]][c]++;  
        }  
        print(r, c, last[j]);  
    }  
    }  
  
    void find(int row) {  
    int u = 0;  
    int n = strlen(nm[row]);  
    for (int i = 0; i < n; i++) {  
        int c = idx(nm[row][i]);  
        u = ch[u][c];  
        if (val[u]) print(row, i - y + 1, u);  
        else if (last[u]) print(row, i - y + 1, last[u]);  
    }  
    }  
      
    void solve() {  
    memset(rc, 0, sizeof(rc));  
    scanf("%d%d", &n, &m);  
    for (int i = 1; i <= n; i++)  
        scanf("%s", nm[i]);  
    scanf("%d%d", &x, &y);  
    for (int i = 1; i <= x; i++) {  
        scanf("%s", xy);  
        insert(xy, i);  
    }  
    getnext();  
    for (int i = 1; i <= n; i++)  
        find(i);  
    int ans = 0;  
    for (int i = 0; i < n; i++) {  
        for (int j = 0; j < m; j++) {  
        if (rc[i][j] == x)  
            ans++;  
        }  
    }  
    printf("%d\n", ans);  
    }  
};  
  
AutoMac gao;  
  
int main() {  
    int t;  
    scanf("%d", &t);  
    while (t--) {  
    gao.init();  
    gao.solve();  
    }  
    return 0;  
}  