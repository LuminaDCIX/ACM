#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>
using namespace std;

map<string, int> Getnod;
int N, tot, root, que[150 * 70 + 10], head, tail, vis[150 * 70 + 10];
char S[155][75], t[1000000 + 10];
struct node {
    int nxt[26];
    int fail, mark, cnt;
}nod[150 * 70 + 10];

inline void insert(char *s) {
    string tem(s);
    if(Getnod.count(tem) > 0) return;
    int now = root;
    for(int i = 0; s[i] != '\0'; i ++) {
        int x = s[i] - 'a';
        if(nod[now].nxt[x] == 0) nod[now].nxt[x] = tot++;
        now = nod[now].nxt[x];
    }
    Getnod[tem] = now;
    nod[now].mark = 1;
}

inline void build() {
    for(int i = 0; i < 26; i ++) if(nod[root].nxt[i]){
        int p = nod[root].nxt[i];
        nod[p].fail = root;
        que[tail++] = p;
    }
    while(head < tail) {
        int p = que[head++];
        for(int i = 0; i < 26; i ++) if(nod[p].nxt[i]) {
            int x = nod[p].nxt[i];
            int j = nod[p].fail;
            while(j != root && nod[j].nxt[i] == 0) j = nod[j].fail;
            if(nod[j].nxt[i]) j = nod[j].nxt[i];
            nod[x].fail = j;
            que[tail++] = x;
        }
    }
    return;
}

inline void query(char *s) {
    int now = root;
    for(int i = 0; s[i] != '\0'; i ++) {
        int x = s[i] - 'a';
        while(now != root && nod[now].nxt[x] == 0) now = nod[now].fail;
        if(nod[now].nxt[x]) now = nod[now].nxt[x];
        int tem = now;
        while(tem != root) {
            nod[tem].cnt ++;
            tem = nod[tem].fail;
        }
        //for(int i = tail - 1; i >= 0; i --) {
        //    int q = nod[que[i]].fail;
        //    nod[que[i]].cnt += nod[q].cnt; 
        //}
    }
    return;
}

void init() {
    root = 1, tot = 2;
    head = tail = 0;
    Getnod.clear();
    memset(que, 0, sizeof(que));
    memset(nod, 0, sizeof(nod));
    memset(vis, 0, sizeof(vis));
}

void input() {
    init();
    for(int i = 1; i <= N; i ++) {scanf("%s", S[i]); insert(S[i]);}
    build();
}

void solve() {
    scanf("%s", t);
    query(t);
    int best = -1;
    for(int i = 1; i <= N; i ++) best = max(best, nod[Getnod[string(S[i])]].cnt);
    printf("%d\n", best);
    for(int i = 1; i <= N; i ++) {
        int x = Getnod[string(S[i])];
        if(vis[x]) continue;
        if(nod[x].cnt == best) {printf("%s\n", S[i]); vis[x] = 1;}
    }
}
int main() {
    while(scanf("%d", &N) && N) {
        input();
        solve();
    }
    return 0;
}