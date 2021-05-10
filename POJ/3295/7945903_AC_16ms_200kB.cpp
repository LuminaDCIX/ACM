#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cstdio> 
using namespace std;
//Product by MiracleEEEE 
int p,q,r,s,t,len,flag;
char m[105];
struct stack{int s[105],top;}l;
bool input(){
	scanf("%s",m); len = strlen(m);
	if(m[0] == '0') return false;
	return true;
}

bool judge(){
	l.top = 1;
	for(int i = len - 1; i >= 0 ; i--){
		if(m [i] == 'p') l.s[l.top++] = p;
		else if(m [i] == 'q') l.s[l.top++] = r;
		else if(m [i] == 'r') l.s[l.top++] = r;
		else if(m [i] == 's') l.s[l.top++] = s;
		else if(m [i] == 't') l.s[l.top++] = t;
		
		if(m[i] == 'K'){
			int a = l.s[--l.top], b = l.s[--l.top];
			if(a&&b) l.s[l.top++] = 1; else l.s[l.top++] = 0;
		}else if(m[i] == 'A'){
			int a = l.s[--l.top], b = l.s[--l.top];
			if(a || b) l.s[l.top++] = 1; else l.s[l.top++] = 0;
		}else if(m[i] == 'N'){
			int a = l.s[--l.top];
			if(!a) l.s[l.top++] = 1; else l.s[l.top++] = 0;
		}else if(m[i] == 'C'){
			int a = l.s[--l.top], b = l.s[--l.top];
			if(!a || b) l.s[l.top++] = 1; else l.s[l.top++] = 0;
		}else if(m[i] == 'E'){
			int a = l.s[--l.top], b = l.s[--l.top];
			if(a == b) l.s[l.top++] = 1; else l.s[l.top++] = 0;
		}
	}
	//cout <<l.top<< l.s[l.top - 1];
	return (l.s[l.top - 1]);
}
void solve(){
	for(p = 0; p <= 1; p++)
		for(q = 0; q <= 1; q++)
			for(r = 0 ; r <= 1; r++)
				for(s = 0; s <= 1; s++)
					for(t = 0; t <= 1; t++)	if(!judge()) {flag = 1; break;}
	if(!flag)cout<<"tautology" <<endl;
	else cout << "not" << endl;
	
}

int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	while(input()){
		flag = 0;
		solve();
	}
	
	return 0;
	
} 