#include <bits/stdc++.h>

using namespace std;    

int main() {
  long long a = 0;
  long long b = 0;
  long long c = 0;
  int A;
  int B;
  int C;
  int nowa;
  int nowb;
  scanf("%d%d", &nowa, &nowb);
  scanf("%d %d %d", &A, &B, &C);
  a += 2 * A;
  b += B;
  a += B;
  b += (long long) 3 * C;
  a = max(a - nowa, 0ll);
  b = max(b - nowb, 0ll);
  printf("%lld\n", a + b);
  
  return 0;
}