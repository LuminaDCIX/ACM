#include <cstdio> 
#include <cstring>

int city,culture,roat,begin,end;
int c[105];
int e[105][105];
int p[105][105];
int l[105];
int ans = 16843009;
int u[10001],v[10001],d[10001];
int i ,j;
void dfs(int step,int position)
{
	if(position == end)
	{
		if(step < ans ) ans = step;
		return ;
	} 
	if(step >= ans ) return ;
	for(i = 1 ;  i <= city ; i++)
	{
		if(l[c[i]]==0&&p[c[i]][c[position]]==0&&e[i][position]>=1)
		{
			bool ok = 1;
			for (j=1; j<= culture ; j++)
              if (l[j] == 1)
                if (p[c[i]][j] == 1) { ok = 0 ; break; }
			if(ok==0) continue;	
			l[c[i]] = 1;
			dfs(step+e[position][i],i);
			l[c[i]] = 0;
				
			
		}
	}
	
}


int main()
{
	memset(e,0,sizeof(e));
    memset(l,0,sizeof(l));

	scanf("%d%d%d%d%d",&city,&culture,&roat,&begin,&end);
	for(i = 1 ; i <= city ; i++)
	{
		scanf("%d",&c[i]);
	}
	 
	for(i = 1 ; i <= culture ; i++)
	{
		for(int j = 1; j <= culture ; j++)
			scanf("%d",&p[i][j]);
	}
	
	for(i = 1 ; i <= roat ; i++)
	{
		scanf("%d%d%d",&u[i],&v[i],&d[i]);
		if (e[u[i]][v[i]]>0 && e[u[i]][v[i]]>d[i] || e[u[i]][v[i]]==0)
      {
        e[u[i]][v[i]]=d[i]; //是否有路径 
        e[v[i]][u[i]]=d[i];
      }
	}
	l[c[begin]] = 1;
	dfs(0,begin);
	if(ans == 16843009) printf("-1") ;
	else printf("%d",ans); 	
	return 0;
} 