#include <cstdio>
#include <stack>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
stack <string> stk;
int n;
int in[29], out[29];
vector <pair<int, string> > e[1005];
bool vis[1005][1005];
string p[1005];
bool cmp(string a,string b) {
        return a<b;
}
void input() {
        string bar;
        for (int i = 1; i <= n; ++i) {
                cin>>p[i];
        }
        sort(p+1,p+1+n,cmp);
        for (int i = 1; i <= n; ++i) {
                string &bar=p[i];
                int u=bar[bar.length()-1]-'a';
                int v=bar[0]-'a';
                in[u]++;
                out[v]++;
                e[v].push_back(make_pair(u,bar));
        }
}
int S, T;
bool Find() {
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i <= 25; ++i) {
                if (in[i] - out[i] == 1)
                        sum1++;
                if (out[i] - in[i] == 1)
                        S = i,
                        sum2++;
                if (out[i]-in[i]>1) return false;
                if (in[i]-out[i]>1) return false;
        }
        if (sum1 + sum2 == 0) {
                for (int i = 0; i <= 25; ++i)
                        if (e[i].size()) {
                                S = i;
                                return true;
                        }
        }
        if (sum1 == 1 && sum2 == 1)
                return true;
        return false;
}
bool print(int S,int len) {
        if (len==n)
                return true;
        for (int i=0;i<e[S].size();++i) {
                if (vis[S][i])
                        continue;
                string bar=e[S][i].second;
                vis[S][i]=1;
                print(bar[bar.length()-1]-'a',len+1);
                stk.push(bar);
        }
        return false;
}

int main(){
        ios::sync_with_stdio(false);
        int T;
        cin>>T;
        while (T--) {
                memset(in, 0, sizeof(in));
                memset(out, 0, sizeof(out));
                memset(vis,0,sizeof(vis));
                for (int i=0;i<=1001;i++)
                        e[i].clear();
                while(!stk.empty())
                        stk.pop();
                S = -1;
                cin>>n;
                input();
                if (!Find())
                        cout<<"***";
                else {
                        /*for (int i=0;i<=25;++i) {
                                sort(e[i].begin(),e[i].end(),cmp);
                        }*/
                        print(S,0);
                        if(stk.size()==n) {
                                cout << stk.top();
                                stk.pop();
                                while(!stk.empty()) {
                                        cout <<'.';
                                        cout << stk.top();
                                        stk.pop();
                                }
                        }
                        else
                                cout<<"***";
                }
                cout << endl;
        }
        return 0;
}
