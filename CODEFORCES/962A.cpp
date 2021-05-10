#include <map>
#include <set>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

const int N = 200000 + 5;

class Solution {
  int a[N];

 public:
  void solve(std::istream& in, std::ostream& out) {
    int n;
    in >> n;
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
      in >> a[i];
      sum += a[i];
    }
    sum = (sum + 1) / 2;
    for (int i = 1; i <= n; ++i) {
      sum -= a[i];
      if (sum <= 0) {
        out << i << endl;
        return;
      }
    }
  }
};

Solution solution;

void solve(std::istream& in, std::ostream& out) {
  out << std::setprecision(12);
  solution = *(new Solution());
  solution.solve(in, out);
}


#include <fstream>


int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);


  istream& in = cin;


  ostream& out = cout;

  solve(in, out);
  return 0;
}


