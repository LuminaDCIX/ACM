#include <iostream>
#include <cmath>
using namespace std;

int main()  {
    int g, b;
    cin >> g >> b;
    double eb = 1.0 * (b - 2) / 2, eg = 1.0 * g - 1;
    if(eb > eg) cout << ceil(2 + eg); else cout << ceil(2 + eb);
    return 0;    
}
