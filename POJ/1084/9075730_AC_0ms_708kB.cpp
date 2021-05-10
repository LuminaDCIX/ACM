#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
int n, k;
typedef long long ll;
int maxn, cntsqu, totstick;
vector <int> squ[65];
vector <int> cre[65];
bool succ;
int exi[65];
int tmp[65];
int ans, deep;
void build()
{
  for (int x = 1; x <= n; ++x) {
    int target = maxn - x * n - x * (n + 1) - x + 1;
    int bar = 0;
    for (int i = 1; i <= target; ++i) {
      cntsqu++;
      bar++;
      for (int j = 0; j < x; ++j) {
        squ[cntsqu].push_back(i + j);
        squ[cntsqu].push_back(i + x * (2 * n + 1) + j);
        cre[i + j].push_back(cntsqu);
        cre[i + x * (2 * n + 1) + j].push_back(cntsqu);
      }
      for (int j = 0; j < x; ++j) {
        squ[cntsqu].push_back(i + j * (n + 1) + (j + 1) * n);
        squ[cntsqu].push_back(i + j * (n + 1) + (j + 1) * n + x);
        cre[i + j * (n + 1) + (j + 1) * n].push_back(cntsqu);
        cre[i + j * (n + 1) + (j + 1) * n + x].push_back(cntsqu);
      }
      if (!(n - bar)) {
        bar = 0;
        i += n + 1;
      }
    }
  }
  return;
}
int h()
{
  int ret = 0;
  for (int i = 1; i <= cntsqu; ++i) {
    tmp[i] = exi[i];
  }
  for (int i = 1; i <= cntsqu; ++i) if (!tmp[i]) {
    ret++;
    tmp[i] -= squ[i].size();
    for (int j = 0; j < squ[i].size(); ++j) {
      for (int l = 0; l < cre[squ[i][j]].size(); ++l) {
        tmp[cre[squ[i][j]][l]]--;
      }
    }
  }
  return ret;
}
void dfs(int sum)
{
  if (sum + h() > deep) {
    return;
  } 
  int temp = 1;
  while (exi[temp] < 0 && temp <= cntsqu) {
    temp++;
  }
  if (temp > cntsqu) {
    succ = 1;
    ans = min(sum, ans);
    return;
  }
  for (int i = 0; i < squ[temp].size(); ++i) {
    int sti = squ[temp][i];
    for (int j = 0; j < cre[sti].size(); ++j) {
      exi[cre[sti][j]]--;
    }
    dfs(sum + 1);
    if (succ) {
      return;
    }
    for (int j = 0; j < cre[sti].size(); ++j) {
      exi[cre[sti][j]]++;
    }
  }
  return;
}
int main()
{
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= 64; ++i) {
      cre[i].clear();
      squ[i].clear();
    }
    cntsqu = 0;
    maxn = 2 * n * (n + 1);
    totstick = maxn;
    build();
    /*for (int i = 1; i <= cntsqu; ++i) {
      for (int j = 0; j < squ[i].size(); ++j) {
        printf("%d ", squ[i][j]);
      }
      putchar('\n');
    }*/
    int t = 0;
    succ = 0;
    scanf("%d", &t);
    for (int i = 1; i <= 64; ++i) {
      exi[i] = 0;
    }
    for (int i = 1; i <= t; ++i) {
      int k;
      scanf("%d", &k);
      for (int j = 0; j < cre[k].size(); ++j) {
        exi[cre[k][j]]--;
      }
      totstick--;
    }
    ans = totstick;
    for (deep = 1; deep; deep++) {
      dfs(0);
      if (succ) {
        printf("%d\n", deep);
        break;
      }
    }
  }
  return 0;
}