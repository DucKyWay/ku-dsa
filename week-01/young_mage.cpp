#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& str, char space = ' ') {
    vector<string> res;
    string temp;
    for (char ch : str) {
        if (ch == space && !temp.empty()) {
            res.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    if (!temp.empty()) {
        res.push_back(temp);
    }
    return res;
}
float percentage(int level) {
    switch (level) {
        case 1:     return 0.1f;
        case 2:     return 0.2f;
        case 3:     return 0.3f;
        case 4:     return 0.4f;
        case 5:     return 0.5f;
        case 6:     return 0.65f;
        case 7:     return 0.8f;
        case 8:     return 1.0f;
        default:    return 0.0f;
    }
}

float maxScore = 0.0f;
void recursive(int depth, int manaUsed, float scoreSum, int a, int b,
         const vector<int>& mana, const vector<float>& score) {
    
    if (depth == a || manaUsed > b) return;

    // bruteforce every skill
    for (int i = 0; i < (int)mana.size(); i++) {
        int newMana = manaUsed + mana[i];
        if (newMana > b) continue;
        
        float newScore = scoreSum + score[i];

        if (newScore > maxScore) {
            maxScore = newScore;
        }

        // recursion
        recursive(depth + 1, newMana, newScore, a, b, mana, score);
    }
}

int main() {
    int a, b, n;
    cin >> a >> b;
    
    cin >> n;
    cin.ignore();

    vector<int> mana(n);
    vector<float> score(n);

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        if (line.empty()) {
            i--;
            continue;
        }
        vector<string> temp = split(line);

        string type = temp[0];
        int level = stoi(temp[1]);
        int manaCost = stoi(temp.back()); // last

        int base = 0;
        if (type == "F" || type == "W")         base = 12; // Fire Wind
        else if (type == "A")                   base = 15; // Aqua?
        else if (type == "E")                   base = 10; // Earth
        else if (type == "L" || type == "D")    base = 20; // Light Dark

        mana[i] = manaCost;
        score[i] = base * percentage(level);
    }

    recursive(0, 0, 0.0f, a, b, mana, score);
    cout << (int)maxScore << endl;

    return 0;
}