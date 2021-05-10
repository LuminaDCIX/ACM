#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

const int N = 2000000 + 5;
int n, m;
char str[N];
char rev[N];
int vadd[N];
long long ans;
int bgn[N];
int end[N];
int ptr;
int s[N * 2];
int len;
struct Trie {
	struct node {
		node* nxt[26];
		int cnt;
		int add;
	};
	node pool[N * 2];
	int ptop;
	inline node* newnode() {
		return &pool[++ptop];
	}
	inline void insert(char *str)
	{
		node* now = &(pool[0]);
		for (int i = 0; i < len; ++i) {
			int x = str[i] - 'a';
			if (now->nxt[x] == NULL) {
				now->nxt[x] = newnode();
			}
			now = now->nxt[x];
			now->add += vadd[i];
		}
		now->cnt++;
		return;
	}
	inline long long find(char *str)
	{
		long long ret = 0;
		node *now = &(pool[0]);
		for (int i = 0; i < len; ++i) {
			int x = str[i] - 'a';
			if (now->nxt[x]) {
				now = now->nxt[x];
				if (now->cnt && vadd[i] && i != len - 1) {
					ret += now->cnt;
				}
			}
			else {
				return ret;
			}
		}
		ret += now->add + now->cnt;
		return ret;
	}
} t;
struct ExKmp {
	int nxt[N];
	int extend[N];
	inline void init(char* str)
	{
		int i = 0;
		nxt[0] = len;
		while (i + 1 < len && str[i] == str[i + 1]) {
			++i;
		}
		nxt[1] = i;
		int p = 1;
		for (i = 2; i < len; ++i) {
			if (i + nxt[i - p] < p + nxt[p]) {
				nxt[i] = nxt[i - p];
			}
			else {
				int j = nxt[p] + p - i;
				if (j < 0) {
					j = 0;
				}
				while (i + j < len && str[i + j] == str[j]) {
					++j;
				}
				nxt[i] = j;
				p = i;
			}
		}
		return;
	}
	inline void solve(char* s, char* t) //solve the extend[] of s
	{
		init(t);
		int i = 0;
		while (i < len && i < len && s[i] == t[i]) {
			++i;
		}
		extend[0] = i;
		int p = 0;
		for (int i = 1; i < len; ++i) {
			if (i + nxt[i - p] < p + extend[p]) {
				extend[i] = nxt[i - p];
			}
			else { 
				int j = p + extend[p] - i;
				if (j < 0) {
					j = 0;
				}
				while (i + j < len && j < len && s[i + j] == t[j]) {
					++j;
				}
				extend[i] = j;
				p = i;
			}
		}
		return;
	}
} sol;
inline void calc()
{
  for (int i = 0; i < n; ++i) {
		for (int j = bgn[i]; j < end[i]; ++j) {
			str[j - bgn[i]] = s[j];
		}
		str[end[i] - bgn[i]] = 0;
		len = end[i] - bgn[i];
		for (int j = 0; j < len; ++j) {
			rev[j] = str[j];
		}
		rev[end[i] - bgn[i]] = 0;
		reverse(rev, rev + len);
		sol.solve(rev, str);
		for (int j = 1; j < len; ++j) {
			if (sol.extend[j] == len - j) {
				++vadd[j - 1];
			}
		}
		ans += t.find(rev);
		for (int j = 0; j < len; ++j) {
			vadd[j] = 0;
			sol.extend[j] = sol.nxt[j] = 0;
		}
	}
	return;
}
int main()
{
	scanf("%d", &n);
	int f;
	for (int i = 0; i < n; ++i) {
		scanf("%d%s", &len, str);
		++ptr;
		bgn[i] = ptr;
		for (int j = 0; j < len; ++j) {
			s[ptr++] = str[j];
			rev[j] = str[j];
		}
		rev[len] = 0;
		end[i] = ptr;
		reverse(rev, rev + len);
		sol.solve(str, rev);
		for (int j = 1; j < len; ++j) {
			if (sol.extend[j] == len - j) {
				++vadd[j - 1];
			}
		}
		t.insert(str);
		for (int j = 0; j < len; ++j) {
			vadd[j] = 0;
			sol.extend[j] = sol.nxt[j] = 0;
		}
	}
	calc();
	printf("%lld\n", ans);
	return 0;
}
