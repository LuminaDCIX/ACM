#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n;
int k;
int a[N];

int cnt[N];

int main() {
  cin >> n >> k;
  vector<int> v;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    v.push_back(a[i]);
    cnt[a[i]]++;
  }
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  for (int i = 0; i < (int) v.size(); ++i) {
    if (i != (int) v.size() - 1 && v[i + 1] <= v[i] + k) {
      n -= cnt[v[i]];
    }
  }
  cout << n << endl;
  
  
  return 0;
}
