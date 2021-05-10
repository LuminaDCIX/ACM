#include <algorithm>
#include <iomanip>
#include <istream>
#include <map>
#include <numeric>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;
// Powered by caide (code generator, tester, and library code inliner)

const int N = 10000 + 5;

int s[N];
int p[N];
long long c;
int n;

long long dp[2][N];

class Solution {
 public:
  void solve(std::istream& in, std::ostream& out) {
    in >> n;
    in >> c;
    for (int i = 1; i <= n; ++i) {
      in >> p[i];
    }
    for (int i = 1; i <= n; ++i) {
      in >> s[i];
    }
    int cur = 0;
    int lst = 1;
    memset(dp[cur], 0x3f3f, sizeof(dp[cur]));
    dp[cur][0] = 0;
    for (int i = 1; i <= n; ++i) {
      lst ^= 1;
      cur ^= 1;
      memset(dp[cur], 0x3f3f, sizeof(dp[cur]));
      dp[cur][0] = dp[lst][0] + p[i];
      for (int j = 1; j <= i; ++j) {
        dp[cur][j] = min(dp[lst][j] + p[i] + j * c, dp[lst][j - 1] + s[i]);
      }
    }
    long long ans = 1e18;
    for (int i = 0; i <= n; ++i) {
      ans = min(ans, dp[cur][i]);
    }
    out << ans << endl;
  }
};

void solve(std::istream& in, std::ostream& out) {
  out << std::setprecision(12);
  Solution solution;
  solution.solve(in, out);
}


#include <fstream>
#include <iostream>


int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);


  istream& in = cin;


  ostream& out = cout;

  solve(in, out);
  return 0;
}


