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
               const vector<int>& mana, const vector<float>& score,
               float maxScorePerSkill) {
    // check
    if (depth == a || manaUsed > b) return;

    // pruning
    float possibleMax = scoreSum + maxScorePerSkill * (a - depth);
    if (possibleMax <= maxScore) return;

    for (int i = 0; i < (int)mana.size(); i++) {
        int newMana = manaUsed + mana[i];
        if (newMana > b) continue;
        
        float newScore = scoreSum + score[i];
        if (newScore > maxScore) {
            maxScore = newScore;
        }

        // recur
        recursive(depth + 1, newMana, newScore, a, b, mana, score, maxScorePerSkill);
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

    float maxInScore = 0.0f;
    for (float s : score) {
        if (s > maxInScore) maxInScore = s;
    }

    recursive(0, 0, 0.0f, a, b, mana, score, maxInScore);
    cout << maxScore << endl;

    return 0;
}

/*
2 3500
5
D 8 Black hole 3250
L 8 Divine Intervention 10000
F 6 Solar Flare 700
A 4 Blizzard 100
E 5 Magical Golem 130

26
*/

/*
3 150
10
F 2 FlameTouch 30
A 5 IceBolt 45
W 1 Breeze 20
D 3 DarkMist 35
L 4 LightWave 40
E 6 StoneCrash 60
F 7 InfernoBlast 75
A 2 FrostBite 25
W 5 Typhoon 50
L 8 HolyStorm 100
*/