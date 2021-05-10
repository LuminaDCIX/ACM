#include<iostream>
#include<cstdio>
using namespace std;

char tree[200][3];
int n,cnt;

void dfs(int j , int k) 
{
	if(tree[j][k]!='*')
	{
		cout << tree[j][k];
		if(k==0)
		{
			int a = k + 1;
			int c = 1;
			if(tree[j][a]!='*')
			{
				while(tree[c][0]!=tree[j][a])c++;
				dfs(c,0);
				k = a;
			}
		}
		if(k == 1)
		{
			int a = k + 1;
			int c = 1;
			if(tree[j][a]!='*')
			{
				while(tree[c][0]!=tree[j][a])c++;
				dfs(c,0);
				k = a;
			}
		}
	}
	return ;
	 //cout << "yes\n";
	
}


int main()
{
	cin >> n ;
	for(int i = 1 ; i <= n ; i++ )
	{
		for(int j = 0 ; j <= 2; j ++)
		cin >> tree[i][j];
	} 

	dfs(1,0);
	return 0;
} 