#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstdio> 
using namespace std;
struct Edge{int to,next;};
Edge E[100005];
int cnt,N,M,color[10005],First[10005],ans,C_a,C_b;
void Ins(int u, int v)
{
	E[++cnt].to = v; E[cnt].next = First[u]; First[u] = cnt;
	E[++cnt].to = u; E[cnt].next = First[v]; First[v] = cnt;
}


bool dfs(int v, int c)
{
	color[v] = c; 
	for(int i = First[v] ; i ; i = E[i].next )
	{
		if(color[E[i].to] == c) return false;
		if(color[E[i].to] == 0 && !dfs(E[i].to, -c)) return false;
	}
	if(c == 1) C_a++; else C_b++;
	return true;
}

void solve()
{
	for(int i = 1; i <= N; i++)
	{
		if(color[i] == 0 && !dfs(i,1))
		{
			printf("Impossible\n");
			ans = 0;
			return ;
		}else ans += min(C_a,C_b);
		C_a = C_b = 0;
	}
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	cin >> N >> M;
	
	memset(First,0,sizeof(0));
	memset(E,0,sizeof(E));
	memset(color,0,sizeof(color));
	for(int i = 1; i <= M ; i++)
	{
		int a, b;
		cin >> a >> b;
		Ins(a,b);
	}


	
	solve();
	
	if(ans != 0) cout << ans;
	
	
	
	return 0;
} 