#include <iostream>  
    #include <string>  
    #include <vector>  
    #include <algorithm>  
    using namespace std;  
      
    //***********************常量定义*****************************  
      
      
      
      
    //*********************自定义数据结构*************************  
      
      
      
      
    //********************题目描述中的变量************************  
      
      
      
      
    //**********************算法中的变量**************************  
      
    string DFS( string tree )  
    {  
        //只有前导0和结尾的1  
        //即已经到叶子节点，无子树，直接返回  
        if( tree == "01" )  return tree;  
      
        //去掉前导0和结尾的1  
        int len = (int)tree.size();  
        string root = tree.substr( 1, len-2 );  
      
        //求树的子树  
        //也就是求串的子串，DFS递归调用  
        int cnt = 0;  
        int start = 0;  
        vector<string> sub;  
        for( int i=0; i<len-2; i++ )  
        {         
            cnt += ( root[i] == '0' ) ? 1 : -1;  
              
            //当0和1的数目相等时，即找到一个子串  
            if( cnt == 0 )  
            {             
                sub.push_back( DFS( root.substr( start, i-start+1 ) ) );  
                start = i+1;  
            }         
        }  
      
        //加上前导0和结尾的1  
        string ans = "0";  
        //对串的子串进行排序  
        //因为排序是放在递归里, 所以最终对所有的子串都按字典顺序排序了  
        sort( sub.begin(), sub.end() );  
        int sz = (int)sub.size();     
        for( int j=0; j<sz; j++ )  
        {  
            ans += sub[j];  
        }  
        return ans + "1";  
    }  
      
      
    //***********************算法实现*****************************  
      
      
      
      
    //************************main函数****************************  
      
    int main()  
    {  
        //freopen( "in.txt", "r", stdin );        
          
        int caseNum;  
        cin >> caseNum;  
      
        while( caseNum-- )  
        {  
            string a, b, ansA, ansB;  
            cin >> a;  
            a = "0" + a + "1";    
            ansA = DFS( a );  
            cin >> b;  
            b = "0" + b + "1";        
            ansB = DFS( b );  
    		//cout << ansA << " " << ansB;
            if( ansA == ansB )        
                cout << "same" << endl;  
            else  
                cout << "different" << endl;  
        }  
              
        return 0;  
    }  
