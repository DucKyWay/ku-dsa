#include <bits/stdc++.h>
using namespace std;

int main() {
    
    int n;
    cin >> n;
    vector<int> word(n);
    vector<int> speed(n);
    vector<double> res(n);

    for(auto& x : word) 
        cin >> x;
    for(auto& x : speed)
        cin >> x;

    sort(word.begin(), word.end());
    sort(speed.begin(), speed.end());

    for(int i = 0; i < n; i++) {
        res.push_back((double)word[i] / (double)speed[i]);
    }

    cout << *max_element(res.begin(), res.end());

    return 0;
}