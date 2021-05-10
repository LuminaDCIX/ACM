#include <iostream>
#include <set>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 1000+5;
int box[maxn][maxn];
int situ[maxn][maxn][4]; 
int p , m;
struct s
{
    int dir;
    int x;
    int y;
    int time; 
};

s turn_right(s a)
{
    s k = a;
    //memcpy(k , a ,sizeof(s));
    k.dir = (a.dir+3)%4;
    k.time ++;
    return k;
}

s turn_left(s a)
{
    s k = a ;
    //memcpy(k , a ,sizeof(s));
    k.dir = (a.dir+1)%4;
    k.time ++;
    return k;
}

s walk(s a,int n)
{
    if(a.dir == 0) 
    {
        bool search = 0;
        int x   =  a.x;
        int y   =  a.y;
        int num =  n ; 
        while(num --)
        {
            x-- ;
            if(x - 1 < 0 || y - 1 < 0) search = 1;
            if(box[x  ][y  ] == 1) search = 1;
            if(box[x-1][y  ] == 1) search = 1;
            if(box[x  ][y-1] == 1) search = 1;
            if(box[x-1][y-1] == 1) search = 1;
            if(search) break;
        }
        if(!search) { a.x -= n ; a.time++ ; return a;}
        
    }
    
    if(a.dir == 1) 
    {
        bool search = 0;
        int x   =  a.x;
        int y   =  a.y;
        int num =  n ; 
        while(num --)
        {
            y-- ;
            if(y - 1 < 0||x-1 < 0) search = 1;
            if(box[x  ][y  ] == 1) search = 1;
            if(box[x-1][y  ] == 1) search = 1;
            if(box[x  ][y-1] == 1) search = 1;
            if(box[x-1][y-1] == 1) search = 1;
            if(search) break;
        }
        if(!search)  { a.y -= n ; a.time++ ; return a;}
        
    }
    
    if(a.dir == 2) 
    {
        bool search = 0;
        int x   =  a.x;
        int y   =  a.y;
        int num =  n ; 
        while(num --)
        {
            x++;
            if(x >= p || y - 1 < 0) search = 1;
            if(box[x  ][y  ] == 1) search = 1;
            if(box[x-1][y  ] == 1) search = 1;
            if(box[x  ][y-1] == 1) search = 1;
            if(box[x-1][y-1] == 1) search = 1;
            if(search) break;
        }
        if(!search) { a.x += n ; a.time++ ; return a;}
    }
    
    if(a.dir == 3) 
    {
        bool search = 0;
        int x   =  a.x;
        int y   =  a.y;
        int num =  n ; 
        while(num --)
        {
            y++;
            if(y >= m || x - 1 < 0) search = 1;
            if(box[x  ][y  ] == 1) search = 1;
            if(box[x-1][y  ] == 1) search = 1;
            if(box[x  ][y-1] == 1) search = 1;
            if(box[x-1][y-1] == 1) search = 1;
            if(search) break;
        }
        if(!search) { a.y += n ; a.time++ ; return a;}
    }
    a.time = -1 ;
    return a;
}
queue<s> sit;
int main()
{

    cin >> p >> m;
    for(int i = 0 ; i < p ;i ++)
    {
        for(int j = 0; j < m ; j ++)
          cin >> box[i][j];
    }
	memset(situ,0,sizeof(situ));
    //bfsbfs
    s begin , end;
    cin >> begin.x >> begin.y >> end.x >> end.y;
    char a;
    cin >> a;
    if(a=='N') begin.dir = 0;
    if(a=='W') begin.dir = 1;
    if(a=='S') begin.dir = 2;
    if(a=='E') begin.dir = 3; 
    begin.time = 0;
    sit.push(begin);
    situ[begin.x][begin.y][begin.dir]=1;
    while(!sit.empty())
    {
        s k = sit.front(); sit.pop();
        if(k.x == end.x && k.y == end.y) {cout << k.time; return 0;        }
        s ls = turn_right(k);
        if(situ[ls.x][ls.y][ls.dir]==0){sit.push(ls); situ[ls.x][ls.y][ls.dir] = 1;	/*cout<< ls.x<<" " << ls.y << " "<<ls.dir<<endl;*/	}
        ls = turn_left(k);
        if(situ[ls.x][ls.y][ls.dir]==0){sit.push(ls); situ[ls.x][ls.y][ls.dir] = 1;	/*cout<< ls.x<<" " << ls.y << " "<<ls.dir<<endl;*/	}
        int n = 1;
        while(n!=4)
        {
            s l = walk(k,n);
            if(l.time == -1 ) break;
            else if(situ[l.x][l.y][l.dir]==0){situ[l.x][l.y][l.dir] = 1 ;sit.push(l) ; /*cout<< l.x<<" " << l.y << " "<<l.dir<<endl;*/}
			n++ ;
        }
        
    }
    cout << -1;
    
    return 0;
}