#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const int TABLE_SIZE = 20;

typedef struct tools {
    string name;
    double x, y, z;
} Tools;

unsigned long hash_name(const string& s) {
    unsigned long h = 5381;
    for (unsigned char c : s) h = ((h << 5) + h) + c;
    return h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Tools tool_list[TABLE_SIZE];
    bool used[TABLE_SIZE] = {false};
    int filled = 0;

    Tools tool;

    while (cin >> tool.name) {
        if (tool.name == "--------------------") break;
        cin >> tool.x >> tool.y >> tool.z;

        if (filled >= TABLE_SIZE) continue;

        unsigned long h = hash_name(tool.name);
        int idx = h % TABLE_SIZE;

        // linear probing
        for (int step = 0; step < TABLE_SIZE; ++step) {
            int p = (idx + step) % TABLE_SIZE;
            if (!used[p]) {
                tool_list[p] = tool;
                used[p] = true;
                ++filled;
                break;
            } else if (tool_list[p].name == tool.name) {
                tool_list[p] = tool;
                break;
            }
        }
    }

    cout << fixed << setprecision(2);

    string search;
    while (cin >> search) {
        bool find = false; 
        unsigned long h = hash_name(search);
        int idx = h % TABLE_SIZE;

        for (int step = 0; step < TABLE_SIZE; ++step) {
            int p = (idx + step) % TABLE_SIZE;
            if (!used[p]) break; 
            if (tool_list[p].name == search) {
                cout << "( " << tool_list[p].x
                     << ", " << tool_list[p].y
                     << ", " << tool_list[p].z << " )\n";
                find = true;
                break;
            }
        }

        if (!find) {
            cout << "Item not found.\n";
        }
    }

    return 0;
}

/*
Wand 20.5 26.4 1.97 
AdventurerCard 16.4 2.3 1.59 
MagicScroll 1.35 2.64 7.65 
-------------------- 
Sword 
Wand 
MagicScrol 
BusinessCard 
MagicScroll 
AdventurerCard
*/