#include <bits/stdc++.h>

using namespace std; 

const int N = 1e5 + 5;

double bun;
double inc;
double dam;

int n;
int m;

double mx[N];
double st[N];
double lst[N];
double reg[N];

struct change {
  double tim;
  double enm;
  double hel;
};

change op[N];

bool cmp(change a, change b) {
  return a.tim < b.tim;
}

int main() {
  scanf("%d %d", &n, &m);
  scanf("%lf %lf %lf", &bun, &inc, &dam);
  vector <pair <double, double> > v;
  bool flg = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%lf %lf %lf", &mx[i], &st[i], &reg[i]);
    if (mx[i] >= dam) {
      flg = 1;
    }   
  }
  if (!flg && inc) {
    puts("-1");
    return 0;
  }
  for (int i = 0; i < m; ++i) {
    scanf("%lf %lf %lf", &op[i].tim, &op[i].enm, &op[i].hel);
  }
  sort(op, op + m, cmp);
  for (int i = 0; i < m; ++i) {
    double tim = op[i].tim;
    double enm = op[i].enm;
    double hel = op[i].hel;
    int p = (int) enm - 1;
    if ((tim - lst[p]) * reg[p] + st[p] > dam) {
      if (reg[p] != 0) {
        double r = lst[p] + floor ((dam - st[p]) / reg[p]);
        double t = lst[p] + ceil ((mx[p] - st[p]) / reg[p]);
        if (t <= r) {
         v.push_back(make_pair(lst[p], tim - 1));
        } else if (r >= 0) {
         v.push_back(make_pair(lst[p], r - (r == tim)));
        }
      }
    } else {
      v.push_back(make_pair(lst[p], tim - 1));
    }
    st[p] = hel; 
    lst[p] = tim;
  }
  for (int i = 0; i < n; ++i) {
    if (st[i] > dam) {
      continue;
    }
    if ((mx[i] <= dam || reg[i] == 0) && inc != 0) {
      puts("-1");
      return 0;
    }
    if (reg[i] == 0) {
      v.push_back(make_pair(lst[i], 1e9));  
    } else if (reg[i] != 0) {
      double t = lst[i] + ceil((mx[i] - st[i]) / reg[i]);
      double r = lst[i] + floor((dam - st[i]) / reg[i]);
      if (t <= r) {
        v.push_back(make_pair(lst[i], 1e9));
      } else {
        v.push_back(make_pair(lst[i], r));
      }
    }
  }              
  vector <double> f;
  for (int i = 0; i < v.size(); ++i) {
    f.push_back(v[i].first);
    f.push_back(v[i].second);
  }
  sort(f.begin(), f.end());
  int cnt = 0;
  map <double, int> mp;
  map <int, double> re;
  f.erase(unique(f.begin(), f.end()), f.end());
  for (int i = 0; i < f.size(); ++i) {
    // cerr << f[i] << endl;
    mp[f[i]] = i;
    re[i] = f[i];
  }
  vector <pair <int, int> > c;
  for (int i = 0; i < v.size(); ++i) {
    c.push_back(make_pair(mp[v[i].first], -1));
    c.push_back(make_pair(mp[v[i].second], 1));
  } 
  sort(c.begin(), c.end());
  long long ans = 0;
  for (int i = 0; i < c.size(); ++i) {
    ans = max(ans, (long long) ((long long) cnt * floor((bun + re[c[i].first] * inc))));
    if (c[i].second == -1) {
     ++cnt;
    } else {
     --cnt;
    }
   }
   printf("%lld\n", ans);   
  return 0;
}
