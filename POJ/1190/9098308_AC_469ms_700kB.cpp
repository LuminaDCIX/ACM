#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int N, M;
int ans;
int min_S[23];
int min_V[23];
vector <int> is_fac;
vector <int> num;

void pre()
{
  for (int m = 1; m <= M; ++m) {
    min_S[m] = min_S[m - 1] + 2 * m * m;
    min_V[m] = min_V[m - 1] + m * m * m;
  }
  for (int i = 1; i * i <= N; ++i) {
    is_fac.push_back(i * i);
    num.push_back(i);
  }
  //for (int i = 0; i < is_fac.size(); ++i) {
  //  printf("%d\n", is_fac[i]);
 // }
  return;
}

int bottom_R;

int dfs(int now, int last_R, int last_H, int sum_V, int sum_S)
{
  //printf("now = %d R = %d H = %d S = %d V = %d\n", now, last_R, last_H, sum_S, sum_V);
  if (now == 1) {
    //printf("now = %d R = %d H = %d S = %d V = %d\n", now, last_R, last_H, sum_S, sum_V);
    int more = N - sum_V;
    if (more <= 0) {
      return -1;
    }
    int maxs = 1000000000;
    /*for (int R = 1; R < last_R; ++R) {
      for (int H = 1; H < last_H; ++H) {
        if (V(R, H) == more) {
          maxs = min(maxs, size_side(R, H));
        } 
      }
    }*/
    for (int i = 0; i < is_fac.size(); ++i) {
      if (is_fac[i] > more) {
        break;
      }
      if (!(more % is_fac[i])) {
        int H = more / is_fac[i];
        if (H >= last_H) {
          continue;
        }
        int R = num[i];
        if (R >= last_R) {
          continue;
        }
        //printf("%d %d %d\n",more, R, H);
        maxs = min(maxs, 2 * R * H);
      }
    }
    if (!maxs) {
      return 0;
    }
    ans = min(ans, sum_S + maxs + bottom_R * bottom_R);
    return 1;
  }
  int more = N - sum_V;
  if (more <= 0) {
    return -1;
  }
  if (2 * more / last_R + bottom_R * bottom_R  + sum_S >= ans) {
    return -1;
  }
  if (sum_V + min_V[now] > N) {
    return -1;
  }
  if (sum_S + min_S[now] + bottom_R * bottom_R >= ans) {
    return -1;
  }
  int bar = 0;
  int max_R = last_R - 1;
  int max_H = last_H - 1;
  for (int i = now; i >= 1; --i) {
    bar += max_R * max_R * max_H;
    max_R--;
    max_H--;
  }
  if (bar + sum_V < N) {
    return 0;
  }
  /*if (sum_V + last_H * last_R * last_R * (M - now) < N) {
    return 0;
  }*/
  for (int R = now - 1; R < last_R; ++R) {
    for (int H = now - 1; H < last_H; ++H) {
      if (dfs(now - 1, R, H, sum_V + R * R * H, sum_S + 2 * R * H) == -1) {
        break;
      }
    }
  }
  return 0;
}

void input()
{
  scanf("%d%d", &N, &M);
  pre();
  return;
}

void solve()
{
  ans = 1000000000;
  if (M == 1) {
    for (int R = 1; R <= N; ++R) {
      if (R * R > N) { 
        break;
      }
      for (int H = 1; H <= N; ++H) {
        int k = R * R * H;
        if (k > N) { 
          break;
        }
        if (k == N) {
          ans = min(ans, R * R + 2 * R * H);
        }
      }
    }
    if (ans == 1000000000) {
      printf("0\n");
      return;
    }
    printf("%d\n", ans);
    return;
  }
  for (bottom_R = M; bottom_R; ++bottom_R) {
    if (min_V[M - 1] + bottom_R * bottom_R * M > N) {
      break;
    }
    for (int H = M; H; ++H) {
      if (min_V[M - 1] + bottom_R * bottom_R * H > N) {
        break;
      }
      dfs(M - 1, bottom_R, H, bottom_R * bottom_R * H, 2 * bottom_R * H);
    }
  }  
  if (ans == 1000000000) {
    printf("0\n");
    return;
  }
  printf("%d\n", (int) ans);
  return;
}

int main()
{
  input();
  solve();
  return 0;
}