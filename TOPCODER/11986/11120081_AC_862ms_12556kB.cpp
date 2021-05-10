#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

class KingdomAndDice {
public:
	double newFairness(vector <int>, vector <int>, int);
};

const int N = 50 + 5;

vector < pair <int, int> > it;

int num[N << 1];
int tot;

int a[N];
int b[N];

int f[N][N * N];

int ci[N * N];
int vi[N * N];
int amt;

double KingdomAndDice::newFairness(vector <int> A, vector <int> B, int x) {
  int n = A.size();
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
  	a[i] = A[i];
  	b[i] = B[i];
  }
  for (int i = 0; i < n; ++i) {
    if (!a[i]) {
      ++cnt;
    } else {
      num[tot++] = a[i];
    }
  }
  for (int i = 0; i < n; ++i) {
    num[tot++] = b[i];
  }
  sort(b, b + n);
  sort(num, num + tot);
  int t = b[0] - (lower_bound(num, num + tot, b[0]) - num + 1);
  it.push_back(make_pair(0, t));
  b[n] = x + 1;
  for (int i = 0; i < n; ++i) {
    int l = b[i];
    int r = b[i + 1];
    int cnt = r - l - 1;
    cnt -= lower_bound(num, num + tot, r) - lower_bound(num, num + tot, l) - 1;
    it.push_back(make_pair(i + 1, cnt));
  }
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] == 0) {
      continue;
    }
    int k = a[i];
    sum += lower_bound(b, b + n, k) - b;
  }
  // cerr << "sum = " << sum << endl;
  // cerr << "cnt = " << cnt << endl;
  f[0][sum] = 1;
  int sz = it.size();
  // cerr << sz << endl;
  // for (int i = 0; i < sz; ++i) {
  //  cerr << it[i].first << " " << it[i].second << endl;
  // }
  for (int i = 0; i < sz; ++i) {
  	int now = 1;
  	int v = it[i].first;
  	int c = min(it[i].second, cnt);
  	while (now < c) {
      ci[amt] = now;
      vi[amt++] = now * v;
      c -= now;
      now <<= 1;
  	}
  	ci[amt] = c;
  	vi[amt++] = v * c;
  }
  for (int i = 0; i < amt; ++i) {
    for (int j = cnt; j >= ci[i]; --j) {
   	  for (int l = n * n; l >= vi[i]; --l) {
   	    f[j][l] |= f[j - ci[i]][l - vi[i]];
   	  }
    }
  }

  double p = 1.0;
  double mn = 1.0;
  for (int c = 0; c <= cnt; ++c) {
	for (int i = 0; i <= n * n; ++i) {
	  if (!f[c][i]) {
	    continue;
	  }
	  double t = (double) i / n / n;
	  if (abs(t - 0.5) < mn) {
	    mn = abs(t - 0.5);
	    p = t;
	  } else if ((abs(t - 0.5) - mn) < 1e-10) {
	    p = min(p, t);
	  }
	}
  }
  return p;
}