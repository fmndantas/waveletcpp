#include <bits/stdc++.h>
#include "../wavelet/wavelet.h"

using namespace std;

/**
   BPSK transmission through channel with white-noise and without wavelet encoding
   EbN0 as varying parameter
   Hard-decoding decision scheme: source -> encoding -> modulation -> channel -> demodulation -> decoding -> error estimation
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
    // demodulating with ask scheme
    vector<double> dem(enc.size());
    for (int i = 0; i < (int) channel.size(); ++i) {
      int geq = lower_bound(ask.begin(), ask.end(), channel[i]) - ask.begin();
      // nearest >=
      double dgeq = ask[min(geq, (int) ask.size())];
      // nearest <
      double dl = ask[max(0, geq - 1)];
      if (fabs(dl - channel[i]) <= fabs(dgeq - channel[i])) {
	dem[i] = dl;
      }
      else {
	dem[i] = dgeq;
      }
    }
    for (int i = 0; i < (int) dem.size(); ++i) {
      if (abs(dem[i]) > m * g) {
	cerr << "error => symbol not from alphabet\n";
	return 1;
      }
    }
    // decoding
    vector<double> dec = w.decode(n, dem);
    for (int i = 0; i < (int) dec.size(); ++i) {
      dec[i] = dec[i] >= 0 ? 1 : -1;
    }    
    // counting wrong bits
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans += (dec[i] != x[i]);
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

