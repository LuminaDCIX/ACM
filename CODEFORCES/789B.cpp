#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 1000000001;
const int prime = 1000007;
ll b, q;
ll l, m;
vector<ll> Hash[1000018];
void _hash(ll x) {
	int key = (x % prime + prime) % prime;
	Hash[key].push_back(x);
}
bool find(ll x) {
	int key = (x % prime + prime) % prime;
	int sz = Hash[key].size();
	for (int i = 0; i < sz; i++) {
		if (Hash[key][i] == x) return true;
	}
	return false;
}
int main() {
	ios::sync_with_stdio(false);
	cin >> b >> q >> l >> m;
	int x;
	for (int i = 1; i <= m; ++i) {
		cin >> x;
		_hash(x);
	}
	int ans = 0;
	int tot = 0;
	while (tot <= 500000) {
		if (abs(b) > l) { break; }
		if (!find(b)) ans++;
		b *= q;
		tot++;
	}
	if (tot == 500001 && ans >= 30000) cout << "inf" << endl;
	else cout << ans << endl;
	return 0;
}
