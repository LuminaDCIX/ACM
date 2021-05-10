#include <iostream>
#include <cstdio> 
using namespace std;
//Product by MiracleEEEE 
//1 2 3 4 5 6 7 8 9 10 11 12123
int S,D,ans;

void solve(){
	int k = 0; 
	int temp = 5 * S;
	if(D*4 < S) {cout << "Deficit" <<endl;return;	}
	while(temp>0){
		k++;
		temp-=S+D;
	} 
	//cout<< "K = " << k << endl;
	if(k < 4)ans = 12*(S) - 2*k*(S+D);
	if(k == 4) ans = 12*S - 9*(S+D);
	if(ans < 0) cout << "Deficit"; else cout << ans;
	cout << endl;
}//4  1 1 1 1 4 1 1 1 1  4 1
int main(){
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	while(cin >> S >> D){
		solve();
	}
	
	return 0;
} 