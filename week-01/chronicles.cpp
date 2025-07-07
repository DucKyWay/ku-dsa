#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<bool> isPrime(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false; //น้อยกว่า 2 มันไม่ใช่

    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }

    return is_prime;
}

int checkPrimeOrder(const vector<bool>& is_prime, int n) {
    int order = 0;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            order++;
            if (i == n) break;
        }
    }

    return order;
}

string printSuffix(int n) {
    if (n % 100 >= 11 && n % 100 <= 13) return "th";
    switch (n % 10) {
        case 1: return "st";
        case 2: return "nd";
        case 3: return "rd";
        default: return "th";
    }
}

int main() {
    int pages;
    cin >> pages;

    if (pages < 0) {
        cout << "ERROR!" << endl;
        return 0;
    } else {
        vector<bool> is_prime = isPrime(pages);

        if (is_prime[pages]) {
            int order = checkPrimeOrder(is_prime, pages);
            cout << order << printSuffix(order) << endl;
        } else {
            cout << "Unrelated" << endl;
        }
    }

    return 0;
}
