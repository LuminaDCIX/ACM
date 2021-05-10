#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;
int num[29];
int start[29];
int inv[11];
stack <int> ans;
string output;
string t;
bool succc;
int maxdeep;
int deep, sign;
void init()
{
  inv[1] = 6;
  inv[6] = 1;
  inv[2] = 5;
  inv[5] = 2;
  inv[3] = 8;
  inv[8] = 3;
  inv[4] = 7;
  inv[7] = 4;
  return;
}
void move(int x) {
  int temp = 0;
  switch(x) {
    case 1:
      temp = num[1];
      num[1] = num[3];
      num[3] = num[7];
      num[7] = num[12];
      num[12] = num[16];
      num[16] = num[21];
      num[21] = num[23];
      num[23] = temp;
      break;
    case 2:
      temp = num[2];
      num[2] = num[4];
      num[4] = num[9];
      num[9] = num[13];
      num[13] = num[18];
      num[18] = num[22];
      num[22] = num[24];
      num[24] = temp;
      break;
    case 3:
      temp = num[11];
      for (int i = 11; i > 5; --i) {
        num[i] = num[i - 1];
      } 
      num[5] = temp;
      break;
    case 4:
      temp = num[20];
      for (int i = 20; i > 14; --i) {
        num[i] = num[i - 1];
      }
      num[14] = temp;
      break;
    case 5:
      temp = num[24];
      num[24] = num[22];
      num[22] = num[18];
      num[18] = num[13];
      num[13] = num[9];
      num[9] = num[4];
      num[4] = num[2];
      num[2] = temp;
      break;
    case 6:
      temp = num[23];
      num[23] = num[21];
      num[21] = num[16];
      num[16] = num[12];
      num[12] = num[7];
      num[7] = num[3];
      num[3] = num[1];
      num[1] = temp;
      break;
    case 7:
      temp = num[14];
      for (int i = 14; i < 20; ++i) {
        num[i] = num[i + 1];
      }
      num[20] = temp;
      break;
    case 8:
      temp = num[5];
      for (int i = 5; i < 11; ++i) {
        num[i] = num[i + 1];
      }
      num[11] = temp;
      break;
  }
}
int succ = 0;
int a = 'A';
void print()
{
  printf("    %d   %d\n", num[1], num[2]);
  printf("    %d   %d\n", num[3], num[4]);
  printf("%d %d %d %d %d %d %d\n", num[5], num[6], num[7], num[8], num[9], num[10], num[11]);
  printf("    %d   %d\n", num[12], num[13]);
  printf("%d %d %d %d %d %d %d\n", num[14], num[15], num[16], num[17], num[18], num[19], num[20]);
  printf("    %d   %d\n", num[21], num[22]);
  printf("    %d   %d\n", num[23], num[24]);
  putchar('\n');
}
int h()
{
  int ret = 0;
  for (int i = 7; i <= 9; ++i) {
      ret += num[i];
  }
  for (int i = 16; i <= 18; ++i) {
      ret += num[i];
  }
  return 8 - ret - num[12] - num[13];
}
void dfs(int x) 
{
  //print();
  int H = h();
  if (H == 0) {
    succ = 1;
    return;
  }
  if (x + H > deep) {
    return;
  }

  move(1); dfs(x + 1);
  if (succ) {
    ans.push(1);
    return;
  }
  move(inv[1]);

  move(2); dfs(x + 1);
  if (succ) {
    ans.push(2);
    return;
  }
  move(inv[2]);

  move(3); dfs(x + 1);
  if (succ) {
    ans.push(3);
    return;
  }
  move(inv[3]);

  move(4); dfs(x + 1);
  if (succ) {
    ans.push(4);
    return;
  }
  move(inv[4]);

  move(5); dfs(x + 1);
  if (succ) {
    ans.push(5);
    return;
  }
  move(inv[5]);

  move(6); dfs(x + 1);
  if (succ) {
    ans.push(6);
    return;
  }
  move(inv[6]);

  move(7); dfs(x + 1);
  if (succ) {
    ans.push(7);
    return;
  }
  move(inv[7]);

  move(8); dfs(x + 1);
  if (succ) {
    ans.push(8);
    return;
  }
  move(inv[8]);

  return;
}
void solve()
{
  succ = 0;
  succc = 0;
  t = "";
  output = "";
  for (sign = 1; sign <= 3; ++sign) {
    bool ok = true;
    for (int i = 7; i <= 9; ++i) {
      if (start[i] != sign) {
        ok = false;
        break;
      }
    }
    for (int i = 16; i <= 18; ++i) {
      if (start[i] != sign) {
        ok = false;
        break;
      }
    }
    if (start[12] != sign || start[13] != sign) {
      ok = false;
    }
    if (ok) {
      printf("No moves needed\n%d\n", sign);
      return;
    }
  }
  for (deep = 1; deep; ++deep) {
    //printf("deep = %d         ===========================\n", deep);
    for (sign = 1; sign <= 3; ++sign) {
      int sum = 0;
      for (int i = 1; i <= 24; ++i) {
        num[i] = (start[i] == sign);
        if (num[i]) {
          sum++;
        }
      }
      while (!ans.empty()) {
        ans.pop();
      }
      if (sum < 8) {
        continue;
      }
      dfs(0);
      if (succ) {
        t = "";
        while (!ans.empty()) {
          t = t + char(ans.top() + a - 1);
          ans.pop();
        }
        if (output == "" || t < output) {
          output = t;
          maxdeep = sign;
        }
        succ = 0;
        succc = 1;
      }
    }
    if (succc) {
      cout << output << endl;
      printf("%d\n", maxdeep);
      return;
    }
  }
}
bool finish = 0;
void input()
{
  scanf("%d", &start[1]);
  if (!start[1]) {
    finish = 1;
    return;
  }
  for (int i = 2; i <= 24; ++i) {
    scanf("%d", &start[i]);
  }
  return;
}
int main()
{
  init();
  while (1) {
    input();
    if (finish) {
      return 0;
    }
    solve();
  }
  return 0;
}