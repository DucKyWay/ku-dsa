#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

unordered_set<string> dict;
unordered_map<int, bool> map;
int max_len;

string target;

bool recursive(int in) {
    if (in == (int)target.size()) return true;
    if (map.count(in)) return map[in];

    for (int i = 1; i <= max_len ; i++) {
        string s = target.substr(in, i);
        if (dict.find(s) != dict.end()) {
            if (recursive(in + i)) {
                return map[in] = true;
            }
        }
    }
    return map[in] = false;
}

int main() {

    int n; 
    cin >> n;
    max_len = 0;
    dict.reserve(n*2);

    for (int i = 0; i < n; i++) {
        cin >> target;
        dict.insert(target);
        max_len = max(max_len, (int)target.size());
    }
    cin >> target;

    cout << (recursive(0) ? "POSSIBLE" : "IMPOSSIBLE");
    return 0;
}
