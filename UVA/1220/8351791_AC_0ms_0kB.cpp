#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <map>
using namespace std;
#define Uni 0
#define Vir 1
int N, G[205][205], s, DP[205][2], Onl[205][2];
map<string, int> ID;
string Str1, Str2;

void build() {
    cin >> Str1;
    int tot = 0;
    ID[Str1] = ++tot;
    s = tot;
    for(int i = 1; i <= N - 1; i ++) {
        cin >> Str1 >> Str2;
        int v, u;
        if(!ID.count(Str1)) {
            ID[Str1] = ++tot;
            v = tot;
        } else v = ID[Str1];
        if(!ID.count(Str2)) {
            ID[Str2] = ++tot;
            u = tot;
        } else u = ID[Str2];
        G[u][v] = 1;
    }
}

int dfs(int u, int sel, int fa) {
    int &res = DP[u][sel];
    if(res > 0) return res;
    Onl[u][sel] = Uni;
    bool ok = 0;
    if(sel == 0) {
        int k = 0, onl = 0;
        for(int v = 1; v <= N; v ++)
          if(G[u][v] && v != fa) {
                int tem = -1; ok = 1;
                if(dfs(v, 1, u) > tem) tem = DP[v][1], k = v, onl = 1;
                if(dfs(v, 0, u) > tem) tem = DP[v][0], k = v, onl = 0;
                res += tem;
                if(DP[v][1] == DP[v][0]) Onl[u][sel] = Vir;//printf("%d Mark", v);
                if(Onl[k][onl] == Vir) Onl[u][sel] = Vir;
          }
    }
    if(sel == 1) {
        for(int v = 1; v <= N; v ++)
          if(G[u][v] && v != fa) {
              res += dfs(v, 0, u); ok = 1;
              if(Onl[v][0] == Vir) Onl[u][sel] = Vir;
          }
        res += 1;
    }
    if(ok == 0) {
        if(sel == 0) res = 0;
        if(sel == 1) res = 1;
        Onl[u][sel] = Uni;
    }
    //printf("DP[%d][%d] = %d Onl = %d\n", u, sel, DP[u][sel], Onl[u][sel]);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    while(cin >> N && N) {
        memset(DP, 0, sizeof(DP));
        memset(Onl, 0, sizeof(Onl));
        memset(G, 0, sizeof(G));
        ID.clear();
        build();
        int res = -1, onl = 0;
        if(dfs(1, 0, 0) > res) res = DP[1][0], onl = 0;
        if(dfs(1, 1, 0) > res) res = DP[1][1], onl = 1;
        printf("%d ",res);
        if(DP[1][0] == DP[1][1]) printf("No\n");
        else if(Onl[1][onl] == Uni) printf("Yes\n");
        else printf("No\n");
    }
    
    return 0;
}
