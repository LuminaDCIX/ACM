#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define PB push_back
#define FI first
#define SE second
#define SIZ(x) ((int)x.size())
#define SET(x,k) memset(x,k,sizeof(x))
#define ALL(x) x.begin(),x.end()

typedef long long LL;
typedef long double DB;
typedef vector<int> VI;
typedef pair<int,int> PII;

inline LL read() {
	LL f=1,x=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

int main() {
	LL r,c,d,x,y;
	cout <<setiosflags(ios::fixed);
	cout << setprecision(15);
	r=read(),c=read(),d=read(),x=read(),y=read();
	
	DB x1,y1,x2,y2;
	if ((x-c)*(x-c)+(y-d)*(y-d)>=r*r) {
		cout<<c<<" "<<d<<" "<<r<<endl;
		return 0;
	}
	if (c!=x) {
		c=-c,d=-d;		
		DB k=(DB)(-d-y)/(DB)(-c-x),b=y-k*x;
		x1=-(sqrtl((k*k+1)*r*r-c*c*k*k+(2*c*d+2*b*c)*k-d*d-2*b*d-b*b)+(d+b)*k+c)/(k*k+1);
		y1=-(k*(sqrtl(k*k*r*r+r*r-c*c*k*k+2*c*d*k+2*b*c*k-d*d-2*b*d-b*b)+c)+d*k*k-b)/(k*k+1);
		x2=(sqrtl((k*k+1)*r*r-c*c*k*k+(2*c*d+2*b*c)*k-d*d-2*b*d-b*b)-(d+b)*k-c)/(k*k+1);
		y2=-(k*(c-sqrtl(k*k*r*r+r*r-c*c*k*k+2*c*d*k+2*b*c*k-d*d-2*b*d-b*b))+d*k*k-b)/(k*k+1);
	} else {
		x1=c,x2=c,y1=d-r,y2=d+r;
	}

	if ((x-x2)*(x-x2)+(y-y2)*(y-y2)<(x-x1)*(x-x1)+(y-y1)*(y-y1))
		cout<<(x+x1)/2<<" "<<(y+y1)/2<<" "<<sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1))/2<<endl;
	else
		cout<<(x+x2)/2<<" "<<(y+y2)/2<<" "<<sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2))/2<<endl;
	return 0;
}
