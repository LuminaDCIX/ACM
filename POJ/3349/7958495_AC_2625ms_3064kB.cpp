#include<iostream>
#include<algorithm>
#include <cstdio>
using namespace std;
int a[6];
struct node
{
	int a,b,c,d,e,f;
}sf[100008];

int cmp(const void *a,const void *b)
{
     struct node *aa=(node *)a;
     struct node *bb=(node *)b;
	 if(aa->a!=bb->a)
		 return (aa->a)-(bb->a);
	 else if(aa->a==bb->a&&aa->b!=bb->b)
		 return (aa->b)-(bb->b);
	 else if(aa->a==bb->a&&aa->b==bb->b&&aa->c!=bb->c)
		 return (aa->c)-(bb->c);
	 else if(aa->a==bb->a&&aa->b==bb->b&&aa->c==bb->c&&aa->d!=bb->d)
		 return (aa->d)-(bb->d);
	 else if(aa->a==bb->a&&aa->b==bb->b&&aa->c==bb->c&&aa->d==bb->d&&aa->e!=bb->e)
		 return (aa->e)-(bb->e);
	 else
		 return (aa->f)-(bb->f);
}

int main()
{
	int n,i,j;
	bool flag=true;
	cin>>n;
	for(i=0;i<n;i++)
	{
		for(j=0;j<6;j++)
			scanf("%d",&a[j]);
		sort(a,a+6);
		sf[i].a=a[0];
		sf[i].b=a[1];
		sf[i].c=a[2];
		sf[i].d=a[3];
		sf[i].e=a[4];
		sf[i].f=a[5];
	}
	qsort(sf,n,sizeof(sf[0]),cmp);
	for(i=0;i<n-1;i++)
		if(sf[i].a==sf[i+1].a&&sf[i].b==sf[i+1].b&&sf[i].c==sf[i+1].c&&sf[i].d==sf[i+1].d&&sf[i].e==sf[i+1].e&&sf[i].f==sf[i+1].f)
		{
			cout<<"Twin snowflakes found.\n";
			flag=false;
			break;
		}
	if(flag)
		cout<<"No two snowflakes are alike.\n";

		
	return 0;
}
