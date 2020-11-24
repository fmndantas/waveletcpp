#include <bits/stdc++.h>
#include "wavelet.h"

using namespace std;

int main() {
  int m = 2, g = 4;

  Wavelet w(m, g);

  assert (w.get_m() == m);
  assert (w.get_g() == g);
  assert (w.get_mg() == m * g);  

  vector<vector<int>> mcw = {{1, 1, 1, -1, 1, 1, -1, 1}, {1, 1, 1, -1, -1, -1, 1, -1}};

  w.set_mcw(mcw);
  assert (w.get_mcw() == mcw);

  int N = 500000;
  vector<int> message(N, -1);

  vector<int> encoded = w.encode(message);
  vector<int> decoded = w.decode(N, encoded);
 
  for (int i = 0; i < N; ++i) {
    if (decoded[i] == m*g) {
      assert (message[i] == 1);
    }
    else if (decoded[i] == -m*g) {
      assert (message[i] == -1);
    }
    else {
      cout << "Wavelet -> erro\n";
      return 0;
    }
  }  

  cout << "Wavelet -> OK\n";
  
  return 0;
  
}