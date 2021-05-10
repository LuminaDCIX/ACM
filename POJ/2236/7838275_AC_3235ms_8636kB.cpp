#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
typedef pair<int,int> P;

const int MaxN = 1005, INF = 1<<17;
int N,set[MaxN],D,Re[MaxN];P S[MaxN];
double dist[MaxN][MaxN];

double GetD(int i , int j)
{
	return sqrt(pow(S[i].first - S[j].first,2) + pow(S[i].second - S[j].second,2 ));
}


int find(int  x)
{
	return set[x] == x ? x : set[x] = find(set[x]);
}

int join(int x , int y )
{
	int fx = find(x);
	int fy = find(y);
	if(fx != fy) set[fx] = fy;
}
void solve()
{
	
	for(int i = 1 ; i <= N ; i++){
		for(int j = 1; j <= N ; j++){
			dist[i][j] = INF;
		}
	}
	for(int i = 1 ; i <= N ; i++){
		for(int j = 1; j <= N ; j++){
			dist[i][j] = GetD(i,j);
		}
	}
	for(int i = 0; i <= N ; i ++) set[i] = i;
	memset(Re,0,sizeof(Re));
	
	char c ; c= getchar();
	while(scanf("%c",&c) == 1 && c != EOF)
	{
	
	
		if(c == 'O'){
			int k; scanf("%d",&k);
			Re[k] = 1;
			for(int i = 1; i <= N ; i++){
				if(Re[i] && dist[k][i] <=  D) join (i , k);
			}
		}
		
		if(c == 'S'){
			int a , b ; scanf("%d%d",&a,&b);
			int fx = find(a); int fy = find(b);
			if(fx == fy) printf("SUCCESS\n");else printf("FAIL\n");
		}
		
		c= getchar();
	
	}
	
}
int main()
{
	//freopen("TEXT.txt","r",stdin);
	cin >> N >> D;
	for(int i = 1; i <= N; i ++)
	{
		cin >> S[i].first >> S[i].second;
	}
	solve();
	return 0;
} 