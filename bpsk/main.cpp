#include <bits/stdc++.h>

using namespace std;

/**
   Codificacao e decodificacao wavelet pro esquema bpsk
   O objetivo é testar a implementação. Assim, não há ruído
 */

int main() {
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
  mt19937 mt(seed);	 // gerador de Mersenne, distribuicao uniforme

  int m, g, n, mg;	      // posto, genero e tamanho da informacao
  cin >> m >> g >> n;
  mg = m * g;
  
  vector<int> X = {-1, 1}, x(n); // fonte  e informacao
  for (int i = 0; i < n; ++i) {	 // preenchimento da informacao
    int j = mt() % 2;
    x[i] = X[j];
  }  

  int sz = mg + n - m; // tamanho da codificacao e da mcw com preenchimento nulo
  vector<vector<int>> mcw(m, vector<int>(sz)); // mcw
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < mg; ++j) {
      cin >> mcw[i][j];
    }
  }

  vector<int> enc(sz);		// mensagem codificada
  int tmp;
  for (int i = 0, s = 0; i < n; i += m, ++s) { // codificacao
    for (int j = 0; j < mg; ++j) {
      tmp = 0;
      for (int k = 0; k < m; ++k) {
	tmp += x[i + k] * mcw[k][j];
      }
      enc[m * s + j] += tmp;
    }
  }

  vector<int> dec(n);		// mensagem decodificada
  for (int i = 0, j = 0, r = 0; i < n; ++i, r = (r + 1) % m) { // decodificacao
    for (int k = 0; k < sz; ++k) {
      dec[i] += mcw[r][(k + j) % sz] * enc[k];
    }
    if ((i + 1) % m == 0) {
      j -= m;
      if (j < 0) {
	j += sz;
      }
    }
  }

  auto sign = [&](int i) {
    return i < 0 ? -1 : 1;
  };
  
  cout << "n=" << n << " m=" << m << " g=" << g << '\n';

  for (int i = 0; i < n; ++i) {	// sign(dec) deve ser igual a mensagem
    if (sign(dec[i]) != x[i]) {
      cout << "erro -> dec != x\n";
      return 0;
    }
  }
  
  cout << "ok -> dec = x\n";

}

