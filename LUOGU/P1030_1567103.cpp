#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int book[9];
char InOrder[9], PostOrder[9], PreOrder[9];
int PrePos = 0;
void Build(int PosBegin, int PosEnd ,int InBegin , int InEnd)
{
	if(book[PosEnd]==0)
	{
		PreOrder[PrePos++] = PostOrder[PosEnd];
		book[PosEnd] = 1;
	}
    
    //cout<< PreOrder[PrePos - 1];
    if(PosBegin >= PosEnd || InBegin >= InEnd) return ;
    int k = 0;
    while(InOrder[k]!=PostOrder[PosEnd]) k++;//gen in INorder
    int i = 0;
    while(PostOrder[i]!=InOrder[k - 1]) i++;//gen in PostOrder
    Build(PosBegin ,PosBegin + k - InBegin - 1,InBegin,k - 1);
    i = 0;
    while(PostOrder[i]!=InOrder[k + 1]) i++;
    //Build(i, PosEnd - 1, k + 1 , InEnd);
    Build(PosBegin + k - InBegin ,PosBegin + k - InBegin + InEnd - k -1, k + 1 , InEnd);
    /*while(InOrder[k]!=PostOrder[end]) ++k;
    PreOrder[PrePos++] = PostOrder[end];
    cout << PostOrder[k];
    if(begin == end) return ;
    int i = 0;
    while(InOrder[i]!=PostOrder[end]) ++i;
    Build(begin , i - 1);
    
    //cout << i;
    //Build(begin , k - 1);
    Build(i + 1 , end  );
    */
}




int main()
{

    cin >> InOrder >> PostOrder;
    memset(book,0,sizeof(book));
    Build(0,strlen(InOrder)-1,0,strlen(PostOrder)-1);
    for(int i = 0; i < PrePos ;i++)cout << PreOrder[i];
    //cout << PreOrder;
    return 0;
}