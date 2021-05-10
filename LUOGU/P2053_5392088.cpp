// luogu-judger-enable-o2
#include <typeinfo>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;


namespace fastIO {
  //Author: MiracleEEEE
  template <int bufSz>
  struct inReader {
#define IL __inline__ __attribute__((always_inline))
  
    inReader(FILE* f): f(f), l(bufSz), r(bufSz) {}

    IL bool check() {
      if (l == r) {
        l = 0;
        r = fread(buf, 1, bufSz, stdin);
        if (l == r) {
          return true;
        }
      }
      return false;
    }
  
    IL int readChar() {
      return check() ? EOF : buf[l++];
    }

    IL int getChar() {
      return check() ? EOF : buf[l];
    }

    IL void spaceToken() {
      while (getChar() != EOF && isspace(getChar())) {
        readChar();
      }
    }
    
    template <typename T>
    T readInt() {    
      char ch = readChar();
      bool pos = true;
      while (ch < '0' || ch > '9') {
        pos = -1;
        ch = readChar();
      }

      T res = 0;
      while ('0' <= ch && ch <= '9') {
        res = 10 * res + ch - '0';
        ch = readChar();
      }
      return pos * res;
    }

    int readEOF() {
      spaceToken();
      if (getChar() == EOF) {
        return EOF;
      }
      return 0;
    }
  
    string readString() {
      spaceToken();
    
      string res;
      int ch = readChar();
      while (ch != EOF && !isspace(ch)) {
        res += ch;
        ch = readChar();
      }
      return res;
    }

    template <typename T>
    T readFloat() {
      spaceToken();
      int tmpSz = 0;
    
      int ch = readChar();
      if (ch == '-') {
        tmp[tmpSz++] = ch;
        ch = readChar();
      }
      while ('0' <= ch && ch <= '9') {
        tmp[tmpSz++] = ch;
        ch = readChar();
      }
      if (ch == '.') {
        tmp[tmpSz++] = ch;
        ch = readChar();
        while ('0' <= ch && ch <= '9') {
          tmp[tmpSz++] = ch;
          ch = readChar();
        }
      }

      tmp[tmpSz] = 0;
        
      if (typeid(T) == typeid(double)) {
        return strtod(tmp, NULL);
      } else if (typeid(T) == typeid(long double)) {
        return strtold(tmp, NULL);
      }
    }
    
    void readCharStar(char* out) {
      spaceToken();
      int ch = readChar();
      while (ch != EOF && !isspace(ch)) {
        *(out++) = ch;
        ch = readChar();
      }
      *out = 0;
    }
    
    char tmp[60];
    char buf[bufSz];
    FILE* f;
    int l;
    int r;
  };

  template <int bufSz>
  struct outWriter {
#define IL __inline__ __attribute__((always_inline))
  
    outWriter(FILE* f): f(f), pos(0) {
      doublePrinter[0] = '%';
      doublePrinter[1] = '.';
      doublePrinter[2] = '7';
      doublePrinter[3] = 'f';

      longDoublePrinter[0] = '%';
      longDoublePrinter[1] = '.';
      longDoublePrinter[2] = '7';
      longDoublePrinter[3] = 'L';
      longDoublePrinter[3] = 'f';
    }
    ~outWriter() {
      flush();
    }
  
    void setPrecision(int x) {
      doublePrinter[2] = x + '0';
      longDoublePrinter[2] = x + '0';
    }

    void flush() {
      if (pos == 0) {
        return;
      }
      fwrite(buf, 1, pos, f);
      pos = 0;
    }
    
    IL void writeChar(char ch) {
      if (pos == bufSz) {
        flush();
      }
      buf[pos++] = ch;
    }

    void writeEndline() {
      writeChar('\n');
    }

    template <typename T>
    void writeInt(T x) {
      if (x < 0) {
        putchar('-');
        x = -x;
      }
      int tmpSz = 0;
      while (x != 0) {
        tmp[tmpSz++] = '0' + x % 10;
        x /= 10;
      }
      if (tmpSz == 0) {
        writeChar('0');
      } else {
        while (tmpSz != 0) {
          writeChar(tmp[--tmpSz]);
        }
      }
    }
    
    void writeString(const string& str) {
      writeCharStar(str.c_str());
    }
  
    template <typename T>
    void writeFloat(T v) {
    
      if (typeid(T) == typeid(double)) {
        sprintf(tmp, doublePrinter, v);
      } else if (typeid(T) == typeid(long double)) {
        sprintf(tmp, longDoublePrinter, v);
      }
      writeCharStar(tmp);
    }
    
    void writeCharStar(const char* out) {
      while (*out != 0) {
        writeChar(*(out++));
      }
    }
    
    char tmp[60];
    char buf[bufSz];
    char doublePrinter[5];
    char longDoublePrinter[6];
    FILE* f;
    int pos;
  };
}
fastIO::inReader<4096> in(stdin);
fastIO::outWriter<4096> out(stdout);

#define read in.readInt<int>
#define write out.writeFloat<double>
#define endline out.writeEndline

const int N = 60 + 5;
const int M = 9 + 5;
const int MAXV = M * N + N + 5;
const int MAXE = 2 * (N + N * N * M + M * N) + 5;
const int s = MAXV - 2;
const int t = MAXV - 1;
const int inf = 0x3f3f3f3f;

struct MCMF {
  int cost[MAXE];
  int cap[MAXE];
  int nxt[MAXE];
  int ver[MAXE];
  int from[MAXE];
  int head[MAXV];
  int tot;

  void makeEdge(int _u, int _v, int _cap, int _cost) {
    cost[tot] = _cost;
    cap[tot] = _cap;
    nxt[tot] = head[_u];
    ver[tot] = _v;
    from[tot] = _u;
    head[_u] = tot++;
  }

  void addEdge(int _u, int _v, int _cap, int _cost) {
    makeEdge(_u, _v, _cap, _cost);
    makeEdge(_v, _u, 0, -_cost);
  }

  int pre[MAXV];
  int dist[MAXV]; 
  int inq[MAXV];

  bool spfa() {
    memset(dist, inf, sizeof(dist));
    queue <int> que;
    que.push(s);
    inq[s] = 1;
    dist[s] = 0;
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      inq[u] = 0;
      for (int o = head[u]; ~o; o = nxt[o]) {
        int v = ver[o];
        if (cap[o] && dist[v] > dist[u] + cost[o]) {
          dist[v] = dist[u] + cost[o];
          pre[v] = o;
          if (!inq[v]) {
            inq[v] = 1;
            que.push(v);
          }
        }
      }
    }
    return dist[t] != inf;
  }

  int solve() {
    int ans = 0;
    while (spfa()) {
      int x = inf;
      for (int o = pre[t]; ~o; o = pre[from[o]]) {
        x = min(x, cap[o]);
      }
      for (int o = pre[t]; ~o; o = pre[from[o]]) {
        cap[o] -= x;
        cap[o ^ 1] += x;
        ans += x * cost[o];
      }
    }
    return ans;
  }

  void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
    memset(pre, -1, sizeof(pre));
  }
} mcmf;

int n;
int m;

int mat[M][N];

int id(int i, int j) { // i for the jth time
  return n + (j - 1) * m + i;
}

int main() {
  mcmf.init();
  m = read();
  n = read();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      mat[j][i] = read();
    }
  } 
  for (int i = 1;  i <= n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < m; ++k) {
        mcmf.addEdge(j, id(k, i), 1, mat[k][j] * i);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    mcmf.addEdge(s, i, 1, 0);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      mcmf.addEdge(id(j, i), t, 1, 0);
    }
  }
  int sum = mcmf.solve();
  double ans = (double) sum / n;
  out.setPrecision(2);
  write(ans);
  endline();
  return 0;
}