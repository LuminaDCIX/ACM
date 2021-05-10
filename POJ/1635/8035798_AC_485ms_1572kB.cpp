#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
//Product by MiracleEEEE 
inline int read(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();} 
	while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	cin >> n;
	return true;
}
string dfs ( string str ) {
	//cout<<str.length()<<endl; 
 	int num_1 = 0, num_0 = 0, len = str.length(), pos = 1;
 	vector<string> vc;
 	for ( int i = 1; i < len - 1; i ++ ) {
 		if ( str[i] == '0' ) num_0 ++; else num_1 ++;
		if( num_0 == num_1 ) {
			string str2 = str.substr( pos , num_0 + num_1 );
			//cout << str2.length()<<" "<< num_0<<" "<<num_1<<" "<<str2<<endl;
			if( str2.length() != 2 ) {str2 = dfs(str2);};
			vc.push_back( str2 );
			pos = i + 1; num_0 = 0,num_1 = 0;
		}
	}
	string str2 = ""; sort( vc.begin(), vc.end());
	int sz = vc.size();
	for ( int i = 0; i < sz; i ++ ) str2 += vc[i];
	str2 = "0" + str2 + "1"; 
	vc.clear();
	return str2;
}
bool solve(){
	for ( int i = 1; i <= n; i ++ ) {
		string A, B;
		cin >> A >> B;
		A = "0" + A + "1"; B = "0" + B + "1";
		A = dfs( A ); B = dfs( B );
	    //cout << A << " " << B<< endl;
		if(A == B)cout << "same\n";else cout << "different\n";
	}
	return true;
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	input();
	solve();
	return 0;
} //123