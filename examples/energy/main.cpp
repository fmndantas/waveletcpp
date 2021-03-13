#include<bits/stdc++.h>

using namespace std;

/*
  Form of output -> ebn0 | ber | coding power | transmission power | number of retransmissions
*/

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

    double E_frm_denc_tot = E_frm_denc * (Nrtx + 1);
    double E_frm_trns_tot = E_frm_trns * Nrtx;

    // if (g == 0) {
    //   E_frm_denc_tot = 0;
    // }
    
    cout << ebn0[i] << ' ' << BER << ' ' << E_frm_denc_tot << ' ' << E_frm_trns_tot << ' ' << Nrtx << '\n';
  }
  
  return 0;
}
