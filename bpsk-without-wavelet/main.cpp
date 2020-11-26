#include <bits/stdc++.h>
#include "../wavelet/wavelet.h"

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
   Codificacao e decodificacao wavelet pro esquema bpsk com ruido branco
   Eb/N0 variando
*/

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
  cout << fixed << setprecision(10);
  
  mt19937 mt(seed);

  int n, EbN0_min, EbN0_max;
  cin >> n >> EbN0_min >> EbN0_max;
  
  default_random_engine generator;

  // fonte
  const vector<double> X = {-1, 1};
  
  // simulacao para variacao do EbN0
  for (int EbN0_db = EbN0_min; EbN0_db <= EbN0_max; ++EbN0_db) {
    double EbN0_linear = powf(10, 0.1 * EbN0_db);
    double N0 = 1 / EbN0_linear;
    double sigma = sqrtf(N0 / 2);
    
    // modulacao
    vector<double> x(n);	
    for (int i = 0; i < n; ++i) {
      x[i] = X[mt() % 2];
    }

    // transmissao pelo canal
    vector<double> x_channel(x.begin(), x.end());
    normal_distribution<double> distribution(0, sigma);
    for (int i = 0; i < n; ++i) {
      x_channel[i] += distribution(generator);
    }

    // demodulacao
    vector<int> y(n);
    for (int i = 0; i < n; ++i) {
      y[i] = x_channel[i] >= 0 ? 1 : -1;
    }
    
    // verificacao dos bits com erro
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans += (x[i] != y[i]);
    }
    
    cout << EbN0_db << ' ' << 1.0 * ans / n << '\n';
  }
  
}

