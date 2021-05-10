#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

inline int read()
{
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

struct point {
  int x;
  int y;
};

bool cmp(point &a, point &b) {
  return a.x < b.x;
}

bool cmp1(point &a, point &b) {
  return a.y < b.y;
}

const int N = 100000 + 5;

int n;

point p[N];

int main()
{
  n = read();
  for (int i = 0; i < n; ++i) {
    p[i].x = read();
    p[i].y = read();
  }
  sort(p, p + n, cmp);
  int ans = n; 
  for (int z = 0; z < n; ++z) {
    
    sort(p, p + n, cmp);
    int cut = p[z].x + 1;

  
    int siz[4];
    memset(siz, 0, sizeof(siz));
  
    for (int i = 0; i < n; ++i) {
      if (p[i].x < cut) {
	++siz[2];
      } else {
	++siz[3];
      }
    }


    sort(p, p + n, cmp1);
    int ptr = -1;
    vector <int> v;
    for (int i = 0; i < n; ++i) {
      v.push_back(p[i].y);
    }
    v.erase(unique(v.begin(), v.end()), v.end());

    ans = min(ans, max(siz[2], siz[3]));
    int k1 = siz[2];
    int k2 = siz[3];
    //    printf("%d %d\n", siz[2], siz[3]);
  
    for (int i = 0; i < (int) v.size(); ++i) {
      int k = v[i] + 1;

      while (ptr + 1 < n && p[ptr + 1].y < k) {
	if (p[ptr + 1].x < cut) {
	  ++siz[0];
	  --siz[2];
	} else {
	  ++siz[1];
	  --siz[3];
	}
	++ptr;
      }
      //    printf("%d %d %d %d\n", siz[0], siz[1], siz[2], siz[3]);
      ans = min(ans, max(max(siz[0], siz[1]), max(siz[2], siz[3])));
    }
  }
  
  printf("%d\n", ans);
  return 0;
}
