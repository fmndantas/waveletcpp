#include <vector>

#ifndef WAVELET_H
#define WAVELET_H

template <typename T>
class Wavelet {
 private:
  int m, g, mg;
  std::vector<std::vector<T>> mcw;

 public:
  Wavelet(int m, int g);

  int get_m();

  int get_g();

  int get_mg();

  void set_mcw(const std::vector<std::vector<T>>& mcw);

  std::vector<std::vector<T>> get_mcw();

  std::vector<T> encode(const std::vector<T>& to_encode);

  std::vector<T> decode(const int n, const std::vector<T>& enc);
};

#endif
