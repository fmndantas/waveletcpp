#include <bits/stdc++.h>

using namespace std;

/**
   Codificacao e decodificacao wavelet pro esquema bpsk
   O objetivo é testar a implementação. Assim, não há ruído
 */

int main() {
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();

  // gerador de Mersenne, distribuicao uniforme
  mt19937 mt(seed);

  int m, g, n, mg;
  cin >> m >> g >> n;
  mg = m * g;

  // fonte e informacao
  int X[] = {-1, 1}, x[n];
  for (int i = 0; i < n; ++i) {
    int j = mt() % 2;
    x[i] = X[j];
  }  
  
  // tamanho do vetor codificação, mcw
  int sz = mg + n - m, mcw[m][mg];
  memset(mcw, 0, sizeof mcw);

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < mg; ++j) {
      cin >> mcw[i][j];
    }
  }

  // vector codificacao
  int tmp, enc[sz];
  memset(enc, 0, sizeof enc);

  // codificacao
  for (int i = 0, s = 0; i < n; i += m, ++s) {
    for (int j = 0; j < mg; ++j) {
      tmp = 0;
      for (int k = 0; k < m; ++k) {
	tmp += x[i + k] * mcw[k][j];
      }
      enc[m * s + j] += tmp;
    }
  }

  // vector decodificacao
  int dec[n];
  memset(dec, 0, sizeof dec);

  // decodificacao
  for (int i = 0, j = 0, r = 0; i < n; ++i, r = (r + 1) % m) {
    for (int k = 0; k < mg; ++k) {
      dec[i] += mcw[r][k] * enc[k + j];
    }
    if ((i + 1) % m == 0) {
      j += m;
    }
  }
  
  cout << "n=" << n << " m=" << m << " g=" << g << '\n';

  for (int i = 0; i < n; ++i) {
    if (dec[i] == mg) {
      assert (x[i] = 1);
    }
    else if (dec[i] == -mg) {
      assert (x[i] == -1);
    }
    else {
      cout << "erro -> dec != x\n";
      return 0;
    }
  }
  
  cout << "ok -> dec = x\n";

}

