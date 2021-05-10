#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int num[N];
int y[N];


bool cmp(int a, int b) {
  return y[a] < y[b];
}


int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> y[i];
    num[i] = i;
  }
  sort(num + 1, num + 1 + n, cmp);
  for (int i = 1; i <= n; ++i) {
    cout << num[i] << " ";
  }
  cout << endl;

  return 0;
}