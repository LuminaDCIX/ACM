 #include <cstdio>
#include <iostream>
using namespace std;
long long r ,l ;
//Product by MiracleEEEE
int N,M,s[100005],Mx; 
inline int read_num(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();}
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
//100 400 300 100 500 101 400
//二分最大长度 NO
//二分最大值 s[i]+s[i+1]+....+s[i+k]
//妈祖单调性 分成M份 单调性可行转化为可行性问题可行 怎么转化 w 
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool solve(){
	while(scanf("%d%d",&N,&M) == 2) {
		for(int i = 1;i <= N ; i ++) 
			scanf("%d",&s[i]),r+=s[i]; 
		int ans = 999999999; 
		while(l < r) {
			
   			long long mid = (l + r) / 2;
			int i = 1,m = 0;
			Mx = 0;
			while(i <= N) {
				int sum = s[i]; 
				while(i <= N &&s[++i] + sum <= mid) {
					sum += s[i];
				}
				//printf("l = %lld r = %lld sum = %d mid = %d\n",l,r,sum,mid);
				Mx = max (Mx, sum);	
				m ++;
			}//printf("m = %lld\n",);
			if(m <= M) {r = mid; ans = min (ans,Mx); } 
			else  if(m > M) l = mid + 1;
		
		}
		printf("%d\n",ans);
	}

}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	solve();
	return 0;
}  