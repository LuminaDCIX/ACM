import sys
from sys import stdin
sys.setrecursionlimit(100000)

N = 100000

dfn = [-1] * N
low = [-1] * N
dep = [-1] * N
cut = [0] * N
g = [[] for x in range(0, N)]
dfs_cnt = 0

def dfs(u, fa):
  global dfs_cnt
  global cut
  dfn[u] = dfs_cnt
  low[u] = dfs_cnt
  dfs_cnt = dfs_cnt + 1
  ch = 0
  for v in g[u]:
    if dfn[v] == -1:
      ch = ch + 1
      dfs(v, u)
      low[u] = min(low[u], low[v])
      if low[v] >= dfn[u]:
        cut[u] = 1
    else:
      low[u] = min(low[u], dfn[v])
  if fa == -1 and ch < 2:
    cut[u] = 0

def main():
  n, m = map(int, stdin.readline().split())
  for i in range(0, m):
    u, v = map(int, stdin.readline().split())
    global g
    u = u - 1
    v = v - 1
    g[u].append(v)
    g[v].append(u)
  for i in range(0, n):
    if dfn[i] == -1:
      dfs(i, -1)
  pnt = []
  for i in range(0, n):
    if cut[i] == 1:
      pnt.append(i + 1)
  print(len(pnt))
  print(" ".join(map(str, pnt)))


if __name__ == '__main__':
  main()


