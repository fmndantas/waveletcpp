#include <vector>
#include "wavelet.h"

template <typename T>
Wavelet<T>::Wavelet(int _m, int _g) : m(_m), g(_g), mg(_m * _g) {
  mcw.assign(this->m, std::vector<T>(this->mg));
}

template <typename T>
int Wavelet<T>::get_m() {
  return this->m;
}

template <typename T>
int Wavelet<T>::get_g() {
  return this->g;
}

template <typename T>
int Wavelet<T>::get_mg() {
  return this->mg;
}

template <typename T>
void Wavelet<T>::set_mcw(const std::vector<std::vector<T>>& _mcw) {
  this->mcw = _mcw;
}

template <typename T>
std::vector<std::vector<T>> Wavelet<T>::get_mcw() {
  return this->mcw;
}

/**
   Each m-slice of input is multiplied by MCW 
   and the result is accumulated from position 
   m onwards on enc vector.
 */
template <typename T>
std::vector<T> Wavelet<T>::encode(const std::vector<T>& to_encode) {
  int n = (int) to_encode.size();
  T tmp;
  std::vector<T> enc(mg + n - m);
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

template <typename T>
std::vector<T> Wavelet<T>::decode(const int n, const std::vector<T>& enc) {
  std::vector<T> dec(n);
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

template class Wavelet<int>;
template class Wavelet<double>;
