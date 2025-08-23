#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cctype>
#include <cmath>
#include <cstdio>

int cal_track(int train, int line) {

}

int main() {

    int n, k;
    cin >> n >> k;
    queue<int> train;
    for(int i = 0; i < n; i++) {
        int no;
        cin >> no;
        train.push(no);
    }

    while(true) {
        int incoming = train.pop(); // clark
        cout << "[Clark] -> Train #" << incoming << " incoming!!" << endl;


    }

    return 0;
}