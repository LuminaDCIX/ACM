#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdio> 
using namespace std;
int box[31][31];
int dx[5]={0,0,1,-1,0};
int dy[5]={1,-1,0,0,0};
struct point
{
    int x;
    int y;
};
struct queue
{
    int front;
    int back;
    point s[905]; 
};

int main()
{
    #ifdef LOCAL
    //freopen("TEXT.txt","r",stdin);
    //freopen("OUTPUT.txt","w",stdout);
    #endif
    int n;
    cin>>n;
    if(n==1)
    {
        int k;
        cin >> k;
        
        cout << k; return 0;
     } 
    for(int i = 0 ; i < n ;i ++)
    {
        for( int j= 0; j < n;j++)
        {
            cin >> box[i][j];
            if(box[i][j]==0)box[i][j]=2;
        }
    }
    queue a;
    a.front = 0;
    a.back = 0;
    int i = 0;
        for(int j =0;j < n ; j++)
        {
            if(box[i][j]==2){
                a.s[a.back].x = i;
                a.s[a.back].y = j;
                a.back ++;
                while(a.front != a.back)
                {
                    int i = a.s[a.front].x;
                    int j = a.s[a.front].y;
                    a.front++;
                    for( int k =0;k<5;k++)
                    {
                        if(i+dx[k]>=0&&i+dx[k]<n&&j+dy[k]>=0&&j+dy[k]<n&&box[i+dx[k]][j+dy[k]]==2) 
                        {
                            box[i+dx[k]][j+dy[k]]=0;
                            a.s[a.back].x=i+dx[k];
                            a.s[a.back].y=j+dy[k];
                            a.back++;
                        }
                    
                    }
                }
				 
            }
        }
     
	 i = n-1;
        for(int j =0;j < n ; j++)
        {
            if(box[i][j]==2){
                a.s[a.back].x = i;
                a.s[a.back].y = j;
                a.back ++;
                while(a.front != a.back)
                {
                    int i = a.s[a.front].x;
                    int j = a.s[a.front].y;
                    a.front++;
                    for( int k =0;k<5;k++)
                    {
                        if(i+dx[k]>=0&&i+dx[k]<n&&j+dy[k]>=0&&j+dy[k]<n&&box[i+dx[k]][j+dy[k]]==2) 
                        {
                            box[i+dx[k]][j+dy[k]]=0;
                            a.s[a.back].x=i+dx[k];
                            a.s[a.back].y=j+dy[k];
                            a.back++;
                        }
                    
                    }
                }
				 
            }
        }  
		
	int j = 0;
        for(int i =0;i < n ; i++)
        {
            if(box[i][j]==2){
                a.s[a.back].x = i;
                a.s[a.back].y = j;
                a.back ++;
                while(a.front != a.back)
                {
                    int i = a.s[a.front].x;
                    int j = a.s[a.front].y;
                    a.front++;
                    for( int k =0;k<5;k++)
                    {
                        if(i+dx[k]>=0&&i+dx[k]<n&&j+dy[k]>=0&&j+dy[k]<n&&box[i+dx[k]][j+dy[k]]==2) 
                        {
                            box[i+dx[k]][j+dy[k]]=0;
                            a.s[a.back].x=i+dx[k];
                            a.s[a.back].y=j+dy[k];
                            a.back++;
                        }
                    
                    }
                }
				 
            }
        }   
   j = n-1;
        for(int i =0;i < n ; i++)
        {
            if(box[i][j]==2){
                a.s[a.back].x = i;
                a.s[a.back].y = j;
                a.back ++;
                while(a.front != a.back)
                {
                    int i = a.s[a.front].x;
                    int j = a.s[a.front].y;
                    a.front++;
                    for( int k =0;k<5;k++)
                    {
                        if(i+dx[k]>=0&&i+dx[k]<n&&j+dy[k]>=0&&j+dy[k]<n&&box[i+dx[k]][j+dy[k]]==2) 
                        {
                            box[i+dx[k]][j+dy[k]]=0;
                            a.s[a.back].x=i+dx[k];
                            a.s[a.back].y=j+dy[k];
                            a.back++;
                        }
                    
                    }
                }
				 
            }
        }
    for(int i = 0; i < n; i++)
	{
	    for(int j =0;j < n ; j++)
	    {
	        cout << box[i][j]<<' ';
	    }
	    cout << endl;
	}
	return 0;
} 