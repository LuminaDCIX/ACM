#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int dir[N];
int x[N];
map<int, int> id;
int ans[N];

void solve(int n, int m, vector<int> t) {

  vector<int> in(n);
  n = t.size();
  if (n == 1) {
    return;
  }
  set<int> L;
  set<int> R;
  for (int i = 0; i < n; ++i) {
    if (dir[id[t[i]]] == 0) {
      L.insert(t[i]);
      R.insert(-t[i]);
    } else {
      R.insert(t[i]);
      L.insert(2 * m - t[i]);
    }
  }
  priority_queue<array<int, 3>> heap;
  for (auto pos : R) {
    auto itr = L.lower_bound(pos);
    if (id[*itr] == id[pos]) {
      ++itr;
    }
    if (itr != L.end()) {
      in[id[pos]]++;
      heap.push({-(*itr - pos), pos, *itr});
    }
  }
  while (!heap.empty()) {
    auto h = heap.top();
    heap.pop();
    int idl = id[h[1]];
    int idr = id[h[2]];

    // cerr << -h[0] << " " << h[1] << " " << h[2] << endl;
    if (ans[idl] != -1 || ans[idr] != -1) {
      if (ans[idl] == -1) {
        int pos = h[1];
        auto itr = L.lower_bound(pos);
        if (itr != L.end()) {
          if (id[*itr] == id[pos]) {
            ++itr;
          }
          if (itr != L.end()) {
            in[id[pos]]++;
            heap.push({-(*itr - pos), pos, *itr});
          }
        }
      }
      continue;
    }
    ans[idl] = -h[0] / 2;
    ans[idr] = -h[0] / 2;
    if (h[1] > 0) {
      L.erase(L.find(2 * m - h[1]));
    } else {
      L.erase(L.find(-h[1]));
    }

    L.erase(L.find(h[2]));

    // cerr << "hello" << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    int m;
    cin >> n >> m;
    id.clear();
    for (int i = 0; i < n; ++i) {
      cin >> x[i];
      id[x[i]] = i;
      ans[i] = -1;
    }
    string s;
    for (int i = 0; i < n; ++i) {
      cin >> s;
      if (s[0] == 'R') {
        dir[i] = 1;
        id[2 * m - x[i]] = i;
      } else {
        dir[i] = 0;
        id[-x[i]] = i;
      }
    }

    vector<int> t;
    for (int i = 0; i < n; ++i) {
      if (x[i] & 1) {
        t.push_back(x[i]);
      }
    }
    solve(n, m, t);
    t.clear();
    for (int i = 0; i < n; ++i) {
      if (!(x[i] & 1)) {
        t.push_back(x[i]);
      }
    }
    solve(n, m, t);
    for (int i = 0; i < n; ++i) {
      cout << ans[i] << " ";
    }
    cout << endl;
  }

  return 0;
}
