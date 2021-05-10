#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdio> 
using namespace std;
//Product by MiracleEEEE 
int k,A,B,N,M,book[105][105],ed; //N机器人
int box[105][105];
struct position{int x,y,f;}p[105]; 
void debug(){
	for(int i = 1 ; i <= A; i++){
		for(int j = 1; j <= B ; j++) cout << box[i][j];
		cout << endl;
	}
	cout << endl;
	
}
void input(){
	memset(box,0,sizeof(box));
	scanf("%d%d%d%d",&B,&A,&N,&M); //A宽 B高 
	for(int i = 1; i <= N ; i++){
		char c;
		scanf("%d%d %c",&p[i].y,&p[i].x,&c);
		if(c == 'N') p[i].f =0;
		if(c == 'E') p[i].f =1;
		if(c == 'S') p[i].f =2;
		if(c == 'W') p[i].f =3;
		box[p[i].x][p[i].y] = i;
		//debug();
	}
}

void print(int v,int p,int q){
	if(!ed){
		if(v == 1){
		cout << "Robot "<<p<<" crashes into the wall"<<endl;
		}
		if(v == 2){
		cout << "Robot "<<p<<" crashes into robot "<<q<<endl;
		}
		ed = 1;
	}
	
}
void solve(){
	ed = 0; 
	for(int i = 1; i <= M ; i++){
		int l,m; char c;
		scanf("%d %c%d",&l,&c,&m);
		for(int j = 1; j <= m && !ed ; j++){
			if(c == 'L') p[l].f = (p[l].f - 1 + 4) % 4;
			if(c == 'R') p[l].f = (p[l].f + 1 + 4) % 4;
			if(c == 'F'){
				if(p[l].f == 0){
					if(p[l].x+1== A+1 ){print(1,l,0);	}
					else if(box[p[l].x+1][p[l].y]==0){box[p[l].x][p[l].y] = 0;p[l].x++;box[p[l].x][p[l].y] = l;}
					else{print(2,l,box[p[l].x+1][p[l].y]);}}
				if(p[l].f == 1){
					if(p[l].y + 1 == B+1 ){print(1,l,0);	}
					else if(box[p[l].x][p[l].y+1]==0){box[p[l].x][p[l].y] = 0;p[l].y++;box[p[l].x][p[l].y] = l;}
					else{print(2,l,box[p[l].x][p[l].y+1]);}}
				if(p[l].f == 2){
					if(p[l].x-1== 0 ){print(1,l,0);	}
					else if(box[p[l].x-1][p[l].y]==0){box[p[l].x][p[l].y] = 0;p[l].x--;box[p[l].x][p[l].y] = l;}
					else{print(2,l,box[p[l].x-1][p[l].y]);}}
				if(p[l].f == 3){
					if(p[l].y-1== 0 ){print(1,l,0);	}
					else if(box[p[l].x][p[l].y-1]==0){box[p[l].x][p[l].y] = 0;p[l].y--;box[p[l].x][p[l].y] = l;}
					else{print(2,l,box[p[l].x][p[l].y-1]);}}
			}
			//debug();
		}
	} if(!ed) cout << "OK"<<endl;
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	cin >> k;
	while(k--){
		input();
		solve();
	} 

	return 0;
} 