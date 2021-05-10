#include <cstdio>
#include <cstring>
using namespace std;

const int large = 500000;
struct TrieTree_Node{
	bool flag;
	int id;
	TrieTree_Node* next[27];
	TrieTree_Node(){
		flag = false;
		id = 0;
		memset(next, 0, sizeof(next));
	}
}root; 

int color = 0;
int degree[large + 1] = {0};
int set[large + 1];

int find(int x){
	return x == set[x] ? x : set[x] = find(set[x]);
}

void union_set(int a, int b){
	int pa = find(a);
	int pb = find(b);
	set[pb] = pa;
	return;
}

int hash(char *s){
	TrieTree_Node*p = &root;
	int len = 0;
	while(s[len] != '\0'){
		int index = s[len++] - 'a';
		if(!p->next[index])  p->next[index] = new TrieTree_Node;
		p = p->next[index];
	}
	if(p -> flag) return p->id;  //有了这种颜色 返回 id 
	else{
		p->flag = true;
		p->id = ++color;         //没有这种颜色 分配id 
		return p->id;
	}
}

int main(){
	for(int k = 1; k <= large; k++) set[k] = k;
	char a[11],b[11];
	while(scanf("%s %s\n",a,b) == 2){
		int i = hash(a);	//hash 索引插入 Trie树 
		int j = hash(b); 
		
		degree[i] ++;		//判断节点的度 
		degree[j] ++;		//检查是不是有欧拉回路 
		
		union_set(i,j);     //加入集合  拆分颜色  
	}
	int s = find(1);
	int num = 0;
	for(int i = 1; i <= color; i++){
		if(degree[i]%2 == 1)num++;
		if(num > 2) {
			printf("Impossible\n");
			return 0;
		}
		if(find(i) != s){         //与1不在同一集合 
			printf("Impossible\n");
			return 0;
		}	
	}
	if(num == 1){
		printf("Impossible\n");	
	}else printf("Possible\n");
	
	
	return 0;
}

