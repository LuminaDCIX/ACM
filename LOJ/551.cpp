#include <bits/stdc++.h>

using namespace std;

int main() {
        int T;
        cin>>T;
        while (T--) {
                long long k;
                cin>>k;
                cout<<((k<=3)?"No":"Yes")<<endl;
                cout<<((k<=3)?"No":((k&1)?"No":"Yes"))<<endl;
        }
}