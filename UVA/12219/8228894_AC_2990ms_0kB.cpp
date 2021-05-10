#include <map>
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;
//Product by MiracleEEEE
int lch[600005], rch[600005], id[600005], uc, mc;
char ts[50000005];
int has[50000005];
string op[600005];
struct node{
        string op; int lc, rc;
        node(string a, int l, int r) {
                op = a;
                lc = l;
                rc = r;
        }
        node() {
                op = "";
                lc = 0;
                rc = 0;
        }
};
bool const operator < (const node a, const node b) {
              if(a.rc != b.rc) return a.rc > b.rc;
              if(a.lc != b.lc) return a.lc > b.lc;
              if(a.op != b.op) return a.op > b.op;
              return 0;
}
map<node, int> stree;
stack<int> m;
int build_tree(char *s, int l, int r, int& v) {
        int u = ++uc;
        id[u] = ++mc;
        string temp = "";
        temp += s[l];
        while(s[l + 1] != '(' && s[l + 1] != ')' && s[l + 1] !=',') {temp += s[l + 1]; ++l;}
        v = u;
        if(r - l == 0) {
                lch[u] = rch[u] = 0;
                if(!stree.count(node(temp, 0, 0))) {op[u] += temp;stree[node(op[u], 0, 0)] = id[u];return id[u];}
                else {--mc; id[u] = stree[node(temp, 0, 0)];return id[u];}
        }
        int c1= -1;
        if(s[l + 1] == '(') c1 = has[l + 1];  
        node tem;
        tem.op += temp;
        tem.lc = build_tree(s, l + 2, c1 - 1, lch[u]);
        tem.rc = build_tree(s, c1 + 1, r - 1, rch[u]);
        if(!stree.count(tem))stree[tem] = id[u], op[u] += temp;
        else {-- mc; id[u] = stree[tem];}
        return id[u];
}
//b(c(d(b,b),c(d(b,b),d)),d(c(d(b,b),c(d(b,b),d)),d))
//012345678901234567890123456789012345678901234567890
void dfs(int u) {
	if(op[u].length() != 0) cout << op[u] ;
	else {cout << id[u]; return;}
	if(lch[u] == 0 && rch[u] == 0) return;
	cout << '(';
	dfs(lch[u]);
	cout << ',';
	dfs(rch[u]);
	cout << ')';
}
bool input(){
	stree.clear();
	m.empty();
	memset(id, 0 ,sizeof(id));
	memset(ts, 0, sizeof(ts));
	for(int i = 0; i < 500005; i ++) op[i].clear();
	uc = 0, mc = 0;
	scanf("%s",ts);
	int len = strlen(ts);
	int ok = 0;
	int c = 0, p = 0, l = 0;
	for(int i = 0; i < len; i ++){
		switch(ts[i]) {
			case '(':++p,m.push(i);break;
			case ')':--p;break;
			case ',':
					has[m.top()] = i;
					m.pop();
					ok = 1;
 		}
	} 
	/*for(int i = 0; i < len; i ++) {
                switch(ts[i]) {
                        case '(': s += '('; break;
                        case ')': s += ')'; break;
                        case ',': s += ','; break;
                        default:
                                string temp = "";
                                temp += ts[i];
                                while(ts[i + 1] != '(' && ts[i + 1] != ')' && ts[i + 1] !=',') {temp += ts[i + 1]; ++i;}
                                if(operat.count(temp) == 0) operat[temp] = char(mapping - 1), atoperat[mapping - 1] = temp,mapping -= 1;
                                s += operat[temp];
                }
	}*/
	int v = 1;
	if(!ok) {cout << ts<< endl; return false;}
	return true;
}
bool solve(){
	int v = 1;
	build_tree(ts, 0, strlen(ts) - 1, v);
    dfs(1);
	cout << endl;
	return true;
}
int main()
{
	std::ios::sync_with_stdio(false);
	int n;	
	scanf("%d", &n);
	while(n --){
		if(input()) solve();
	}
	return 0;
}