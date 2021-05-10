#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
typedef double db;

const int N=50000+5;
const double eps = 1e-7;

class geometry {
public:
  static int sgn(double x) {
    if (fabs(x) < eps) {
      return 0;
    }
    return x < 0 ? -1 : 1;
  }
  
  struct vec {
    double x;
    double y;
    vec(double _x = 0, double _y = 0) : x(_x), y(_y) {};
    
    vec operator + (vec v) {
      return vec(x + v.x, y + v.y);
    }
    vec operator - (vec v) {
      return vec(x - v.x, y - v.y);
    }
    double operator * (vec v) {
      return x * v.y - y * v.x;
    }
    double operator ^ (vec v) {
      return x * v.x + y * v.y;
    }
    bool operator == (vec v) {
      return sgn(x - v.x) == 0 && sgn(y - v.y) == 0;
    }
  };
  double len(vec a) {
    return sqrt(a ^ a);
  }
};


int read() {
  int f=1,x=0;char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
  return f*x;
}

int n;

int top;
geometry::vec stk[N];
geometry::vec p[N];

class convex_hall : public geometry {
public:
  static bool cmp(const vec &a, const vec &b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
  }

  vector<vec> solve(vector<vec> p) {
    sort(p.begin(), p.end(), cmp);
    
    int n = p.size();
    vector<vec> stk(n + 1);
    int top = 0;
    
    for (int i = 0; i < n; ++i) {
      while (top > 1 && sgn((stk[top - 1] - stk[top - 2]) * (p[i] - stk[top - 1])) <= 0) {
        --top;
      }
      stk[top++] = p[i];
    }
    int t = top;
    for (int i = n - 2; i >= 0; --i) {
      while (top > t && sgn((stk[top - 1] - stk[top - 2]) * (p[i] - stk[top - 1])) <= 0) {
        --top;
      }
      stk[top++] = p[i];
    }
    --top;
    stk.resize(top);
    return stk;
  }
} ddd;

class rotating_caliper : public geometry {
public:
  double solve(vector<vec> v) {
    int j = 1;
    double ans = 0;
    v.push_back(v[0]);
    int n = v.size();
    for (int i = 0; i < n - 1; ++i) {
      while ((v[i + 1] - v[i]) * (v[j] - v[i]) < (v[i + 1] - v[i]) * (v[j + 1] - v[i])) {
        j = (j + 1) % n;
      }
      ans = max(ans, max(len(v[i] - v[j]), len(v[i + 1] - v[j])));
    }
    return ans;
  }
} ccc;

double sqr(double x) {return x * x;}
int main() {
  n=read();
  rep (i,0,n) p[i].x=read(),p[i].y=read();
  vector<geometry::vec> v = ddd.solve(vector<geometry::vec>(p, p + n));

  printf("%d\n",(int)sqr(ccc.solve(v)));
  return 0;
}
