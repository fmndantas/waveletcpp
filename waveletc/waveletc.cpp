#include <bits/stdc++.h>

using namespace std;

class Wavelet {
private:
  int m, g, mg;
  vector<vector<int>> mcw;

public:
  Wavelet(int m, int g) : m(m), g(g), mg(m * g) {
    mcw.assign(this->m, vector<int>(this->mg));
  }

  int get_m() {
    return this->m;
  }

  int get_g() {
    return this->g;
  }

  int get_mg() {
    return this->mg;
  }

  void set_mcw(const vector<vector<int>>& mcw) {
    this->mcw = mcw;
  }

  vector<vector<int>> get_mcw() {
    return this->mcw;
  }

  vector<int> encode(const vector<int>& to_encode) {
    int n = (int) to_encode.size(), tmp;
    vector<int> enc(mg + n - m);
    for (int i = 0, s = 0; i < n; i += this->m, ++s) {
      for (int j = 0; j < this->mg; ++j) {
	tmp = 0;
	for (int k = 0; k < m; ++k) {
	  tmp += to_encode[i + k] * this->mcw[k][j];
	}
	enc[m * s + j] += tmp;
      }
    }
    return enc;
  }

  vector<int> decode(const int n, const vector<int>& enc) {
    vector<int> dec(n);
    for (int i = 0, j = 0, r = 0; i < n; ++i, r = (r + 1) % this->m) {
      for (int k = 0; k < this->mg; ++k) {
	dec[i] += this->mcw[r][k] * enc[k + j];
      }
      if ((i + 1) % m == 0) {
	j += m;
      }
    }
    return dec;
  }
};

int main() {
  cout << "Rodando testes de Wavelet\n";
  
  int m = 2, g = 4;

  Wavelet w(m, g);

  assert (w.get_m() == m);
  assert (w.get_g() == g);
  assert (w.get_mg() == m * g);  

  vector<vector<int>> mcw = {{1, 1, 1, -1, 1, 1, -1, 1}, {1, 1, 1, -1, -1, -1, 1, -1}};

  w.set_mcw(mcw);
  assert (w.get_mcw() == mcw);

  int N = 100000;
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
      cout << "Erro\n";
      return 0;
    }
  }  

  cout << "Testes foram OK\n";

  return 0;
}
