#include<iostream>
using namespace std;
typedef long long ll;
const ll mod=1000000007;
ll euler(ll x) {
	ll res = x;
	for (ll i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			while(x % i == 0) {
				x /= i;
			}
			res -= res / i;
		}
	}
	if (x > 1) res -= res / x;
	return res;
}
int main() {
	ios::sync_with_stdio(false);
	ll x, k;
	cin >> x >> k;
	ll res = x;
	k = (k + 1) / 2;
	while (k--) {
		res = euler(res);
		if(res == 1) break;
	} 
	cout << res % mod<< endl;
	return 0;
} 
/*
gcd(x,640 - x) = 15
gcd(x, 640) = 15
gcd(x / 5, 128) = 3
gcd(y, 128) = 3

*/
