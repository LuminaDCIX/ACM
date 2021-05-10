// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define siz(x) ((int)x.size())
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define foreach(e,x) for (__typeof(x.begin()) e=x.begin();e!=x.end();++e)
typedef long long ll;
typedef double db;
typedef map<int,int> mii;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
 
int read() {
  int f=1,x=0;char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
  return f*x;
}
 
// head
 
const int N = 100000 + 5;
const int MAX = 200000 + 5;
const double eps = 1e-18;
const double inf = 1e9;
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
 
int n;

int rnd() {
  static int seed = 20010330;
  seed += seed << 2 | 1;
  return seed % 10;
}

double f(double x, double k, double b) {
  return k * x + b;
}

 

class plane_intersection : public geometry {
public:

   vec intersection(vec a, vec b, vec x, vec y) {
     double s1 = (b - a) * (x - a);
     double s2 = (y - a) * (b - a);
     if (sgn(s1 + s2) == 0) {
       return a;
     }
     return vec((s1 * y.x + s2 * x.x) / (s1 + s2), (s1 * y.y + s2 * x.y) / (s1 + s2));
   }
  
  struct plane {
    vec x;
    vec y;
    double ang;
    plane() {
    }
    plane(vec _x, vec _y) : x(_x), y(_y) {
      ang = atan2(y.y - x.y, y.x - x.x);
    }
  } ext[4];

  plane_intersection(double mnx, double mxx, double mny, double mxy) {
    ext[0] = plane(vec(mnx, mny), vec(mxx, mny));
    ext[1] = plane(vec(mxx, mny), vec(mxx, mxy));
    ext[2] = plane(vec(mxx, mxy), vec(mnx, mxy));
    ext[3] = plane(vec(mnx, mxy), vec(mnx, mny));
  }
 
  static bool cmp(plane &a,  plane &b) {
    int d = sgn(a.ang - b.ang);
    if (d == 0) {
      return sgn((a.y - a.x) * (b.y - a.x)) < 0;
    } else {
      return d < 0;
    }
  }
 
  bool judge(plane a, plane b, plane x) {
    vec c = intersection(a.y, a.x, b.y, b.x);
    return sgn((x.y - x.x) * (c - x.x)) < 0;
  }
 
  vector<vec> solve(vector<plane> p) {
    n = (int) p.size();
    for (int i = 0; i < 4; ++i) {
      p.push_back(ext[i]);
      ++n;
    }
    sort(p.begin(), p.end(), cmp);
    
    vector<plane> s;
    s.push_back(p[0]);
    
    for (int i = 1; i < n; ++i) {
      if (sgn(p[i].ang - p[i - 1].ang) == 0) {
        continue;
      }
      s.push_back(p[i]);
    }
    
    n = (int) s.size();
    p = s;
    s.resize(n + 1);
    
    int head = 0;
    int tail = 0;
    s[tail++] = p[0];
    s[tail++] = p[1];
    
    for (int i = 2; i < n; ++i) {
      while (tail > head + 1 && judge(s[tail - 1], s[tail - 2], p[i])) {
        --tail;
      }
      while (tail > head + 1 && judge(s[head], s[head + 1], p[i])) {
        ++head;
      }
      s[tail++] = p[i];
    }
                                   

    while (tail > head + 1 && judge(s[tail - 2], s[tail - 1], s[head])) {
      --tail;
    }
    while (tail > head + 1 && judge(s[head], s[head + 1], s[tail - 1])) {
      ++head;
    }

    if (tail - head >= 3) {
      s[tail++] = s[head];
      vec k = intersection(s[head].x, s[head].y, s[head + 1].x, s[head + 1].y);
      vector<vec> res(1, k);
      for (int i = head + 1; i < tail; ++i) { 
        k = intersection(s[i].x, s[i].y, s[i + 1].x, s[i + 1].y);
        if (k == res.back()) {
          continue;
        }
        res.push_back(k);
      }
      return res;
    } else {
      return vector<vec>();
    }
  }
} hp(-inf, 0, -inf, inf);


int tot;
plane_intersection::plane p[MAX];
typedef geometry::vec vec;
void inst(db k,db b,int o) {
  db f1=0,f2=1;
  if (o&&f1>f2) swap(f1,f2);
  else if (!o&&f1<f2) swap(f1,f2);
  vec x=vec(f1,f(f1,k,b));
  vec y=vec(f2,f(f2,k,b));
  p[tot++] = plane_intersection::plane(y,x);
}

 
int main() {

  n=read();
  rep (i,0,n) {
    int x=read(),p=read(),q=read();
    inst(-x,(db)p/x,0);
    inst(-x,(db)q/x,1);
  }
  int ans=0,low=0,high=n;
  while (low<=high) {
    int mid=low+high>>1;
    if ((int)hp.solve(vector<plane_intersection::plane>(p, p + mid * 2)).size()) ans=mid,low=mid+1;
    else high=mid-1;
  }
  printf("%d\n",ans);
  return 0;
}
