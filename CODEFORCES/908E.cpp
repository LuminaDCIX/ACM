#include <bits/stdc++.h>

using namespace std;

const int K=1000+5;
const int N=50+5;
const int p=1e9+7;

int k;
int n;

char s[N][K];
int C[K][K];
int B[K];

void init() {
  C[0][0]=1;
  for (int i=1;i<=k;++i) {
    C[i][0]=1;
    for (int j=1;j<=i;++j) {
      C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
    }
  }
  B[1]=1;
  B[0]=1;
  for (int i=2;i<=k;++i) {
    for (int j=0;j<i;++j) {
      B[i]=(B[i]+(long long)C[i-1][j]*B[i-j-1]%p)%p;
    }
  }
}

int main() {
  scanf("%d %d",&k,&n);
  for (int i=0;i<n;++i) {
    scanf("%s",s[i]);
  }
  vector <string> v;
  for (int i=0;i<k;++i) {
    string m;
    m.clear();
    for (int j=0;j<n;++j) {
      m=m+s[j][i];
    }
    v.push_back(m);
  }
  sort(v.begin(),v.end());
  init();
  int ans=1;
  for (int i=0;i<k;++i) {
    int ptr=i;
    while (ptr<k-1&&v[ptr]==v[ptr+1]) {
      ++ptr;
    }
    ans=(long long)ans*B[ptr-i+1]%p;
    i=ptr;
  }
  printf("%d\n",ans);
  return 0;
}
