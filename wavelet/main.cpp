#include <bits/stdc++.h>
#include "wavelet.h"

using namespace std;

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

  vector<int> encoded = w.encode(message);
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
