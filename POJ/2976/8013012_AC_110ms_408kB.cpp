#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, k;
double a[1005],b[1005];
double s1[1005];
double ans = -1.0;
//Product by MiracleEEEE 
inline int read_num(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();}
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
//100 * sigxi/sigyi = x -> 100 * sigxi = maxX * sigyi ( x -> max)
bool input(){ 
	for(int i = 1; i <= n ; i ++) scanf("%lf",&a[i]),a[i]*=100;
	for(int j = 1; j <= n ; j ++) scanf("%lf",&b[j]);
	return true;
}
bool solve(){	
	while(scanf("%d%d",&n,&k)&&!(n==0&&k==0)) {
		input();
		double l = 0.0, r = 100.0 ;double mid;
		while(r - l > 1e-7) {
			mid = (l + r) / 2.0;
			for(int i = 1;i <= n ; i ++)  s1[i] = 1.0 * a[i] - mid * b[i];
			sort(s1+1,s1+n+1);
			double sum1 = 0.0;
			for(int i = k + 1;i <= n ; i ++)sum1 += s1[i] ;
			//printf("sum = %d mid = %d\n",sum,mid);
			if(sum1 > 0) l = ans = mid;
			else r = mid;
		}
		printf("%.0f\n",l);
	}
	return true;
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	solve();
	return 0;
} //hehe