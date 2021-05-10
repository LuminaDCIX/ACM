#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdio> 
using namespace std;
//Product by MiracleEEEE
int k[100],num[100],N,n,p; 
bool input(){
	cin >> n;
	for(int i = 1; i <= n ; i++) cin >> num[i];
}

void judge(){
	//for(int i = 1; i <= n*2; i++ )cout << k[i]<<" ";
	//cout << endl;
	int temp = 0,pos = 1;
	for(int i = 1; i <= n ;i ++){
		while(k[pos]!=1)pos++;
		int m = pos;
		if(k[m-1]==0) {num[i] = 1;}
		else{
			temp++;int p =0;
			while(temp!=0&m>=0){
				if(k[--m]==0){temp--;p++;
				}else{temp++;	}
			}
			num[i] = p ;
		} pos++;
	}
}//(((()()())))
void solve(){
	p = 0;for(int i = 1; i <= num[1] ;i ++) {	k[++p] = 0; }
	k[++p] = 1;
	for(int i = 2;  i <=  n; i++){
		for(int j = 1; j <= num[i] - num[i-1]; j ++){k[++p] = 0;}
		k[++p] = 1;
	}
	judge();
	for(int i = 1; i <= n; i++ )cout << num[i]<<" ";
	cout << endl;
}

int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	cin >> N;
	while(N--){
		input();
		solve();
	}
	return 0;
} 
//21123
