#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& str) {
    vector<string> res;
    istringstream iss(str);
    string word;
    while (iss >> word) {
        res.push_back(word);
    }
    return res;
}

double percentage(int level) {
    switch (level) {
        case 1:     return 0.1;
        case 2:     return 0.2;
        case 3:     return 0.3;
        case 4:     return 0.4;
        case 5:     return 0.5;
        case 6:     return 0.65;
        case 7:     return 0.8;
        case 8:     return 1.0;
        default:    return 0;
    }
}

int main() {
    int a, b;
    cin >> a >> b;
    
    int n;    
    cin >> n;
    cin.ignore();

    vector<int> mana(n);
    vector<double> score(n);

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        vector<string> temp = split(line);

        string type = temp[0];
        int level = stoi(temp[1]);
        int manaCost = stoi(temp.back());

        int base = 0;
        if (type == "F" || type == "W")         base = 12; // Fire Wind
        else if (type == "A")                   base = 15; // Aqua?
        else if (type == "E")                   base = 10; // Earth
        else if (type == "L" || type == "D")    base = 20; // Light Dark

        mana[i] = manaCost;
        score[i] = base * percentage(level);
    }

    for(int i = 0; i < n; i++) {
        cout << "score: " << score[i] << " mana: " << mana[i] << endl;
    }

    // เลือก max i คาถา j mana
    vector<vector<double>> dp(a + 1, vector<double>(b + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = a; j >= 1; j--) { // สกิล
            for (int k = b; k >= mana[i]; k--) { // มานา
                dp[j][k] = max(dp[j][k], dp[j - 1][k - mana[i]] + score[i]);
            }
        }
    }

    // max score บน dyn prog
    double maxScore = 0;
    for (int j = 0; j <= b; j++) {
        if (dp[a][j] > maxScore) {
            maxScore = dp[a][j];
        }
    }

    cout << (int)maxScore << endl;

    return 0;
}
