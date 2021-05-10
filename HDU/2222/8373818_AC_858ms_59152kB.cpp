#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int T, N;
char s[10010], t[1000010];
struct node {
    int nxt[26];
    int fail, cnt;
}nod[10000 * 50 + 10];
int tot, root;
int que[10000 * 50 + 10], tail, head, res;

inline void insert(char *s) {
    int now = root;
    for(int i = 0; s[i] != '\0'; i ++) {
        int x = s[i] - 'a';
        if(nod[now].nxt[x] == 0) nod[now].nxt[x] = tot ++;
        now = nod[now].nxt[x];
    }
    nod[now].cnt ++;
    return;
}

inline void build() {
    for(int i = 0; i < 26; i ++) {
        int p = nod[root].nxt[i];
        nod[p].fail = root;
        que[tail++] = p;
    }

    while(head < tail) {
        int p = que[head++];
        //printf("%d\n", p);
        for(int i = 0; i < 26; i ++) if(nod[p].nxt[i]) {
            int x = nod[p].nxt[i];
            int j = nod[p].fail;
            while(j != root && nod[j].nxt[i] == 0) j = nod[j].fail;
            if(nod[j].nxt[i]) j = nod[j].nxt[i];
            nod[x].fail = j;
            //nod[j].cnt = 0;
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
        while(tem != root && nod[tem].cnt != -1) {
            if(nod[tem].cnt) {
                res += nod[tem].cnt;
                nod[tem].cnt = -1;
            }
            tem = nod[tem].fail;
        }
    }
    /*for(int i = tail - 1; i >= 0; i --) {
        int p = nod[que[i]].fail;
        nod[p].cnt += nod[que[i]].cnt;
    }*/
    return;
} 

inline void input() {
    scanf("%d", &N);
    tot = 2, root = 1; res = 0;
    memset(nod, 0, sizeof(nod));
    memset(que, 0, sizeof(que)); tail = head = 0;
    while(N --) {
        scanf("%s", s);
        insert(s);
    }
    build();
}

inline void solve() {
    scanf("%s", t);
    query(t);
    printf("%d\n", res);
}

int main() {
    scanf("%d", &T);
    while(T --) {
        input();
        solve();
        //printf("%d", )
    }
    return 0;
}