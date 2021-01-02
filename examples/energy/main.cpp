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

double Ic(int g) {
  return 5 * pow(2, g - 1)  + 2 * (g - 4) + 17.25;
}

int main() {
  cout << fixed << setprecision(10);

  // number of ebn0 points and input reading
  int n, g;
  cin >> n >> g;
  vector<double> ebn0(n), wrong(n), frame(n);
  for (int i = 0; i < n; ++i) {
    cin >> ebn0[i] >> wrong[i] >> frame[i];
  }
  
  cout << n << '\n';

  // microprocessor parameters
  double Pproc = 24e-3, Ptx = 1e-3, Prx = 1e-3, I = 868e6, Rb = 500e3, f_d = 1e5;
 
  // energy computation
  for (int i = 0; i < n; ++i) {
    double E_bit_denc = Ic(g) * Pproc / I;
    double E_bit_trns = (Ptx + Prx) / Rb;

    double E_frm_denc = E_bit_denc * f_d;
    double E_frm_trns = E_bit_trns * f_d;

    double BER = wrong[i] / frame[i];
    double FER = 1 - powf(1 - BER, f_d);
    double Nrtx = 1 / (1 - FER);
    
    double E_frm_total = E_frm_denc + Nrtx * (E_frm_denc + E_frm_trns);

    cout << ebn0[i] << ' ' << BER << ' ' << E_frm_total << ' ' << Nrtx << '\n';
  }
  
  return 0;
}
