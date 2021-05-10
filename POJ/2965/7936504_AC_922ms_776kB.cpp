#include <cstdio> 
#include <iostream>
using namespace std; // Product by MiracleEEEE
struct P{int x, y; P():x(0),y(0){} P(int x,int y):x(x),y(y){}};
int box[5][5],step,Find,ans = 20;
struct Stack{
	int front,back;
	P e[6000];
}s;
void input(){
	for(int i = 1; i <= 4; i++)
		for(int j = 1; j <= 4; j++){
			char x; scanf("%c",&x);
			if(x!='\n') box[i][j] = x == '-' ? 1 : 0 ;
			else j--;
		}
	s.back = s.front = 0;
}

void c(int x, int y ){
	for(int i = 1; i <= 4; i++){
		box[x][i] = !box[x][i];
		box[i][y] = !box[i][y];
	}
	box[x][y] = !box[x][y];
	
	
	
}

int judge(){
	/*if(step==6)
	{

		for(int i = 1; i <= 4; i++){
			
			for(int j = 1; j <= 4; j++) cout <<  box[i][j];
			cout << endl;
		}
		cout << endl;
	}*/
	for(int i = 1; i <= 4; i++)
		for(int j = 1; j <= 4; j++) if(box[i][j]==0)return 0 ;
	return 1;
}
void dfs(int x,int y,int k){
	//cout << k<<endl;
	if(k == step){
		Find = judge();
		if(Find) {ans = k;}
		return;
	}
	if(Find || x == 5) return;
	s.e[s.back++]= P(x,y);
	c(x,y); if(y<4){dfs(x,y+1,k+1); }else {dfs(x+1,1,k+1);}
	c(x,y); if(!Find)s.back--;if(y<4)dfs(x,y+1,k);else dfs(x+1,1,k);
}

void solve(){
	for(step = 0; step <= 16 ; step++){
		s.back = s.front;
		dfs(1,1,0);
		if(Find)break;
	}
	if(Find) {
		cout << ans<<endl;
		while(s.back!=s.front){
		P a = s.e[--s.back];
		cout << a.x <<" "<< a.y<<endl;
		}
	} 
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	input();
	solve();
	return 0;
} 