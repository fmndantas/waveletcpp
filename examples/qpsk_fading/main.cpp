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
   MMSE equalizator
   QPSK demodulator
   QPSK decisor
*/

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();  mt19937 mt(seed);

  cout << fixed << setprecision(10);

  // n raw bits
  int n, EbN0_min, EbN0_max, EbN0_step;
  cin >> n >> EbN0_min >> EbN0_max >> EbN0_step;
  
  // qpsk modulator
  double A = sqrt(2) / 2;
  double M[] = {-A, A};
  
  // awgn generator
  default_random_engine generator;

  // fading distribution
  normal_distribution<double> alpha_g(0, 0.5);

  auto sign = [](double x) {
    return x < 0 ? -1 : 1;
  };
  
  auto simulate = [&](double ebn0_linear) {
    const int N = n / 2;
    // todo: conferir variancia
    const double n0 = 0.5 / ebn0_linear;
    const double stddev = sqrt(n0 / 2);
    
    // source + modulation
    vector<complex<double>> modulated(N);
    for (int i = 0; i < N; ++i) {
      double real = M[mt() % 2], imag = M[mt() % 2];
      modulated[i] = complex<double>(real, imag);
    }

    // channel
    normal_distribution<double> awgn_g(0, stddev);
    vector<complex<double>> alpha(N), awgn(N);
    for (int i = 0; i < N; ++i) {
      alpha[i] = complex<double>(alpha_g(generator), alpha_g(generator));
      awgn[i] = complex<double>(awgn_g(generator), awgn_g(generator));
    }
    vector<complex<double>> channeled(N);
    for (int i = 0; i < N; ++i) {
      channeled[i] = alpha[i] * modulated[i] + awgn[i];
    }

    // equalization
    vector<complex<double>> equalized(N);
    for (int i = 0; i < N; ++i) {      
      double k = norm(alpha[i]) + 1 / ebn0_linear;
      equalized[i] = (channeled[i] * conj(alpha[i])) / k;
    }

    // demodulation + error computation
    int ret = 0;
    for (int i = 0; i < N; ++i) {
      if (sign(equalized[i].real()) != sign(modulated[i].real())) {
	ret++;
      }
      if (sign(equalized[i].imag()) != sign(modulated[i].imag())) {
	ret++;
      }
    }

    return ret;    
  };

  // EbN0 varying simulation
  cout << EbN0_max / EbN0_step - EbN0_min / EbN0_step + 1 << ' ' << 0 << '\n';
  for (int EbN0_db = EbN0_min; EbN0_db <= EbN0_max; EbN0_db += EbN0_step) {    
    const double ebn0_linear = powf(10, 0.1 * EbN0_db);    
    int errors = 0, total = 0;
    while (errors < 50 && total < 1e9) {
      errors += simulate(ebn0_linear);
      total += n;
      debug(EbN0_db, errors);
    }
    cout << EbN0_db << ' ' << errors << ' ' << total << '\n';
  }
  
}

