#include <bits/stdc++.h>
#include "../wavelet/wavelet.h"

using namespace std;

/**
   BPSK transmission through channel with white-noise without wavelet encoding
   EbN0 as varying parameter
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

