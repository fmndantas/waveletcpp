#include <vector>

#ifndef WAVELET_H
#define WAVELET_H

class Wavelet {
 private:
  int m, g, mg;
  std::vector<std::vector<int>> mcw;

 public:
  Wavelet(int m, int g);

  int get_m();

  int get_g();

  int get_mg();

  void set_mcw(const std::vector<std::vector<int>>& mcw);

  std::vector<std::vector<int>> get_mcw();

  std::vector<int> encode(const std::vector<int>& to_encode);

  std::vector<int> decode(const int n, const std::vector<int>& enc);
};

#endif
