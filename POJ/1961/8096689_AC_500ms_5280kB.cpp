#include <cstdio>
#include <cstring>
using namespace std;
//Product by MiracleEEEE
int N, next[1000005], kase;
char s[1000005]; 
inline int read(){
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool solve(){
	while (scanf("%d",&N) && N) {
		scanf("%s",s);
		memset(next, 0, sizeof(next));
		int j = -1; next[0] = -1;
		for (int i = 1; i < N; i ++) {
			while (j != -1 && s[j + 1] != s[i]) j = next[j];
			if (s[j + 1] == s[i]) j++;
			next[i] = j;
		}
		//for (int i = 0; i < N; ++i) { printf("%d\n", next[i]);}
		printf("Test case #%d\n",++kase);
		for (int i = 1; i < N; i ++) {
			if (next[i] != -1 && (i + 1) % (i - next[i]) == 0) {
				printf("%d %d\n", i + 1, (i + 1)/ (i - next[i]));
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
} 
