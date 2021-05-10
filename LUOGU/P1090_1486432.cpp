#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdio>
#include <queue> 
using namespace std;

priority_queue<int,vector<int>,greater<int> > q;

int main()
{


	
	int n;
	cin >> n;
	int k ;
	for(int i = 1; i <= n ; i++)
	{
		cin >> k;	
		q.push(k);
	}
	long long ans=0;
	int a,b;
	for(int i = 1; i <= n-1 ; i ++)
	{
		a = q.top();q.pop();
		b = q.top();q.pop();
		q.push(a+b);
		ans += a+b;
		
	}
	
	cout << ans;
	//lol
	
	
	return 0;
}  