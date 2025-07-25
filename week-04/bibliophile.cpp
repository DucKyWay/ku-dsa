#include <iostream>
#include <stack>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    stack<string> pile;
    queue<string> miena, luna;
    vector<string> init_book;

    string line;
    if (!getline(cin, line)) return 0;

    stringstream ss(line);
    string book;
    while (ss >> book) {
        init_book.push_back(book);
    }

    for (int i = init_book.size() - 1; i >= 0; --i) {
        pile.push(init_book[i]);
    }

    while (getline(cin, line)) {
        if (line.empty()) continue;

        char cmd = line[0];
        if (cmd == 'M') { // หยิบหนังสือ มิเอนะ
            if (!pile.empty()) {
                miena.push(pile.top());
                pile.pop();
            }
        } else if (cmd == 'L') { // หยิบหนังสือ ลูน่า
            if (!pile.empty()) {
                luna.push(pile.top());
                pile.pop();
            }
        } else if (cmd == 'm') { // มิเอนะอ่านเสร็จ
            if (!miena.empty()) {
                pile.push(miena.front());
                miena.pop();
            }
        } else if (cmd == 'l') { // ลูน่าอ่านเสร็จ
            if (!luna.empty()) {
                pile.push(luna.front());
                luna.pop();
            }
        } else if (cmd == 'P' || cmd == 'p') { // Output
            cout << "Miena's Remaining Book(s) to be read: ";
            if (miena.empty()) {
                cout << "None\n";
            } else {
                queue<string> temp = miena;
                while (!temp.empty()) {
                    cout << temp.front();
                    temp.pop();
                    if (!temp.empty()) cout << " ";
                }
                cout << "\n";
            }

            cout << "Luna's Remaining Book(s) to be read: ";
            if (luna.empty()) {
                cout << "None\n";
            } else {
                queue<string> temp = luna;
                while (!temp.empty()) {
                    cout << temp.front();
                    temp.pop();
                    if (!temp.empty()) cout << " ";
                }
                cout << "\n";
            }

            cout << "Remaining Book(s) in the Pile: ";
            if (pile.empty()) {
                cout << "None\n";
            } else {
                vector<string> temp;
                stack<string> copy = pile;
                while (!copy.empty()) {
                    temp.push_back(copy.top());
                    copy.pop();
                }
                for (int i = 0; i < temp.size(); ++i) {
                    cout << temp[i];
                    if (i != temp.size() - 1) cout << " ";
                }
                cout << "\n";
            }

            cout << "====================" << endl;
        } else {
            cout << "Input Error";
            break;
        }
    }

    return 0;
}

/*
Incantation Mathematics DataStructures
m
m
p
M
M
L
l
l
l
m
m
L
P
s
*/