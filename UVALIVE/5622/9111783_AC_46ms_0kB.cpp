#include <cstdio>  
#include <cctype>  
#include <cstring>  
#include <queue>  
using namespace std;  
  
const int dir[4][2] = {  
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}  
};  
const char reverseDir[4] = {  
    'S', 'N', 'E', 'W'  
};  
  
int R, C;  
char map[20][21];  
int best[20][20][20][20][2];  
struct State{  
    int boxRow, boxCol, manRow, manCol, push, walk;  
    bool operator < (const State& other)const{  
        if(push != other.push) return push > other.push;  
        return walk > other.walk;  
    }  
    void show()const{  
        printf("box@(%d,%d)  man@(%d,%d)  push:%d  walk:%d\n",   
                boxRow, boxCol, manRow, manCol, push, walk);  
    }  
};  
priority_queue<State> Q;  
  
inline bool isUreachable(int r, int c){  
    return r < 0 || r >= R || c < 0 || c >= C || map[r][c] == '#';  
}  
inline bool isBetter(const State& state){  
    int* a = best[state.boxRow][state.boxCol][state.manRow][state.manCol];  
    if(a[0] != state.push) return a[0] > state.push;  
    return a[1] > state.walk;  
}  
inline void setBest(const State& state){  
    int* a = best[state.boxRow][state.boxCol][state.manRow][state.manCol];  
    a[0] = state.push;  
    a[1] = state.walk;  
}  
  
void printPath(int br, int bc, int mr, int mc, int p, int w)  
{  
    if(p == 0 && w == 0) return;  
    for(int i = 0; i < 4; ++i){  
        int pmr = mr + dir[i][0], pmc = mc + dir[i][1];  
        if(isUreachable(pmr, pmc)) continue;  
        //if this move is walk, previously man can not be at current box's place  
        if(!(pmr == br && pmc == bc) && best[br][bc][pmr][pmc][0] == p && best[br][bc][pmr][pmc][1] == w-1){  
            printPath(br, bc, pmr, pmc, p, w-1);  
            putchar(tolower(reverseDir[i]));  
            break;  
        }  
        //if this move is push, previously box is at current man's place  
        int pbr = br + dir[i][0], pbc = bc + dir[i][1];  
        if(isUreachable(pbr, pbc)) continue;  
        if(pbr == mr && pbc == mc && best[pbr][pbc][pmr][pmc][0] == p-1 && best[pbr][pbc][pmr][pmc][1] == w){  
            printPath(pbr, pbc, pmr, pmc, p-1, w);  
            putchar(reverseDir[i]);  
            break;  
        }  
    }  
}  
void solve()  
{  
//initialize  
    while(!Q.empty()) Q.pop();  
    memset(best, 0x6F, sizeof(best));  
//find start  
    State now, nex;  
    for(int i = 0; i < R; ++i){  
        char* p = strchr(map[i], 'B');  
        if(p){  
            now.boxRow = i;  
            now.boxCol = p - map[i];  
        }  
        p = strchr(map[i], 'S');  
        if(p){  
            now.manRow = i;  
            now.manCol = p - map[i];  
        }  
    }  
    now.push = now.walk = 0;  
//AStar  
    Q.push(now);  
    setBest(now);  
    while(!Q.empty()){  
        now = Q.top(); Q.pop();  
//      now.show();  
        if(map[now.boxRow][now.boxCol] == 'T'){  
            printPath(now.boxRow, now.boxCol, now.manRow, now.manCol, now.push, now.walk);  
            puts("");  
            return;  
        }  
        for(int i = 0; i < 4; ++i){  
            nex = now;  
            nex.manRow += dir[i][0];  
            nex.manCol += dir[i][1];  
            if(isUreachable(nex.manRow, nex.manCol)) continue;  
            if(nex.manRow == now.boxRow && nex.manCol == now.boxCol){//this move is a push  
                //check if box can move or visit this state before  
                nex.boxRow += dir[i][0];  
                nex.boxCol += dir[i][1];  
                if(isUreachable(nex.boxRow, nex.boxCol)) continue;  
                ++nex.push;  
                if(!isBetter(nex)) continue;  
                Q.push(nex);  
                setBest(nex);  
            }  
            else{//this move is a walk  
                ++nex.walk;  
                if(!isBetter(nex)) continue;  
                Q.push(nex);  
                setBest(nex);  
            }  
        }  
    }  
    puts("Impossible.");  
}  
  
int main()  
{  
    int kase = 0, i;  
    while(scanf("%d%d", &R, &C), R){  
        while(getchar() != '\n') ;  
        for(i = 0; i < R; ++i) gets(map[i]);  
        printf("Maze #%d\n", ++kase);  
        solve();  
        puts("");  
    }  
    return 0;  
}  