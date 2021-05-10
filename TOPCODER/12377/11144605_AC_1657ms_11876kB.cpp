#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class TheSquareRootDilemma {
public:
  int countPairs(int, int);
};


int TheSquareRootDilemma::countPairs(int n, int m) {
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int s = 1;
    for (int j = 1; j * j <= i; ++j) {
      if (i % (j * j) == 0) {
        s = j * j;
      }
    }
    int r = i / s;
    // for (int j = 1; j * j * r <= m; ++j) {
    //   ++ans;
    // }
    ans += sqrt((double) m / r);
  }
  return ans;
}



