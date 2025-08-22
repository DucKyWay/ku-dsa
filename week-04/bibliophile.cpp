#include <iostream>
#include <stack>
#include <queue>
#include <sstream>
using namespace std;

int main() {

    stack<string> pile;
    queue<string> miena, luna;
    string line;

    if (!getline(cin, line)) return 0;
    stringstream ss(line);
    string book;
    while (ss >> book) {
        pile.push(book);
    }

    string command;
    while (cin >> command) {
        if (command.empty()) continue;

        if (command == "M") { // หยิบหนังสือ มิเอนะ
            if (!pile.empty()) {
                miena.push(pile.top());
                pile.pop();
            }
        } else if (command == "L") { // หยิบหนังสือ ลูน่า
            if (!pile.empty()) {
                luna.push(pile.top());
                pile.pop();
            }
        } else if (command == "m") { // มิเอนะอ่านเสร็จ
            if (!miena.empty()) {
                pile.push(miena.front());
                miena.pop();
            }
        } else if (command == "l") { // ลูน่าอ่านเสร็จ
            if (!luna.empty()) {
                pile.push(luna.front());
                luna.pop();
            }
        } else if (command == "P" || command == "p") { // Output
            cout << "Miena's Remaining Book(s) to be read: ";
            if (miena.empty()) {
                cout << "None" << endl;
            } else {
                queue<string> temp = miena;
                while (!temp.empty()) {
                    cout << temp.front() << " ";
                    temp.pop();
                }
                cout << endl;
            }

            cout << "Luna's Remaining Book(s) to be read: ";
            if (luna.empty()) {
                cout << "None" << endl;
            } else {
                queue<string> temp = luna;
                while (!temp.empty()) {
                    cout << temp.front() << " ";
                    temp.pop();
                }
                cout << endl;
            }

            cout << "Remaining Book(s) in the Pile: ";
            if (pile.empty()) {
                cout << "None" << endl;
            } else {
                stack<string> temp = pile;
                vector<string> rev;
                while (temp.size() != 0) {
                    rev.push_back(temp.top());
                    temp.pop();
                }
                for (int i = rev.size() - 1; i > -1; i--) {
                    cout << rev[i] << " ";
                }
                cout << endl;
            }

            cout << "====================" << endl;
        } else {
            cout << "Input Error" << endl;
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