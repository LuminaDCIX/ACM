#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;

typedef long long LL;
const int SZ = 600010;

struct sam_node{
    sam_node *ch[30], *par;
    int val,rcnt,rmax;
}T[SZ], *root, *last;

int Tcnt = 0;

sam_node* newnode(int x)
{
    sam_node *k = T + (Tcnt ++);
    k -> val = x;
    memset(k -> ch,0,sizeof(k -> ch));
    k -> par = 0;
    k -> rcnt = 0;
    k -> rmax = 0;
    return k;
}

void insert(int x,int id)
{
    sam_node *p = last,*np = newnode(last -> val + 1);
    np -> rmax = id;
    np -> rcnt = 1;
    while(p && !p -> ch[x])
        p -> ch[x] = np,p = p -> par;
    if(!p)
        np -> par = root;
    else
    {
        sam_node *q = p -> ch[x];
        if(q -> val == p -> val + 1)
        {
            np -> par = q;
        }
        else
        {
            sam_node *nq = newnode(p -> val + 1);
            memcpy(nq -> ch,q -> ch,sizeof(q -> ch));
            nq -> par = q -> par;
            q -> par = np -> par = nq;
            while(p && p -> ch[x] == q)
                p -> ch[x] = nq,p = p -> par;
        }
    }
    last = np;
}

int in[SZ];
queue<sam_node*> q;

void calc_right(char s[])
{
    for(int i = 1;i < Tcnt;i ++)
    {
        sam_node *k = T + i;
        in[k -> par - T] ++;
    }
    for(int i = 0;i < Tcnt;i ++)
        if(!in[i])
            q.push(T + i);
    while(q.size())
    {
        sam_node *f = q.front(); q.pop();
        if(!f -> par) continue;
        f -> par -> rcnt += f -> rcnt;
        f -> par -> rmax = max(f -> par -> rmax,f -> rmax);
        if(!-- in[f -> par - T])
            q.push(f -> par);
    }
}

bool vis[SZ];

LL ask(char s[])
{
    LL ans = 0;
    int l = strlen(s + 1),len = 0;
    sam_node *p = root;
    for(int i = l;i >= 1;i --)
    {
        int c = s[i] - 'a' + 1;
        while(p && !p -> ch[c])
            p = p -> par,len = p -> val;
        if(!p)
            p = root,len = 0;
        else
            p = p -> ch[c],len ++;
        if(i + len > p -> rmax)
        {
            if(i <= p -> rmax)
                ans = max(ans,((LL)p -> rmax - i + 1) * p -> rcnt);
            for(sam_node *fa = p -> par;fa && !vis[fa - T];fa = fa -> par)
            {
                 vis[fa-T]=1;
                if(fa -> rmax >= i && fa -> rmax < i + fa -> val)
                    ans = max(ans,((LL)fa -> rmax - i + 1) * fa -> rcnt);
            }
        }
     
    }
    return ans;
}



char s[SZ];

void init()
{
    root = newnode(0);
    last = root;
}

int main()
{
    //freopen("data.in","r",stdin);
    //freopen("data.out","w",stdout);
    init();
    scanf("%s",s + 1);
    int l = strlen(s + 1);
    for(int i = 1;i <= l;i ++)
        insert(s[i] - 'a' + 1,i);
    calc_right(s);
/*  for(int i = 1;i < Tcnt;i ++)
    {
        sam_node *k = T + i;
        printf("%d %d %d\n",k -> val,k -> rmax,k -> rcnt);
    }*/
    printf("%lld",ask(s));
    return 0;
}
