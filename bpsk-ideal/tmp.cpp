#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B> string to_string(pair<A, B> p); 
template <typename A, typename B, typename C>string to_string(tuple<A, B, C> p);
template <typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> p); 
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); } 
string to_string(bool b) { return (b ? "true" : "false"); } 
string to_string(vector<bool> v) { bool first = true; string res = "{"; for (int i = 0; i < static_cast<int>(v.size()); i++) { if (!first) res += ", "; first = false; res += to_string(v[i]); } res += "}"; return res; }
template <size_t N>
string to_string(bitset<N> v) { string res = ""; for (size_t i = 0; i < N; i++) res += static_cast<char>('0' + v[i]); return res; }
template <typename A>
string to_string(A v) { bool first = true; string res = "{"; for (const auto &x : v) { if (!first) res += ", "; first = false; res += to_string(x); } res += "}"; return res; } 
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A, typename B, typename C> string to_string(tuple<A, B, C> p) { return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")"; }
template <typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> p) { return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")"; }
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << to_string(H); debug_out(T...); }
#ifndef ONLINE_JUDGE
#define debug(...) cerr << '[' << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

/**
   Codificacao e decodificacao wavelet pro esquema bpsk
   O objetivo é testar a implementação. Assim, não há ruído
 */

int main() {
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
  // gerador de Mersenne, distribuicao uniforme
  mt19937 mt(seed);

  int m, g, n, mg;
  cin >> m >> g >> n;
  mg = m * g;

  // fonte e informacao
  int X[] = {-1, 1}, x[n];
  for (int i = 0; i < n; ++i) {
    int j = mt() % 2;
    x[i] = X[j];
  }  
  
  // tamanho do vetor codificação, mcw
  int sz = mg + n - m, mcw[m][mg];
  memset(mcw, 0, sizeof mcw);

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < mg; ++j) {
      cin >> mcw[i][j];
    }
  }

  // vector codificacao
  int tmp, enc[sz];
  memset(enc, 0, sizeof enc);

  // codificacao
  for (int i = 0, s = 0; i < n; i += m, ++s) {
    for (int j = 0; j < mg; ++j) {
      tmp = 0;
      for (int k = 0; k < m; ++k) {
	tmp += x[i + k] * mcw[k][j];
      }
      enc[m * s + j] += tmp;
    }
  }

  // vector decodificacao
  int dec[n];
  memset(dec, 0, sizeof dec);

  // codificacao
  for (int i = 0, j = 0, r = 0; i < n; ++i, r = (r + 1) % m) {
    for (int k = 0; k < mg; ++k) {
      dec[i] += mcw[r][k] * enc[k + j];
    }
    if ((i + 1) % m == 0) {
      j += m;
    }
  }

  auto sign = [&](int i) {
    return i < 0 ? -1 : 1;
  };
  
  cout << "n=" << n << " m=" << m << " g=" << g << '\n';

  for (int i = 0; i < n; ++i) {
    if (sign(dec[i]) != x[i]) {
      cout << "erro -> dec != x\n";
      return 0;
    }
  }
  
  cout << "ok -> dec = x\n";

}

