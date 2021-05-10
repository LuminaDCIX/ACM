#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <vector>
using namespace std;
const int prime = 1000003;
int ok;
struct Code {
	int hash, belong, e[4][4];
	char f;
	int coding() {
		hash = 0;
		for(int i = 1; i <= 3; i ++)
			for(int j = 1; j <= 3; j ++)
				 hash = hash * 10 + e[i][j];
                return hash;
	}
	void decoding() {
		for(int i = 3; i >= 1; i --)
			for(int j = 3; j >= 1; j --)
				e[i][j] = hash % 10, hash /= 10;
	}
	Code(int x,int k[][4], int b, char fc) {
		hash = x;
		memcpy(e, k, sizeof(int) * 16);
		if(k[1][1] < 1 || k[1][1] > 9) decoding();
		if(x == 0) coding();
		belong = b;
		f = fc;
	}
	Code() {
                hash = 0;
                memset(e,0,sizeof(e));
                belong = 0;
                f = '0';
	}
};
vector<Code> h[1000004];
queue<Code> q1, q2;
void print_pre(Code x,int m, int n) {
        x.coding();
        int t = x.hash % prime, k;
        for(int i = 0; i < h[t].size(); i ++) {
                if(h[t][i].hash == x.hash) k = i;
        }
        if(h[t][k].f == 's') return ;
        else {
                if(h[t][k].f == 'u') swap(x.e[m + 1][n],x.e[m][n]),print_pre(x, m + 1, n);
                if(h[t][k].f == 'd') swap(x.e[m - 1][n],x.e[m][n]),print_pre(x, m - 1, n);
                if(h[t][k].f == 'l') swap(x.e[m][n + 1],x.e[m][n]),print_pre(x, m, n + 1);
                if(h[t][k].f == 'r') swap(x.e[m][n - 1],x.e[m][n]),print_pre(x, m, n - 1);
        }
        putchar(h[t][k].f);
}
void print_post(Code x, int m, int n) {
        x.coding();
        int t = x.hash % prime, k;
        for(int i = 0; i < h[t].size(); i ++) {
                if(h[t][i].hash == x.hash) k = i;
        }
        if(h[t][k].f == 'u') putchar('d');
        if(h[t][k].f == 'd') putchar('u');
        if(h[t][k].f == 'l') putchar('r');
        if(h[t][k].f == 'r') putchar('l');
        if(h[t][k].f == 's') return ;
        else {
                if(h[t][k].f == 'u') swap(x.e[m + 1][n],x.e[m][n]),print_post(x, m + 1, n);
                if(h[t][k].f == 'd') swap(x.e[m - 1][n],x.e[m][n]),print_post(x, m - 1, n);
                if(h[t][k].f == 'l') swap(x.e[m][n + 1],x.e[m][n]),print_post(x, m, n + 1);
                if(h[t][k].f == 'r') swap(x.e[m][n - 1],x.e[m][n]),print_post(x, m, n - 1);
        }
}
void print(Code x, char f, int v) {
        int m, n;
        for(int i = 1; i <= 3; i ++)
                for(int j = 1; j <= 3;j ++)
                        if(x.e[i][j] == 9) m = i, n = j;
        if(v == 1) {
                print_pre(x, m, n);
                if(f == 'u') putchar('d');
                if(f == 'd') putchar('u');
                if(f == 'l') putchar('r');
                if(f == 'r') putchar('l');
                if(f == 'u') swap(x.e[m + 1][n],x.e[m][n]),print_post(x, m + 1, n);
                if(f == 'd') swap(x.e[m - 1][n],x.e[m][n]),print_post(x, m - 1, n);
                if(f == 'l') swap(x.e[m][n + 1],x.e[m][n]),print_post(x, m, n + 1);
                if(f == 'r') swap(x.e[m][n - 1],x.e[m][n]),print_post(x, m, n - 1);
        }
        if(v == 2) {
                Code t;
                memcpy(&t, &x, sizeof(Code));
                if(f == 'u') swap(t.e[m + 1][n],t.e[m][n]),print_pre(t, m + 1, n);
                if(f == 'd') swap(t.e[m - 1][n],t.e[m][n]),print_pre(t, m - 1, n);
                if(f == 'l') swap(t.e[m][n + 1],t.e[m][n]),print_pre(t, m, n + 1);
                if(f == 'r') swap(t.e[m][n - 1],t.e[m][n]),print_pre(t, m, n - 1);
                putchar(f);
                print_post(x, m, n);
        }
        ok = 1;
}
void inh(Code x, char f, int v) {
        int t = x.hash % prime;
        x.belong = v, x.f = f;
        for(int i = 0; i < h[t].size(); i ++) {
                if(h[t][i].hash == x.hash) {
                        if(h[t][i].belong == v) return;
                        if(h[t][i].belong != v) {print(x, f, h[t][i].belong); return ;}
                }
        }
        if(v == 1) q1.push(x);
        if(v == 2) q2.push(x);
        h[t].push_back(x);
}
void inq(Code x,int v) {
        int m, n;
        Code l;
        for(int i = 1; i <= 3; i ++)
                for(int j = 1; j <= 3; j ++)
                        if(x.e[i][j] == 9) m = i, n = j;
        memcpy(&l, &x, sizeof(Code));
        if(m - 1 >= 1) {
                swap(l.e[m - 1][n], l.e[m][n]);
                l.coding(); inh(l, 'u', v);
                swap(l.e[m - 1][n], l.e[m][n]);
        }
        if(m + 1 <= 3) {
                swap(l.e[m + 1][n], l.e[m][n]);
                l.coding(); inh(l, 'd', v);
                swap(l.e[m + 1][n], l.e[m][n]);
        }
        if(n - 1 >= 1) {
                swap(l.e[m][n - 1], l.e[m][n]);
                l.coding(); inh(l, 'l', v);
                swap(l.e[m][n - 1], l.e[m][n]);
        }
        if(n + 1 <= 3) {
                swap(l.e[m][n + 1], l.e[m][n]);
                l.coding(); inh(l, 'r', v);
                swap(l.e[m][n + 1], l.e[m][n]);
        }
}
void solve() {
	while(!q1.empty() && !q2.empty()) {
                Code x;
                memcpy(&x, &q1.front(), sizeof(Code));
                q1.pop();
                if(!ok) inq(x, 1); else return;
                memcpy(&x, &q2.front(), sizeof(Code));
                q2.pop();
                if(!ok) inq(x, 2); else return;
	}
	printf("unsolvable");
}
void input() {
	char e[4][4]; int d[4][4], f[4][4];
	for(int i = 1; i <= 3; i ++)
		for(int j = 1; j <= 3; j ++) {
			cin >> e[i][j];
		}
	for (int i = 1; i <= 3; i ++)
		for(int j = 1; j <= 3; j ++) {
                        f[i][j] = (i - 1) * 3 + j;
			if(e[i][j] == 'x') {d[i][j] = 9; continue;}
			d[i][j] = e[i][j] - '0';
		}
        Code S(0, d, 1, 's'), E(123456789, f, 2, 'e');
        q1.push(S);
        q2.push(E);
        h[S.hash % prime].push_back(S);
        h[E.hash % prime].push_back(E);
}

int main() {
	input();
	solve();
	return 0;
}
