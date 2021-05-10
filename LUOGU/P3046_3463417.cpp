#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>

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

using namespace std;

const int N = 1000 + 5;

int n;

int x[N];
int y[N];

struct point
{
  double x;
  double y;

  bool operator < (const point &rhs) const {
    return abs(x - rhs.x) < 1e-8 ? y - rhs.y < -1e-8: x - rhs.x < -1e-8;
  }

  point(double _x, double _y) {
    x = _x;
    y = _y;
  }
};

set <point> s;
set <point> id;

struct vec
{
  double x;
  double y;

  vec(double _x, double _y) {
    x = _x;
    y = _y;
  }
};

double dot(vec a, vec b) {
  return a.x * b.x + a.y * b.y;
}

vec operator + (vec a, vec b) {
  return vec(a.x + b.x, a.y + b.y);
}

vec operator - (vec a, vec b) {
  return vec(a.x - b.x, a.y - b.y);
}

vec operator / (vec a, double b) {
  return vec(a.x / b, a.y / b);
}

vec operator * (vec a, double b) {
  return vec(a.x * b, a.y * b);
}

inline point getpoint(vec x, vec y, vec p)
{
  // printf("%.3f %.3f\n", p.x, p.y);
  vec c = p - y;
  vec r = x - y;
  //printf("%.3f %.3f\n", r.x, r.y);
  //printf("%.3f %.3f\n", c.x, c.y);
  vec s = r * dot(r, c) / dot(r, r);
  //printf("%.3f %.3f\n", dot(r, c), dot(r, r));
  //printf("%.3f %.3f\n", s.x, s.y);
  s = (s - c) * 2.0;
  //s = 2.0 * s - c;
  // printf("%.3f %.3f\n", s.x, s.y);
  return point(p.x + s.x, p.y + s.y);
}

bool checker(vec xi, vec yi)
{
  point op(0, 0);
  //printf("%.3f %.3f %.3f %.3f\n", xi.x, xi.y, yi.x, yi.y);
				    
  for (int i = 0; i < n; ++i) {
    op = getpoint(xi, yi, vec((double) x[i], (double) y[i]));
    //printf("%.3f %.3f\n", op.x, op.y);
    if (s.find(op) == s.end()) {
      return false;
    }
  }
  return true;
}

int main()
{
  
  n = read();
  for (int i = 0; i < n; ++i) {
    x[i] = read();
    y[i] = read();
    s.insert(point(1.0 * x[i], 1.0 * y[i]));
  }
  int cnt = 0;
  for (int i = 1; i < n; ++i) {
    if (checker(vec(1.0 * x[0], 1.0 * y[0]), vec(1.0 * x[i], 1.0 * y[i]))) {
      //printf("%d\n", i);
      vec a = vec(x[0], y[0]);
      vec b = vec(x[i], y[i]);
      vec c = a - b;
      c = c / (sqrt(dot(c, c)));
      //printf("%.3f %.3f\n", c.x, c.y);
      if (c.x < 0) {
	c = c * -1;
      }
      id.insert(point(c.x, c.y));
    }
    vec r = vec(x[0] - x[i], y[0] - y[i]) / 2.0;
    vec k = vec(x[0] + x[i], y[0] + y[i]) / 2.0;
    vec c = vec(r.y, -r.x);
    if (checker(k, k + c)) {
      //printf("%.3f %.3f %.3f %.3f\n", r.x, r.y, (r + c).x, (r + c).y);
      c = c / (sqrt(dot(c, c)));
      //printf("%.3f %.3f\n", c.x, c.y);
      if (c.x < 0) {
	c = c * -1;
      }
      id.insert(point(c.x, c.y));
    }
  }
  printf("%d\n", id.size());
  return 0;
}
