#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
typedef pair <int, int> p;

struct card
{
  int col, val;
} cards[21];
vector <p> lines[21];
int T, n;
int ans = 0;
int exi[17];
const int maxcol = 15;
bool cmp(card a, card b) 
{
  if (a.val == b.val) {
    return a.col < b.col;
  }
  return a.val < b.val;
}

void init()
{
  for (int i = 1; i <= maxcol; ++i) {
    exi[i] = 0;
  }
  for (int i = 1; i <= n; ++i) {
    if (cards[i].val == 0 && cards[i].col == 1) {
      exi[14]++;
      continue;
    }
    if (cards[i].val == 0 && cards[i].col == 2) {
      exi[15]++;
      continue;
    }
    if (cards[i].val == 2) {
      exi[13]++;
      continue;
    }
    if (cards[i].val == 1) {
      exi[12]++;
      continue;
    }
    exi[cards[i].val - 2]++;
  }
  for (int i = 0; i < 20; ++i) {
    lines[i].clear();
  }
  for (int len = 1; len <= 12; ++len) {
    for (int l = 1; l <= 12 - len + 1; ++l) {
      int r = l + len - 1;
      bool ok = 1;
      int minn = 16;
      for (int i = l; i <= r; ++i) {
        if (!exi[i]) {
          ok = 0;
          break;
        }
        minn = min(minn, exi[i]);
      }
      if (ok) {
        lines[len].push_back(make_pair(l, minn));
      }
    }
  }
  return;
}

void input()
{
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &cards[i].val, &cards[i].col);
  } 
  init();
  return;
}

void print()
{
  for (int i = 1; i <= maxcol; ++i) {
    printf("%d = %d\n", i, exi[i]);
  }
  putchar('\n');
  return;
}
void calc(int now, int left)
{
  if (left == 0) {
    ans = min(ans, now);
    return;
  }
  for (int i = 1; i <= maxcol && left >= 6; ++i) if (exi[i] >= 4) {
    for (int j = 1; j <= maxcol; ++j) if (exi[j] == 2) {
      for (int k = 1; k <= maxcol; ++k) if (exi[k] == 2) {
        if (k == j || k == i || i == j) {
          continue;
        }
        exi[k] -= 2;
        exi[j] -= 2;
        exi[i] -= 4;
        calc(now + 1, left - 8);
      }
    }
    for (int j = 1; j <= maxcol; ++j) if (exi[j] == 1) {
      for (int k = 1; k <= maxcol; ++k) if (exi[k] == 1) {
        if (k == j || k == i || i == j) {
          continue;
        }
        exi[k]--;
        exi[j]--;
        exi[i] -= 4;
        calc(now + 1, left - 6);
      }
    }
  }
  //boom
  for (int i = 1; i <= maxcol && left >= 4; ++i) if (exi[i] == 4) {
    exi[i] -= 4;
    calc(now + 1, left - 4);
  }
      //tri + 2
  for (int i = 1; i <= maxcol && left >= 5; ++i) if (exi[i] == 3) {
    for (int j = 1; j <= maxcol; ++j) if (exi[j] == 2) {
      if (i == j) {
        continue;
      }
      exi[j] -= 2;
      exi[i] -= 3;
      calc(now + 1, left - 5);
    }
  }
    //tri + 1
  for (int i = 1; i <= maxcol && left >= 4; ++i) if (exi[i] == 3) {
    for (int j = 1; j <= maxcol; ++j) if (exi[j] == 1) {
      if (i == j) {
        continue;
      }
      exi[j]--;
      exi[i] -= 3;
      calc(now + 1, left - 4);
    }
  } 
  //rick
  if (exi[14] && exi[15]) {
    exi[14]--;
    exi[15]--;
    calc(now + 1, left - 2);
  }
    //tri
  for (int i = 1; i <= maxcol && left > 2; ++i) if (exi[i] == 3) {
    exi[i] -= 3;
    calc(now + 1, left - 3);
}
    //double
  for (int i = 1; i <= maxcol && left > 1; ++i) if (exi[i] == 2) {
    exi[i] -= 2;
    calc(now + 1, left - 2);
  }
  //single
  //cnt = 0;
  for (int i = 1; i <= maxcol && left; ++i) if (exi[i] == 1) {
    //printf("single %d %d\n", i, exi[i]);
    exi[i]--;
    //printf("single %d %d\n", i, exi[i]);
    calc(now + 1, left - 1);
    //exi[i]++;
  }
  return;
}
int tmp[21];

void dfs(int now, int left) 
{
  if (now >= ans) {
    return;
  }
  for (int i = 1; i <= maxcol; ++i) {
    tmp[i] = exi[i];
  }
  calc(now, left);
  for (int i = 1; i <= maxcol; ++i) {
    exi[i] = tmp[i];
  }
 // print();
  if (!left) {
    ans = min(ans, now);
    return;
  }
    //line single
  for (int len = 12; len >= 5; --len) {
        if (len > left) {
      continue;
    }
    for (int i = 0; i < lines[len].size(); ++i) {
      int l = lines[len][i].first;
      int r = l + len - 1;
      bool exist = 1;
      for (int j = l; j <= r; ++j) {
        if (!exi[j]) {
          exist = 0;
          break;
        }
      }
      if (exist) {
        for (int j = l; j <= r; ++j) {
          exi[j]--;
        }
        dfs(now + 1, left - len);
        for (int j = l; j <= r; ++j) {
          exi[j]++;
        }
      }
    }
  }
    //double line
  for (int len = 12; len>= 3; --len) {
    if (len * 2 > left) {
      continue;
    }
    for (int i = 0; i < lines[len].size(); ++i) {
      int l = lines[len][i].first;
      if (lines[len][i].second < 2) {
        continue;
      }
      int r = l + len - 1;
      bool exist = 1;
      for (int j = l; j <= r; ++j) {
        if (exi[j] < 2) {
          exist = 0;
          break;
        }
      }
      if (exist) {
        for (int j = l; j <= r; ++j) {
          exi[j] -= 2;
        }
        dfs(now + 1, left - 2 * len);
        for (int j = l; j <= r; ++j) {
          exi[j] += 2;
        }
      }
    }
  }
        //3 line
  for (int len = 12; len >= 2; --len) {
    if (len * 3> left) {
      continue;
    }
    for (int i = 0; i < lines[len].size(); ++i) {
      int l = lines[len][i].first;
      if (lines[len][i].second < 3) {
        continue;
      }
      int r = l + len - 1;
      bool exist = 1;
      for (int j = l; j <= r; ++j) {
        if (exi[j] < 3) {
          exist = 0;
          break;
        }
      }
      if (exist) {
        for (int j = l; j <= r; ++j) {
          exi[j] -= 3;
        }
        dfs(now + 1, left - 3 * len);
        for (int j = l; j <= r; ++j) {
          exi[j] += 3;
        }
      }
    }
  }
  /*  int cnt = 0;
  for (int i = 1; i <= maxcol; ++i) if (exi[i] == 1) {
      cnt++;
    }
  if (now + cnt > ans) {
    return;
  }*/
  for (int i = 1; i <= maxcol; ++i) {
    tmp[i] = exi[i];
  }
  calc(now, left);
  for (int i = 1; i <= maxcol; ++i) {
    exi[i] = tmp[i];
  }
    //4 + 2
}
void solve()
{ 
  ans = n;
  dfs(0, n);
  printf("%d\n", ans);
  return;
}
int main()
{
  int kase = 0;
  scanf("%d%d", &T, &n);
  while (T--) {
    ++kase;
    input();
    for (int i = 1; i <= maxcol; ++i) {
      tmp[i] = exi[i];
    }
    calc(0, n);
    for (int i = 1; i <= maxcol; ++i) {
      exi[i] = tmp[i];
    }
    solve();
  }
  return 0;
}