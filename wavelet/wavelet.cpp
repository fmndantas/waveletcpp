#include <vector>

#include "wavelet.h"

Wavelet::Wavelet(int m, int g) : m(m), g(g), mg(m * g) {
  mcw.assign(this->m, std::vector<int>(this->mg));
}

int Wavelet::get_m() {
  return this->m;
}

int Wavelet::get_g() {
  return this->g;
}

int Wavelet::get_mg() {
  return this->mg;
}

void Wavelet::set_mcw(const std::vector<std::vector<int>>& mcw) {
  this->mcw = mcw;
}

std::vector<std::vector<int>> Wavelet::get_mcw() {
  return this->mcw;
}

std::vector<int> Wavelet::encode(const std::vector<int>& to_encode) {
  int n = (int) to_encode.size(), tmp;
  std::vector<int> enc(mg + n - m);
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

std::vector<int> Wavelet::decode(const int n, const std::vector<int>& enc) {
  std::vector<int> dec(n);
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
