#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdio> 
using namespace std;
typedef pair<int,int> P;
const int MAXN = 200005, INF = 99999999;
int N,n,Q; P dat[2 * MAXN - 1];
void init(int n_)
{
	n = 1 ;
    while(n < n_) n <<= 1 ;

    for(int i = 0; i < 2 * n - 1 ; i++) 
    {
    	dat[i].first = 0;
    	dat[i].second = INF;
	}

}
void update(int k , int a, int f)
{
	if(f == 1) // max
	{
		k += n - 1 ; 
		dat[k].first = a;
		while(k > 0){
			k = (k - 1) / 2;
			dat[k].first = max(dat[k * 2 + 1].first, dat[k * 2 + 2].first);
		}
	}
	
	if(f == 0) // min
	{
		k += n - 1 ; 
		dat[k].second = a;
		while(k > 0){
			k = (k - 1) / 2;
			dat[k].second = min(dat[k * 2 + 1].second, dat[k * 2 + 2].second);
		}
	}
}

int MAXquery(int a ,int b , int k , int l ,int r)
{
	
	if(r <= a || b <= l) return 0;
	if(a <= l && r <= b) return dat[k].first;
	else{
		int v1 = MAXquery(a,b,k*2+1,l,(l+r)/2);
		int v2 = MAXquery(a,b,k*2+2,(l+r)/2,r);
		return max(v1,v2);
	}
}

int MINquery(int a ,int b , int k , int l ,int r)
{			
	
	if(r <= a || b <= l) return INF;
	if(a <= l  && r <= b) return dat[k].second;
	else{
		int v1 = MINquery(a,b,k*2+1,l,(l+r)/2);
		int v2 = MINquery(a,b,k*2+2,(l+r)/2,r);
		return min(v1,v2);
	}
	
}

void solve()
{

	init(N);
	for(int i = 1; i <= N ; i++)
	{
		int x; scanf("%d",&x);
		update(i,x,0); update(i,x,1);
	}
	
	for(int i = N + 2; i <= N + Q + 1; i++)
	{
		int x,y; scanf("%d%d",&x,&y);
		if(x != y){
			int v1 = MINquery(x,y+1,0,0,n+1);
			int v2 = MAXquery(x,y+1,0,0,n+1);
			printf("%d\n",v2 - v1);
		}else puts("0");
		
	}
	 
}

int main()
{
	#ifdef LOCAL
	freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	

	scanf("%d%d",&N,&Q);
	
	solve();

	
	return 0;
} 