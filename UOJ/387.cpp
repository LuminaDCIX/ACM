#include <bits/stdc++.h>

using namespace std;

inline int read() {
        int f=1;
        int x=0;
        char ch=getchar();
        for (;!isdigit(ch);ch=getchar()) {
                f=(ch=='-')?-1:1;
        }
        for (;isdigit(ch);ch=getchar()) {
                x=x*10+ch-'0';
        }
        return f*x;
}

int n;
int m;

const int N=1e5+5;

int fa[N];
vector<int> g[N];

int siz[N];
int son[N];
int sonmx[N];
int dep[N];

void dfs(int u) {
        son[u]=(int)g[u].size();
        siz[u]=1;
        for (auto v:g[u]) {
                dfs(v);
                dep[u]=max(dep[v]+1,dep[u]);
                siz[u]+=siz[v];
                sonmx[u]=max(sonmx[u],sonmx[v]);
        }
        sonmx[u]=max(sonmx[u],son[u]);
}

vector<vector<int> > doit1() {
        priority_queue<pair<int, int> > que;
        que.push(make_pair(son[0],0));
        vector<vector<int> > ans;
        while (!que.empty()) {
                vector<int> cur;
                while (!que.empty()&&(int)cur.size()<m) {
                        int u=que.top().second;
                        cur.push_back(u);
                        que.pop();
                }
                ans.push_back(cur);
                for (auto v:cur) {
                        for (auto i:g[v]) {
                                que.push(make_pair(son[i],i));
                        }
                }
        }
        return ans;
}

vector<vector<int> > doit2() {
        priority_queue<pair<int, int> > que;
        que.push(make_pair(siz[0],0));
        vector<vector<int> > ans;
        while (!que.empty()) {
                vector<int> cur;
                while (!que.empty()&&(int)cur.size()<m) {
                        int u=que.top().second;
                        cur.push_back(u);
                        que.pop();
                }
                ans.push_back(cur);
                for (auto v:cur) {
                        for (auto i:g[v]) {
                                que.push(make_pair(siz[i],i));
                        }
                }
        }
        return ans;
}

vector<vector<int> > doit3() {
        priority_queue<pair<int, int> > que;
        que.push(make_pair(sonmx[0],0));
        vector<vector<int> > ans;
        while (!que.empty()) {
                vector<int> cur;
                while (!que.empty()&&(int)cur.size()<m) {
                        int u=que.top().second;
                        cur.push_back(u);
                        que.pop();
                }
                ans.push_back(cur);
                for (auto v:cur) {
                        for (auto i:g[v]) {
                                que.push(make_pair(sonmx[i],i));
                        }
                }
        }
        return ans;
}

vector<vector<int> > doit4() {
        priority_queue<pair<int, int> > que;
        que.push(make_pair(dep[0],0));
        vector<vector<int> > ans;
        while (!que.empty()) {
                vector<int> cur;
                while (!que.empty()&&(int)cur.size()<m) {
                        int u=que.top().second;
                        cur.push_back(u);
                        que.pop();
                }
                ans.push_back(cur);
                for (auto v:cur) {
                        for (auto i:g[v]) {
                                que.push(make_pair(dep[i],i));
                        }
                }
        }
        return ans;
}

vector<vector<int> > doit5() {
        priority_queue<pair<int, int> > que;
        que.push(make_pair(dep[0]+sonmx[0],0));
        vector<vector<int> > ans;
        while (!que.empty()) {
                vector<int> cur;
                while (!que.empty()&&(int)cur.size()<m) {
                        int u=que.top().second;
                        cur.push_back(u);
                        que.pop();
                }
                ans.push_back(cur);
                for (auto v:cur) {
                        for (auto i:g[v]) {
                                que.push(make_pair(dep[i]+sonmx[i],i));
                        }
                }
        }
        return ans;
}


int main() {
        n=read();
        m=read();
        fa[0]=-1;
        for (int i=1;i<n;++i) {
                fa[i]=read()-1;
                g[fa[i]].push_back(i);
        }
        
        dfs(0);

        auto ans=doit1();
        auto t=doit2();
        if ((int)ans.size()>(int)t.size()) {
                ans=t;
        }
        t=doit3();
        if ((int)ans.size()>(int)t.size()) {
                ans=t;
        }
        t=doit4();
        if ((int)ans.size()>(int)t.size()) {
                ans=t;
        }
        t=doit5();
        if ((int)ans.size()>(int)t.size()) {
                ans=t;
        }
        
        printf("%d\n",ans.size());
        for (auto v:ans) {
                printf("%d ",(int)v.size());
             for (auto u:v) {
                        printf("%d ",u+1);
                }
                puts("");
        }
        return 0;
}
