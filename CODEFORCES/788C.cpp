#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
int n, k;
const int bas = 1001;
int cst[1000005];
bool inq[2005];
int vis[2005], ans;
queue <pair<int, int> > que;
void input(){
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= k; ++i){
                scanf("%d", &cst[i]);
                cst[i] -= n;
                if (!inq[cst[i] + bas]) {
                        que.push(make_pair(cst[i] + bas, 1));
                        inq[cst[i] + bas] = 1;
                }
                else {
                        i--;
                        k--;
                }
                if (!cst[i]) {
                        ans = 1;
                        return;
                }
        }
        return;
}
void solve(){
        if (ans) return;
        while (!que.empty()){
              int t = que.front().first;
              int len = que.front().second;
              que.pop();
              //printf("%d %d\n", t, len);
              if (vis[t]) continue;
              vis[t] = 1;
              inq[t] = 0;
              for (int i = 1; i <= k; ++i){
                        if(cst[i] == cst[i - 1])
                                continue;
                        if (cst[i] + t > 2001)
                                continue;
                        if (cst[i] + t < 1)
                                continue;
                        if (!vis[cst[i] + t]
                            && !inq[cst[i] + t]){
                                que.push(make_pair(cst[i] + t, len + 1));
                                inq[cst[i] + t] = 1;
                        }
                        if (cst[i] + t == bas) {
                                ans = len + 1;
                                return;
                        }
              }
        }
        return;
}
int main(){
        input();
        solve();
        if (ans == 0)
                printf("-1\n");
        else
                printf("%d\n", ans);
        return 0;
}

