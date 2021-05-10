#include <cstdio>
#include <cstring>
using namespace std;
int row,col,pos,n,x,y,book[11][11]; char box[11][11],ok;
//Product by MiracleEEEE 
inline int read_num(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();}
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool judge(){
	if(x <= 0 || x > row || y <= 0 || y > col){
		printf("%d step(s) to exit\n",n ); return true;
	}else if(book[x][y] != 0){
		printf("%d step(s) before a loop of %d step(s)\n", book[x][y] - 1, n - book[x][y]+ 1); return true;
	}else book[x][y] = ++n;
	return false;
}
bool input(){
	memset(box,0,sizeof(box)); n = 0; memset (book, 0, sizeof(book)); ok = 1;
	x = 1; y = pos;
	if(judge()) ok = 0; 
	for(int i = 1 ; i <= row; i++){
		getchar();
		for(int j = 1; j <= col  ; j ++) {
			char ch = getchar();
			box[i][j] = ch;
		}
	}
	return true;
}

bool solve(){
	for(int i  = 1; i <= row * col ; i++){
		if(ok && box[x][y] == 'N') {--x; if(judge()) ok = 0;}
		if(ok && box[x][y] == 'S') {++x; if(judge()) ok = 0;}
		if(ok && box[x][y] == 'W') {--y; if(judge()) ok = 0;}
		if(ok && box[x][y] == 'E') {++y; if(judge()) ok = 0;}
	}
	
	return true;
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	while(scanf("%d%d%d",&row,&col,&pos)){
		if(row == 0 && col == 0 && pos == 0) break;
		input();
		solve();
	}
	return 0;
} 