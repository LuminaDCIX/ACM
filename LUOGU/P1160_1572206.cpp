#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio> 
using namespace std;

int N ; 
typedef struct Lnode
{
	int data;
	Lnode *prior, *next ;
}Lnode, *LinkList;
LinkList position[100005];
LinkList L = new Lnode;
LinkList Locate(int i)
{
	return position[i];
}



void insert(int pos, int p,int i)
{
	LinkList ls = Locate(pos);
	if(ls == NULL) return ;
	Lnode *k = new Lnode;
	k->data = i;
	position[i] = k;
	if(p == 0)//insert i left
	{
		k->next = ls;
		k->prior = ls->prior;
		ls->prior->next = k;
		ls->prior = k;
		 
		/*Lnode *m = ls->prior;
		m->next = k;
		k->next = ls;
		k->prior = m;
		ls->prior = k;*/
	} 
	if(p == 1) //insert i right 
	{
		k->prior = ls;
		k->next = ls->next;
		ls->next->prior = k;
		ls->next = k;
		/*Lnode *m = ls->next;
		k->next = m;
		ls->next = k;
		m->prior = k;
		k->prior = ls;*/
	}	
	return ;
}

void Delete(int i)
{
	LinkList ls = Locate(i);
	if(ls == NULL) return ;
	ls->prior->next = ls->next;
	ls->next->prior = ls->prior;
	position[i] = NULL;
	delete ls; 
	return ;
}


int main()
{
	#ifdef LOCAL
//	freopen("TEXT.txt","r",stdin);
//	freopen("OUTPUT.txt","w",stdout);
	#endif
	 cin >> N;
	
	L->data = 0;
	int pos, p;
	Lnode *k = new Lnode;
	k->data = 1;
	k->prior = L; L->next = k; k->next = L; L->prior = k;
	position[1] = k;
	for(int i = 2; i<= N ; i++)
	{
		cin >> pos >> p;
		insert (pos,p,i);
		/*LinkList p = L->next;
		while(p!=L)
		{
			cout << p->data;
			p = p->next;
		}*/
	} 
	
	 
	int M; cin >> M;
	for(int j = 1 ; j<= M ; j++)
	{
		int l;
		cin >> l; 
		Delete(l);
		/*LinkList p = L->next;
		while(p!=L)
		{
			cout << p->data;
			p = p->next;
		}*/
	}
	

	for(LinkList ite = L->next ; ite != L ; ite = ite->next) 
	{
		cout << ite->data<< " ";	
	}
	
	return 0;
} 