#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstdio> 
using namespace std;
int box[5][5]; //1up 2 down 3left 4right
int ans = 99999,step,Find=0;
int book[5][5];
void input()
{
	for(int i = 1; i <= 4; i++)
		for(int j = 1; j <= 4; j++){
			char x; scanf("%c",&x);
			if(x!='\n')box[i][j] = (x == 'b' ? 1 : 0); //b 0 w 1
			else j--;
		}
	memset(book,0,sizeof(book));
}

void m(int x, int y , int k ){
	if(x+1<=4)box[x+1][y] =!box[x+1][y];
	if(x-1>=1)box[x-1][y] =!box[x-1][y];
	if(y+1<=4)box[x][y+1] =!box[x][y+1];
	if(y-1>=1)box[x][y-1] =!box[x][y-1];
	box[x][y] =!box[x][y];
}

void dfs(int x, int y,int k){
	if(k==step){
		bool b = 0,w = 0,ok = 1;
		for(int i = 1; i <= 4; i++){
			for(int j = 1; j <= 4; j++){
				if(box[i][j] == 0) b = 1;
				else w = 1;
				if(b&&w){ok = 0; break;}
			}
			if(!ok) break;
		}
		if(ok){
			ans = min(ans , k);
			Find = 1;
		}
		return;
	}
	//cout << k << endl;
	if(Find||x==5) return;

	m(x,y,0);
	if(y<4)dfs(x,y+1,k+1);else dfs(x+1,1,k+1);
	m(x,y,0);
	if(y<4)dfs(x,y+1,k);else dfs(x+1,1,k);
}





int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	input();
	for(step =0; step<=16;step++)
	{	
		Find = 0;
		dfs(1,1,0);
		if(Find) break;
	}
	
	if(Find)cout << ans;
	else cout << "Impossible" ;
	return 0;
} 