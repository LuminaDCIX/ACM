#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
//Product by MiracleEEEE
const int maxn = 1005;
struct queue{int front, tair; int s[maxn];
	void C() {
		front = tair = 0;
	}
}team, member[maxn]; 
map<int,int> find;
int n, kase;
inline int read_num(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();} 
	while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	for ( int i = 1; i <= n; i ++ ) {
		int length = read_num();
		for ( int j = 1; j <= length; j ++ ) {
			int key = read_num();
			find[key] = i;
		}
	}
	return true;
}
bool solve(){
	while ( scanf("%d", &n) == 1 && n ) {
		find.clear(); team.C(); for(int i = 1; i <= maxn ; i++ ) member[i].C(); 
		input(); 
		printf("Scenario #%d\n",++kase); 
		char order[8];
		while ( scanf("%s", order ) && order[0] != 'S' ) {
			if ( order[0] == 'E' ) {
				int num = read_num();
				int temp = find[num]; 
				if(member[temp].front ==  member[temp].tair ) team.s[(team.tair)%maxn] = temp, team.tair = (team.tair+1)%maxn;  
				member[temp].s[(member[temp].tair)%maxn] = num,member[temp].tair = (member[temp].tair+1)%maxn;
			}
			if ( order[0] == 'D' ) {
				int temp = team.s[team.front]; 
				write(member[temp].s[member[temp].front]) ; putchar('\n');
				member[temp].front = (member[temp].front + 1)%maxn;
				if( member[temp].front == member[temp].tair ) team.front = (team.front + 1)%maxn;
			}
		}
		putchar('\n');
	} 
	return true;
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	solve();
	return 0;
} //HEHE