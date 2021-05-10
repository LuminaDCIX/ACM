#include <map>
#include <cstdio>

using namespace std;

int n;

inline void calc(int &plt, int p, int x) {
  if (x % 4 == 1) {
    plt *= (p + 1);
  }
  if (x % 4 == 3) {
    plt *= (p + 1) % 2;
  }
}

int main() {
  scanf("%d", &n);
  int plt = 4;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      int p = 0;
      while (n % i == 0) {
        n /= i;
        ++p;
      }
      calc(plt, p << 1, i);
    }                                                                                                                              
  }  
  if (n > 1) {
    calc(plt, 2, n);
  }
  printf("%d\n", plt);
  return 0;
}
