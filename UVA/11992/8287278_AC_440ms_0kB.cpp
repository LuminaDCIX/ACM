#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define lson o << 1
#define rson o << 1 | 1
#define M (L + ((R - L) >> 1))
#define INF 1e6+10
//Product by MiracleEEEE
int sum[25][2005010], minv[25][2005010], maxv[25][2005010], addv[25][2005010], setv[25][2000010], x;
int r, c, m, x1, x2, Y1, y2;
void maintain(int v, int o, int L, int R) {
	sum[v][o] = minv[v][o] = maxv[v][o] = 0;
	if (setv[v][o] >= 0) {
		sum[v][o] = (setv[v][o]) * (R - L + 1);
		minv[v][o] = setv[v][o];
		maxv[v][o] = setv[v][o];
	} else if (R > L) {
		sum[v][o] = sum[v][lson] + sum[v][rson];
		minv[v][o] = min(minv[v][lson], minv[v][rson]);
		maxv[v][o] = max(maxv[v][lson], maxv[v][rson]);
	}
	sum[v][o] += addv[v][o] * (R - L + 1); maxv[v][o] += addv[v][o]; minv[v][o] += addv[v][o];
}
void build(int v, int o, int L, int R) {
	if (L == R) {
		scanf("%d", &addv[v][o]);
	} else {
		build(v, lson, L, M);
		build(v, rson, M + 1, L);
	}
	maintain(v, o, L, R);
}
bool input() {
	//for (int i = 1; i <= r; i++) build(i, 1, 1, c);
	memset(setv, -1, sizeof(setv));
	memset(minv, 0, sizeof(minv));
	memset(maxv, 0, sizeof(maxv));
	memset(sum, 0, sizeof(sum));
	memset(addv, 0, sizeof(addv));
	return true;
}

void pushdown(int v, int o) {
	if (setv[v][o] >= 0) {
		setv[v][lson] = setv[v][rson] = setv[v][o];
		addv[v][lson] = addv[v][rson] = 0;
		setv[v][o] = -1;
	}
	if (addv[v][o] > 0) {
		addv[v][lson] += addv[v][o];
		addv[v][rson] += addv[v][o];
		addv[v][o] = 0;
	}
}
void add_v(int v, int o, int L, int R) {
	if (Y1 <= L && y2 >= R) {
		addv[v][o] += x;
	}
	else {
		pushdown(v, o);
		if (Y1 <= M) add_v(v, lson, L, M); else maintain(v, lson, L, M);
		if (M < y2) add_v(v, rson, M + 1, R); else maintain(v, rson, M + 1, R);
	}
	maintain(v, o, L, R);
}

void set_v(int v, int o, int L, int R) {
	if (Y1 <= L && y2 >= R) {
		setv[v][o] = x;
		addv[v][o] = 0;
	} else {
		pushdown(v, o);
		if (Y1 <= M) set_v(v, lson, L, M); else maintain(v, lson, L, M);
		if (y2 > M) set_v(v, rson, M + 1, R); else maintain(v, rson, M + 1, R);
	}
	maintain(v, o, L, R);
}
int _min = 0, _max = 0, _sum = 0;
void query(int v, int o, int L, int R, int add) { 
	if (setv[v][o] >= 0) {
		_min = min(setv[v][o] + addv[v][o] + add, _min);
		_max = max(setv[v][o] + addv[v][o] + add, _max);
		_sum += (setv[v][o] + addv[v][o] + add) * (min(R, y2) - max(L, Y1) + 1);
	} else 
	if (Y1 <= L && y2 >= R) {
		_min = min(minv[v][o] + add, _min);
		_max = max(maxv[v][o] + add, _max);
		_sum += (sum[v][o]) + add * (R - L + 1);
	} else {
		if (Y1 <= M) query(v, lson, L, M, add + addv[v][o]);
		if (y2 > M) query(v, rson, M + 1, R, add + addv[v][o]);
	}
}
bool solve() {
	while (m--) {
		int q;  scanf("%d", &q);
		switch (q)
		{
		case 1:
			scanf("%d %d %d %d %d", &x1, &Y1, &x2, &y2, &x);
			for (int i = x1; i <= x2; i++) add_v(i, 1, 1, c);
			break;
		case 2:
			scanf("%d %d %d %d %d", &x1, &Y1, &x2, &y2, &x);
			for (int i = x1; i <= x2; i++) set_v(i, 1, 1, c);
			break;
		case 3:
			scanf("%d %d %d %d", &x1, &Y1, &x2, &y2);
			_sum = 0, _min = INF, _max = -INF; 
			for (int i = x1; i <= x2; i++) query(i, 1, 1, c, 0);
			printf("%d %d %d\n", _sum, _min, _max);
			break;
		}
	}
	return true;
}
int main()
{
	while (scanf("%d%d%d", &r, &c, &m) != EOF) {
		input();
		solve();
	}
	return 0;
}
