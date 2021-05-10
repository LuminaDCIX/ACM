#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;
int n, deep;
int num[17];
int now[17];
int old[17];
vector <int> block;
vector <int> all;
bool succ;
bool down[17];
void input()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &now[i]);
  }
  return;
}
int h()
{
  //int up = 1;
  //int ret = 0;
  /*for (int i = 1; i <= n; ++i) {
    down[i] = 0;
  }
  /*for (int i = 1; i <= n; ++i) {
    printf("%d ", now[i]);
  }
  putchar('\n'); */
  /*for (int i = 2; i <= n; ++i) {
    if (now[i] < now[i - 1]) {
      down[i] = 1;
    }
  }*/
  /*
    if (up && now[i] < now[i - 1]) {
      ret++;
      up = 0;
    }
    if (now[i] > now[i - 1]) {
      up = 1;
    }*/
  int ret = 0;
  if (now[1] != 1) {
    ret++;
  }
  for (int i = 1; i < n; ++i) {
    if (now[i + 1] != now[i] + 1) {
      ret++;
    }
  }
  //printf("ret = %d\n", ret);
  return ret;
}
  //printf("ret = %d\n", ret);
 // return ret;
//}
void ins(int begin, int l, int r) 
{

  //block.clear();
  //all.clear();
  //printf("%d %d %d\n", begin, l, r);
  for (int i = 1; i <= n; ++i) {
    old[i] = now[i];
    now[i] = 0;
  }
  /*I
  for (int i = l; i <= r; ++i) {
    block.push_back(old[i]);
    old[i] = 0;
  }
  for (int i = 1; i <= begin; ++i) {
    if (old[i]) {
      all.push_back(old[i]);
      old[i] = 0;
    }
  }
  int len = 0;
  
  for (int i = 0; i < all.size(); ++i) {
    now[++len] = all[i];
  }
  for (int i = 0; i < block.size(); ++i) {
    now[++len] = block[i];
  }
  for (int i = 1; i <= n; ++i) {
    if (old[i]) {
      now[++len] = old[i];
    }
  }*/
  if (begin < l) {
    int k = r - l + 1;
    for (int i = 1; i <= k; ++i) {
      now[begin + i] = old[l + i - 1];
      old[l + i - 1] = 0;   
    }
  } 
  if (begin > r) {
    int k = r - l + 1;
    for (int i = 1; i <= k; ++i) {
      now[begin + i - k] = old[l + i - 1];
      old[l + i - 1] = 0;
    }
  }
  int p = 1, q = 1;
  while (q <= n) {
    if (now[q]) {
      q++;
      continue;
    }
    if (old[p]) {
      now[q++] = old[p++]; 
    }
    else {
      p++;
    }
  }
  /*for (int i = 1; i <= n; ++i) {
    printf("%d ", now[i]);
  }
   putchar('\n');*/ 
  return;
}
void dfs(int x)
{
  if (x == deep) {
    for (int i = 1; i <= n; ++i) {
      if (now[i] != i) {
        return;
      }
    }
    succ = 1;
    return;
  }
  if (3 * x + h() > 3 * deep) {
    return;
  }
  /*for (int i = 1; i <= n; ++i) {
    int l, r;
    if (down[i]) {
      l = i - 1;
      r = i;
      while (down[r] && r < n) {
        r++;
      }*/
      for (int j = 1; j <= n; ++j) { //len r - l + 1
        for (int a = 1; a <= n - j + 1; ++a) {
          for (int k = 0; k <= n; ++k) {
            if (k + 1 >= a && k <= a + j - 1) {
              continue;
            }
            ins(k, a, a + j - 1);
            dfs(x + 1);
            if (succ) {
              return;
            }
            if (k < a) {
              ins(a + j - 1, k + 1, k + j);
            }
            if (k > a + j - 1) {
              ins(a - 1, k - j + 1, k);
            }
          }
        }
      }
      //i = r;
    //}
  //}
}
void solve()
{
  succ = 0;
  for (deep = 0; deep <= 4; ++deep) {
    //printf("deep = %d\n", deep);
    dfs(0);
    if (succ) {
      printf("%d\n", deep);
      return;
    }
  }
  printf("5 or more\n");
  return;
}
int main()
{
  int T;
  scanf("%d\n", &T);
  while (T--) {
    input();
    solve();
  }
  return 0;
}