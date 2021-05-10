#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdio> 
using namespace std;
/*
struct BIGNUM{
	int s[4000];
	int len;
	BIGNUM(){len = 1;memset(s,0,sizeof(s));}
	void C(char *A,int l){
		for(int i = l - 1  ; i >= 0 ; i--) s[l-i-1] = A[i]-'0';
		len = l;
	}
	BIGNUM operator *(const BIGNUM &) const;
};

BIGNUM BIGNUM::operator * (const BIGNUM & T)const{
	BIGNUM ret;
	int i , j , up;
	int temp = 0, temp1;
	for(int i = 0; i < len; i++){
		up = 0;
		for(j = 0; j < T.len; j++){
			ret.s[i+j] += s[i] * T.s[j] + temp;
		}
	}
	for(int i = 0 ; i <= len + T.len ; i++){
		temp = ret.s[i] /10;
		ret.s[i+1] += temp;
		ret.s[i] %= 10;
		
	}
	return ret;
}*/

int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	double n, p;
	while(cin >> n >> p){
		int l = 0 ,r  = pow(10,9);
		while(1){
			int m = (l+r)/2;
			double c = pow(m,n);
			if(p == c) {
				cout << m << endl;break;
			}else{
				if(p > c) l = m + 1 ;
				else r = m;
			}
		}
	}	
	return 0;
} 