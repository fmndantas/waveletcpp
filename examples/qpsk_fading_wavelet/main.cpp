#include <bits/stdc++.h>
#include "../../wavelet/wavelet.h"

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
   Binary {-1, +1} source
   QPSK modulator
   AWGN, faded channel
   Wavelet encoding and decoding
   MMSE equalizator
   QPSK demodulator
   Soft decisor
*/

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();  mt19937 mt(seed);

  cout << fixed << setprecision(10);

  // n raw bits
  int n, m, g, EbN0_min, EbN0_max, EbN0_step, loErr;
  long long loTotal;
  cin >> n >> m >> g >> EbN0_min >> EbN0_max >> EbN0_step >> loErr >> loTotal;

  // loading wavelet
  vector<vector<double>> mcw(m, vector<double>(m * g));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m * g; ++j) {
      cin >> mcw[i][j];
    }
  }
  Wavelet<double> w(m, g);
  w.set_mcw(mcw);
  
  // qpsk modulator
  double A = 1;
  double M[] = {-A, A};
  
  // awgn generator
  default_random_engine generator;

  // fading distribution
  normal_distribution<double> alpha_g(0, sqrt(0.5));

  auto sgn = [](double x) {
    return x < 0 ? -1 : 1;
  };
  
  auto simulate = [&](double ebn0_linear) {
    const int N = n / 2;
    const double n0 = 0.5 * m * g / ebn0_linear;
    const double stddev = sqrt(n0 / 2);
    
    // source + mapping
    vector<double> modulated_p(N), modulated_q(N);
    for (int i = 0; i < N; ++i) {
      modulated_p[i] = M[mt() % 2];
      modulated_q[i] = M[mt() % 2];
    }

    // encoding
    vector<double> encoded_p = w.encode(modulated_p);
    vector<double> encoded_q = w.encode(modulated_q);
    int sz = encoded_p.size();
    
    // channel
    normal_distribution<double> awgn_g(0, stddev);
    vector<double> alpha_p(sz), alpha_q(sz), awgn_p(sz), awgn_q(sz), channeled_p(sz), channeled_q(sz);
    for (int i = 0; i < sz; ++i) {
      alpha_p[i] = alpha_g(generator);
      alpha_q[i] = alpha_g(generator);
      awgn_p[i] = awgn_g(generator);
      awgn_q[i] = awgn_g(generator);
      channeled_p[i] = alpha_p[i] * encoded_p[i] - alpha_q[i] * encoded_q[i] + awgn_p[i];
      channeled_q[i] = alpha_p[i] * encoded_q[i] + alpha_q[i] * encoded_p[i] + awgn_q[i];
    }

    // equalization
    vector<double> equalized_p(sz), equalized_q(sz);
    for (int i = 0; i < sz; ++i) {      
      double k = alpha_p[i] * alpha_p[i] + alpha_q[i] * alpha_q[i] + 1 / ebn0_linear;      
      equalized_p[i] = (channeled_p[i] * alpha_p[i] + channeled_q[i] * alpha_q[i]) / k;
      equalized_q[i] = (channeled_q[i] * alpha_p[i] - channeled_p[i] * alpha_q[i]) / k;
    }
    
    // decoding
    vector<double> decoded_p = w.decode(N, equalized_p);
    vector<double> decoded_q = w.decode(N, equalized_q);
    
    // demodulation + error computation
    int ret = 0;
    for (int i = 0; i < N; ++i) {
      ret += (sgn(decoded_p[i]) != sgn(modulated_p[i])) + (sgn(decoded_q[i]) != sgn(modulated_q[i]));
    }

    return ret;    
  };

  // EbN0 varying simulation
  cout << EbN0_max / EbN0_step - EbN0_min / EbN0_step + 1 << ' ' << g << '\n';
  for (int EbN0_db = EbN0_min; EbN0_db <= EbN0_max; EbN0_db += EbN0_step) {
    const double ebn0_linear = powf(10, 0.1 * EbN0_db);    
    int errors = 0, total = 0;
    while (errors < loErr && total < loTotal) {
      errors += simulate(ebn0_linear);
      total += n;
      debug(EbN0_db, errors, total);
    }
    cout << EbN0_db << ' ' << errors << ' ' << total << '\n';
  }
  
}

