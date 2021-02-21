#include <bits/stdc++.h>
#include "wavelet.h"

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

int main() {
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count(); mt19937 mt(seed);
  int m, g, N;
  cin >> N >> m >> g;

  Wavelet<int> w(m, g);

  assert (w.get_m() == m);
  assert (w.get_g() == g);
  assert (w.get_mg() == m * g);  

  vector<vector<int>> mcw(m, vector<int>(m * g));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m * g; ++j) {
      cin >> mcw[i][j];
    }
  }
  
  // testing mcw creation
  w.set_mcw(mcw);
  assert (w.get_mcw() == mcw);
  
  vector<int> message(N);  
  for (int i = 0; i < N; ++i) {
    message[i] = mt() % 2 == 0 ? -1 : 1;
  }
  
  cout << "-> N = " << N << ' ';
  
  // testing encoding
  set<int> alphabet;
  for (int i = -m * g; i <= m * g; i += 2) {
    alphabet.insert(i);
  }

  for (int i = 0; i < (int) encoded.size(); ++i) {
    if (alphabet.count(encoded[i]) == 0) {
      cerr << "=> symbol not from alphabet\n";
      return 1;
    }
  }

  // testing decoding
  vector<int> decoded = w.decode(N, encoded);

  for (int i = 0; i < N; ++i) {
    if (decoded[i] == m*g) {
      assert (message[i] == 1);
    }
    else if (decoded[i] == -m*g) {
      assert (message[i] == -1);
    }
    else {
      int OK = message[i] == -1 ? -m * g : m * g;
      cerr << "=> symbol " << decoded[i] << "should be " << OK << '\n';
      return 0;
    }
  }  
  
  cout << "=> OK\n";
  
  return 0;
  
}
