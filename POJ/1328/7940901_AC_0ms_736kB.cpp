#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
int n,d,Case,book[1005];
struct dist{double left,right;};
struct P{int x,y;dist s;}p[1005];
bool _cmp (const P a, const P b){return a.s.left < b.s.left;} 
bool check(int i){
	
	int a = d *d, b = p[i].y*p[i].y;
	if(a<b||d<=0)return false;
	p[i].s.left  = p[i].x - (sqrt(a-b));
	p[i].s.right = p[i].x + (sqrt(a-b));
//	cout << p[i].dist;
	return true;
}

void input()
{
	for(int i = 1; i <= n ; i++){
		scanf("%d%d",&p[i].x,&p[i].y);
	}
	
}
void solve(){
	while(scanf("%d%d",&n,&d))
	{
	    if(n==0&&d==0)return;
		input();int Ans = 0;
		for(int i = 1; i <= n; i++){
			if(!check(i)){Ans= -1;}
		}
		sort(p+1,p+n+1,_cmp);
		if(Ans!=-1){
			int tos = 1;double flag = p[tos].s.right;Ans++;
			while(tos<=n&&Ans!=-1)
			{
				if(p[tos].s.left > flag){
					Ans++;
					flag = p[tos].s.right;
				}else{
					if(flag > p[tos].s.right) flag = p[tos].s.right;
				}tos++;
			}
		}
		
		cout <<"Case "<<++Case<<": "<< Ans <<endl;
	}
	//4 5 -5 3 -3 5 2 3 3 3adsfasdfqew
}
int main()
{
	//freopen("TEXT.txt","r",stdin);
	solve();
	

	return 0;
} 