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
   binary source transmission through channel with white-noise, wavelet encoding and ask modulation scheme
   EbN0 as varying parameter
   Soft-decoding decision scheme: source -> encoding -> modulation -> channel -> decoding -> demodulation (\lambda = 0) -> error estimation
*/

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();  mt19937 mt(seed);

  cout << fixed << setprecision(10);
  
  int n, m, g, EbN0_min, EbN0_max;
  cin >> n >> m >> g >> EbN0_min >> EbN0_max;

  vector<vector<double>> mcw(m, vector<double>(m * g));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m * g; ++j) {
      cin >> mcw[i][j];
    }
  }
  
  Wavelet<double> w(m, g);
  w.set_mcw(mcw);
  
  // awgn generator
  default_random_engine generator;

  // source
  vector<double> X = {-1, 1}, ask(m * g + 1);

  // ask options to demodulation
  int pos = 0;
  for (double i = -m * g; i <= m * g; i += 2) {    
    ask[pos++] = 1.0 * i;
  }

  auto simulate = [&](double EbN0_linear) {
    double N0 = m * g / EbN0_linear;
    double sigma = sqrtf(N0 / 2);    
    // information
    vector<double> x(n);	
    for (int i = 0; i < n; ++i) {
      x[i] = X[mt() % 2];
    }
    // encoding
    vector<double> enc = w.encode(x);    
    // transmitting with ask scheme
    vector<double> channel(enc.begin(), enc.end());
    normal_distribution<double> distribution(0, sigma);
    for (int i = 0; i < (int) enc.size(); ++i) {
      channel[i] += distribution(generator);
    }    
    // decoding
    vector<double> dec = w.decode(n, channel);
    // demodulating
    vector<double> dem(n);
    for (int i = 0; i < n; ++i) {
      dem[i] = (dec[i] >= 0 ? 1 : -1);
    }
    // counting wrong bits
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans += (dem[i] != x[i]);
    }
    return ans;
  };

  cout << EbN0_max - EbN0_min + 1 << '\n';

  // EbN0 varying simulation
  for (int EbN0_db = EbN0_min; EbN0_db <= EbN0_max; ++EbN0_db) {
    double EbN0_linear = powf(10, 0.1 * EbN0_db), pe_t = 0.5 * erfc(sqrtf(EbN0_linear));
    int n_runs = ceil((50.0 / pe_t) / n), now = 0;
    for (int i = 0; i < n_runs; ++i) {
      now += simulate(EbN0_linear);
    }
    cout << setw(2) << EbN0_db << setw(15) << 1.0 * now / (n_runs * n) << ' ' << setw(15) << pe_t << '\n';
  }
  
}

