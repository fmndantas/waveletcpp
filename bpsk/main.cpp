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
  mt19937 mt(seed);	 // gerador de Mersenne, distribuicao uniforme

  int m, g, n, mg;	      // posto, genero e tamanho da informacao
  cin >> m >> g >> n;
  mg = m * g;
  
  vector<int> X = {-1, 1}, x(n); // fonte  e informacao
  for (int i = 0; i < n; ++i) {	 // preenchimento da informacao
    int j = mt() % 2;
    x[i] = X[j];
  }  

  // debug(x);
  
  vector<vector<int>> mcw(m, vector<int>(mg)); // mcw
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < mg; ++j) {
      cin >> mcw[i][j];
    }
  }

  // debug(mcw);

  int sz = mg + n - m;		// tamanho da codificacao
  vector<int> enc(sz);		// mensagem codificada
  int tmp;
  for (int i = 0, s = 0; i < n; i += m, ++s) { // codificacao
    for (int j = 0; j < mg; ++j) {
      tmp = 0;
      for (int k = 0; k < m; ++k) {
	tmp += x[i + k] * mcw[k][j];
      }
      enc[m * s + j] += tmp;
    }
  }

  // debug(enc);

  vector<vector<int>> mcw0(m, vector<int>(sz)); // mcw com preenchimento nulo
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < mg; ++j) {
      mcw0[i][j] = mcw[i][j];
    }
  }

  // debug(mcw0);
  
  vector<int> dec(n);		// mensagem decodificada
  for (int i = 0, j = 0, r = 0; i < n; ++i, r = (r + 1) % m) { // decodificacao
    for (int k = 0; k < sz; ++k) {
      dec[i] += mcw0[r][(k + j) % sz] * enc[k];
    }
    if ((i + 1) % m == 0) {
      j -= m;
      if (j < 0) {
	j += sz;
      }
    }
  }

  // debug(dec);

  auto sign = [&](int i) {
    return i < 0 ? -1 : 1;
  };
  
  cout << "n=" << n << " m=" << m << " g=" << g << '\n';

  for (int i = 0; i < n; ++i) {	// sign(dec) deve ser igual a mensagem
    if (sign(dec[i]) != x[i]) {
      cout << "erro -> dec != x\n";
      return 0;
    }
  }
  
  cout << "ok -> dec = x\n";

}

