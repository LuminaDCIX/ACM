#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdio> 
#include <queue>
using namespace std;
int sign = 4;
char num[2050];
int check(int l,int r)
{
	int b=0;
	int i=0;
	for(int v = l-1; v<r;v++ )
	{
		if(num[v]=='0') b = 1;
		if(num[v]=='1') i = 1;
		if(b&&i) return 3;
	}
	 if(b) return 2;
	return 1;
}

struct node
{
	char data;
	node* lc;
	node* rc;
	node()
	{
		data = 0;
		lc = NULL;
		rc = NULL; 
	 } 
};


struct tree
{
	node *root;
	
};
const int maxn = 10000+5;
node k[maxn];
queue<node*> freenode;
int init()
{
	for(int i = 0; i < maxn ; i++)
	freenode.push(&k[i]);
}

node* build(int l,int r)
{
	if(l>r) return NULL;
	
	node* a = freenode.front();
	freenode.pop();
	if(l==r)
	{
		if(num[l-1]=='0') a->data = 'B';
		else if(num[l-1]=='1')a->data = 'I';
		a->lc = NULL;
		a->rc = NULL;
		return a;
	}
	sign =4;
	sign = check(l,r);
	if(sign == 3) a->data = 'F';
	else if(sign == 2) a->data = 'B';
	else a->data = 'I';
	int m = (l+r)/2;
	a->lc = build(l,m);
	a->rc = build(m+1,r);
	return a;
}

void hx(node* b)
{
	if(b->lc!=NULL)hx(b->lc);
	if(b->rc!=NULL)hx(b->rc);
	cout << b->data;
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	
	tree ans;
	int i = 1;
	init(); 
	int n ;
	cin >> n;
	int r = 1<<n;
	ans.root = freenode.back();
	freenode.pop(); 
	cin >>num;
	sign = check(1,r);
	if(r>1)
	{
			if(sign == 2) ans.root->data = 'B';
			else if(sign == 1) ans.root->data='I';
			else ans.root->data = 'F';
			int m1 = r/2;
			ans.root->lc = build(1,m1);
			ans.root->rc = build(m1+1,r);
	}
	else 
	{
		if(sign == 2) ans.root->data = 'B';
		else if(sign == 1) ans.root->data='I';
		else ans.root->data = 'F';
		ans.root->lc = ans.root->rc = NULL; 
	}
	
	hx(ans.root);
	
	return 0;
} 