#include <iostream>
using namespace std;
int N, M, S, flag, inq[105], vis[105];
double dist[105], V;
struct queue{
	int front, back, s[10010];
	void pop() {front ++;}
	void push(int x) {s[back++] = x;}
	int top() {return s[front];}
	int empty() {return front == back;}
}q;
struct data{double ext, com;}e[105][105];
void input() {
	cin >> N >> M >> S >> V;
	for (int i = 1; i <= M; i ++) {
		int a, b; double ext, com;
		cin >> a >> b >> ext >> com;
		e[a][b].ext = ext, e[a][b].com = com;
		cin >> ext >> com;
		e[b][a].ext = ext, e[b][a].com = com;
	}
}
void solve() {
	q.push(S);inq[S]++;dist[S] = V;vis[S]++;
	while (!q.empty()) {
		int x = q.top(); q.pop();
		inq[x] = 0;
		for (int i = 1; i <= N;i ++) {
			if (dist[i] < (dist[x] - 1.0 * e[x][i].com) * 1.0 * e[x][i].ext) {
				if (vis[i] > N){flag = true; break;}
				dist[i] = (dist[x] - 1.0 * e[x][i].com) * 1.0 * e[x][i].ext;
				if (!inq[i])q.push(i), inq[i] = 1;
				vis[i]++;
			}
			//for (int i = 1; i <= N; i ++) cout << dist[i] << " "; cout << endl;
		}
	}
	if (flag) cout << "YES" << endl;
	else cout << "NO";
}
int main() {
	input();
	solve();
	return 0;
}