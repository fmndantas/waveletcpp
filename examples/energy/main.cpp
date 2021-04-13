#include<bits/stdc++.h>

using namespace std;

template <typename A, typename B> string to_string(pair<A, B> p); 
template <typename A, typename B, typename C>string to_string(tuple<A, B, C> p);
template <typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> p); 
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); } 
string to_string(bool b) { return (b ? "true" : "false"); } 
string to_string(vector<bool> v) { bool first = true; string res = "{"; for (int i = 0; i < static_cast<int>(v.size()); i++) { if (!first) res += ", "; first = false; res += to_string(v[i]); } res += "}"; return res; }
template <size_t N>
string to_string(bitset<N> v) { string res = ""; for (size_t i = 0; i < N; i++) res += static_cast<char>('0' + v[i]); return res; }
template <typename A>
string to_string(A v) { bool first = true; string res = "{"; for (const auto &x : v) { if (!first) res += ", "; first = false; res += to_string(x); } res += "}"; return res; } 
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A, typename B, typename C> string to_string(tuple<A, B, C> p) { return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")"; }
template <typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> p) { return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")"; }
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << to_string(H); debug_out(T...); }
#ifndef ONLINE_JUDGE
#define debug(...) cerr << '[' << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

/*
  Form of output -> ebn0 | ber | coding power | transmission power | number of retransmissions
*/

const double inf = numeric_limits<double >::infinity();
const double pi = acos(-1);

int main() {

  // number of ebn0 points and input reading
  int n, m, g;
  cin >> n >> m >> g;
  vector<double> ebn0(n), wrong(n), frame(n);
  for (int i = 0; i < n; ++i) {
    cin >> ebn0[i] >> wrong[i] >> frame[i];
  }
  
  cout << n << '\n';

  // processor parameters
  // set<double> clocks = {1e6, 2e6, 4e6, 8e6, 16e6, 26e6, 32e6, 48e6, 64e6, 72e6, 80e6};
  // map<double, double> clock_ia = {
  // 		      {1e6, 0.51e-3},
  // 		      {2e6, 0.62e-3},
  // 		      {4e6, 0.84e-3},
  // 		      {8e6, 1.27e-3},
  // 		      {16e6, 2.15e-3},
  // 		      {26e6, 3.23e-3},
  // 		      {32e6, 4.63e-3},
  // 		      {48e6, 6.69e-3},
  // 		      {64e6, 8.67e-3},
  // 		      {72e6, 9.68e-3},
  // 		      {80e6, 10.7e-3},
  // };
  double rb = 250e3;
  double tb = 1 / rb;
  double kc = 4;
  double mg = m * g;
  double va = 1.8;
  double I = max((double) 0, kc * (2 * mg - 1) * rb);
  debug(I);
  assert (I <= 31e6);
  if (I) {
    I *= (48.0 / 31.0);
  }
  assert (I <= 48e6);
  // double ia = 0;
  // if (I) {
  //   assert (I <= 80e6);
  //   ia = clock_ia[*clocks.lower_bound(I)];
  //   debug(I / 1e6, *clocks.lower_bound(I) / 1e6, ia);
  // }
  double ia = 67e-6 * (I / 1e6);
  double pproc = va * ia;
  double ebitcod = tb * pproc;
  double fsz = 10 * 8;
  double eframecod = ebitcod * fsz;
  
  // propagation parameters
  double d = 100;
  double f = 2.4e9;
  double n0 = 1.380649e-23 * 303; 

  double nd = 30;
  double kf = 1;
  double Lf = 15 + 4 * (kf - 1);
  double Adb = 20 * log10(f / 1e6) + nd * log10(d) + Lf - 28;
  double A = powf(10, 0.1 * Adb);
  // debug(Adb, va, ia,  pproc);
  
  // double c = 3e8;
  // double MDdb = 0;
  // double MD = powf(10, MDdb / 10);
  // double A = (16 * pi * pi * d * d * f * f) / (MD * c * c);
  
  // energy computation
  for (int i = 0; i < n; ++i) {
    double ebn0db = ebn0[i];
    double ebitrecp = n0 * powf(10, 0.1 * ebn0db);
    double ebittran = 1.75 * A * ebitrecp;
    double eframetran = ebittran * fsz;    
    double BER = wrong[i] / frame[i];
    double FER = 1 - powf(1 - BER, fsz);
    double ntx = 1 / (1 - FER);
    double eframecodtot = eframecod, eframetranstot = eframetran;
    if (eframecodtot) {
      // codificacao e ntx * decodificacao-
      eframecodtot *= (1 + ntx);
    }
    if (ntx == inf) {
      eframetranstot = inf;
    }
    else {
      // ntx transmissoes
      eframetranstot *= ntx;
    }
    cout << ebn0[i] << ' ' << BER << ' ' << eframecodtot << ' ' << eframetranstot << ' ' << ntx << '\n';
  }
  
  return 0;
}


/*
  diminui d
  - diminui energia de transmissao do bit no receptor e portanto a energia geral
  - em um determinado momento, a energia de transmissao do bit eh tao pequena que a energia de codificacao se supera a de transmissao mesmo com as repeticoes e o sistema codificado gasta mais

  diminui taxa de transmissao
  - nao altera nada pq ebitcod nao depende de rb

  diminui tamanho do frame

 */
