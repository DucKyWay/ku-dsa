#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

int main() {
    int j, d;
    double K;
    cin >> j >> K; // เลขชี้, need
    cin >> d; // day

    double P = 1.0 * pow(10, j);  // สารอาหาร:เม็ด
    double total_nu = 0.0;
    int normmilk = 0;
    int promilk = 0;

    for (int i = 0; i < d; i++) {
        int n;
        cin >> n;

        double daily_nu = 0.0; // per day

        for (int m = 0; m < n; ++m) {
            daily_nu += P;
        }

        total_nu += daily_nu;
        double M_lung = daily_nu / K;
        double M_cow = n * (P / K);

        if (M_cow >= 1.0) {
            normmilk++;
        }

        if (fabs(2 * daily_nu - K) <= 1e-9) {
            promilk++;
        }
    }

    cout << "Milk : " << normmilk << endl;
    cout << "ProMax Milk : " << promilk << endl;
    cout << "Nutrient : " << fixed << setprecision(17) << total_nu << endl;

    return 0;
}
