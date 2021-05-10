#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdio> 
#include <cstring>
using namespace std;
int e[205][205];

int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	int n;
	cin >> n;
	int i , j;
	for(i = 1 ; i <= n ; i ++)
	{
		for(j = 1 ; j <= n ; j ++) e[i][j]=999999;
	}
	
	for(i = 1 ; i <= n ; i++)
	  for( j = i + 1; j <= n ; j++) scanf("%d",&e[i][j]);
	
	int k;
	for( k = 1; k <= n ; k++)
	  for(i = 1; i <= n ; i++)
	    for(j = 1 ; j <= n ; j++) 
		if(e[i][j]>e[i][k]+e[k][j])e[i][j]=e[i][k]+e[k][j];
	    
	printf("%d",e[1][n]);
	
	 
	
	
	
	
	return 0;
} 