#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define rep(i,a,n) for (register int i=(a);i<(n);++i)

const int MAX_CARD=17;
int mx=14;

int n;

int cnt[MAX_CARD];

int ans=0;

int v[17];
int tot;

bool cur=0;

int f[6][16][16][16];

int c[5];

int fc() {
  memset(c,0,sizeof(c));
  rep (i,0,mx+1) c[cnt[i]%4]++,c[cnt[i]/4*4]++;
  return f[c[4]][c[3]][c[2]][c[1]];
}


void dfs(int now,int lft) {
  int k=fc();
  if (now>=ans) { return; }
  ans=min(ans,now+k);
  bool fix=0;
  if (cnt[13]>0&&cnt[14]>0) cnt[13]--, cnt[14]--, dfs(now+1,lft-2), cnt[13]++, cnt[14]++,fix=1;
  //danshunzi
  if (lft>=5) rep (i,0,12) if (cnt[i]&&cnt[i+1]&&cnt[i+2]&&cnt[i+3]) rep (j,i+4,12) {
        if (!cnt[j]) break;
        rep (k,i,j+1) --cnt[k];
        dfs(now+1,lft-j+i-1);
        rep (k,i,j+1) ++cnt[k];
        fix=1;
      }
  //shuangshunzi
  if (lft>=6) rep (i,0,12) if (cnt[i]>=2&&cnt[i+1]>=2) rep (j,i+2,12) {
        if (cnt[j]<2) break;
        rep (k,i,j+1) cnt[k]-=2;
        dfs(now+1,lft-(j-i+1)*2);
        rep (k,i,j+1) cnt[k]+=2;
        fix=1;
      }
  //sanshunzi
  if (lft>=6) rep (i,0,12) if (cnt[i]>=3) rep (j,i+1,12) {
        if (cnt[j]<3) break;
        rep (k,i,j+1) cnt[k]-=3;
        dfs(now+1,lft-(j-i+1)*3);
        rep (k,i,j+1) cnt[k]+=3;
        fix=1;
      }
 
}


void calc(int n4,int n3,int n2,int n1,int now,int lft) {
  if (lft>23) return;
  if (now>=ans) return;
  if (lft==0) {
    ans=min(ans,now);
    return;
  }
  if (n4&&n2>=2) n4-=1,n2-=2,calc(n4,n3,n2,n1,now+1,lft-8),n4+=1,n2+=2;
  if (n4&&n1>=2) n4-=1,n1-=2,calc(n4,n3,n2,n1,now+1,lft-6),n4+=1,n1+=2;
  if (n3&&n2) n3-=1,n2-=1,calc(n4,n3,n2,n1,now+1,lft-5),n3+=1,n2+=1;
  if (n3&&n1) n3-=1,n1-=1,calc(n4,n3,n2,n1,now+1,lft-4),n3+=1,n1+=1;
  if (n4) n4-=1,calc(n4,n3,n2,n1,now+1,lft-4),n4+=1;
  if (n3) n3-=1,calc(n4,n3,n2,n1,now+1,lft-3),n3+=1;
  if (n2) n2-=1,calc(n4,n3,n2,n1,now+1,lft-2),n2+=1;
  if (n1) n1-=1,calc(n4,n3,n2,n1,now+1,lft-1),n1+=1;
}

int main() {
  int a, b, T;
  scanf("%d%d", &T,&n);

  rep (n4,0,6) rep (n3,0,16) rep (n2,0,16) rep (n1,0,16) ans=1e9,calc(n4,n3,n2,n1,0,n4*4+n3*3+n2*2+n1*1),f[n4][n3][n2][n1]=ans;

  while (T--) {
    ++cur;
    memset(cnt,0,sizeof(cnt));
    rep (i,0,n) {
      scanf("%d%d",&b,&a);

      if (b==1) b=11;
      else if (b==2) b=12;
      else if (b==0&&a==1) b=13;
      else if (b==0&&a==2) b=14;
      else b-=3;
      cnt[b]++;
    }



    ans=2e9;
    dfs(0,n);
    printf("%d\n",ans);
  }
  fclose(stdin);
  fclose(stdout);
  return 0;
}
