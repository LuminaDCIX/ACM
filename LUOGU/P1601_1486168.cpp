#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdio> 
using namespace std;
const int maxn = 10000 + 5;
int num1[maxn];
int num2[maxn];
int num3[maxn];
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	
	string a, b;
	
	cin >> a >> b;
	int len1 = a.length();
	int len2 = b.length();
	
	for( int i = 0 ; i < len1; i++) num1[len1-i-1] = a[i]-'0';
	for( int i = 0 ; i < len2; i++) num2[len2-i-1] = b[i]-'0';
	
	int len3 = (len1>len2?len1:len2)+1;
	int x =0;
	for(int i = 0 ; i < len3 ; i++)
	{
		num3[i] = num1[i] + num2[i] + x;
		x = num3[i] / 10;
		num3[i] %= 10;
		 
	}
	
	while(num3[len3-1]==0&&len3-1!=0) len3--;
	for(int i = len3 - 1 ; i >= 0;i--) printf("%d",num3[i]);
	
	 
	
	
	
	
	return 0;
} 