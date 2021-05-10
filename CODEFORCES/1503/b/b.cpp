#include <bits/stdc++.h>

using namespace std;

#define y1 _y1
#define all(x) x.begin(), x.end()
#define gid(x, y) get<y>(x)


queue<pair<int, int> > even;
queue<pair<int, int> > odd;

int nxt[3];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if ((i + j) & 1) {
        odd.push(make_pair(i, j));
      } else {
        even.push(make_pair(i, j));
      }
    }
  }
  int op;
  cin >> op;
  --op;
  int fop = op;
  int nop = (op + 1) % 3;
  nxt[fop] = nop;
  nxt[nop] = 3 - fop - nop;
  nxt[3 - fop - nop] = nop;
  

  int cnt[3] = {0, 0, 0};
  bool full = false;
  queue<pair<int, int> > que;
  cout << nop + 1 << " " << 1 << " " << 1 << endl;
  even.pop();
  ++cnt[nop];
  
  for (int i = 1; i < n * n; ++i) {
    cin >> op;
    --op;
    if (!full) {
      if (op == nop) {
        ++cnt[nxt[op]];
        cout << nxt[op] + 1 << " " << gid(odd.front(), 0) + 1 << " " << gid(odd.front(), 1) + 1 << endl;
        odd.pop();
      } else {
        ++cnt[nxt[op]];
        cout << nxt[op] + 1 << " " << gid(even.front(), 0) + 1 << " " << gid(even.front(), 1) + 1 << endl;
        even.pop();
      }
      if (cnt[nop] == (n * n + 1) / 2) {
        nxt[fop] = 3 - fop - nop;
        nxt[nop] = fop;
        nxt[3 - fop - nop] = fop;
        full = true;
        que = odd;
      }
      if (cnt[3 - fop - nop] == n * n / 2) {
        nxt[3 - fop - nop] = nop;
        nxt[nop] = fop;
        nxt[fop] = nop;
        full = true;
        que = even;
      }
    } else {
      cout << nxt[op] + 1 << " " << gid(que.front(), 0) + 1 << " " << gid(que.front(), 1) + 1 << endl;
      que.pop();
    }
    cout.flush();
  }
  return 0;
}

