// luogu-judger-enable-o2
#include <bits/stdc++.h>

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
        pos = 0;
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
#define write out.writeInt<int>
#define enter out.writeEndline()

using namespace std;

const int N = 50000 + 5;

struct LinearSieve {
  int p[N];
  bool notP[N];
  int mu[N];
  int mindiv[N];
  int tot;

  void solve(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!notP[i]) {
        p[tot++] = i;
        mindiv[i] = i;
        mu[i] = -1;
      }
      for (int j = 0; j < tot; ++j) {
        int k = p[j] * i;
        if (k > n) {
          break;
        }
        notP[k] = 1;
        mindiv[k] = p[j];
        if (mindiv[i] == p[j]) {
          mu[k] = 0;
          break;
        } else {
          mu[k] = mu[i] * -1;
        }
      }
    }
  }
};

LinearSieve s;

long long sum[N];

int main() {
  int T = read();
  s.solve(N - 1);
  int *mu = s.mu;
  for (int i = 1; i < N; ++i) {
    sum[i] = sum[i - 1] + mu[i];
  }

  for (int i = 0; i < T; ++i) {
    int n = read();
    int m = read();
    int d = read();
    n /= d;
    m /= d;
    int lim = min(n, m);
    int ans = 0;
    for (int j = 1, f, g; j <= lim; ++j) {
      int nxtn = n / (f = n / j);
      int nxtm = m / (g = m / j);
      int nxt = min(nxtn, nxtm);
      ans += (sum[nxt] - sum[j - 1]) * f * g;
      j = nxt;
    }
    write(ans);
    enter;
  }
  return 0;
}
