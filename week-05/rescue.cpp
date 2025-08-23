#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>

using namespace std;

void organize_books(int w, const vector<string>& books) {
    map<char, vector<string>> shelves;

    for (const string& book : books) {
        char first_letter = toupper(book[0]);
        if (shelves[first_letter].size() < w) {
            shelves[first_letter].push_back(book);
        } else {
            cout << "Error: Shelf for " << first_letter << " is full" << endl;
            return;
        }
    }

    bool all_empty = true;

    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        if (!shelves[letter].empty()) {
            all_empty = false;
            cout << "Shelf " << letter << ":" << endl;
            int i = 1;
            for (const string& book : shelves[letter]) {
                cout << letter << i << ": " << book << endl;
                i++;
            }
        } else {
            cout << "Shelf " << letter << ":" << endl;
            cout << letter << "1: shelf is empty!" << endl;
        }
    }

    if (all_empty) {
        cout << "All shelfs are empty!" << endl;
    }
}

int main() {
    int w;
    cin >> w;

    vector<string> books;
    string book;

    while (cin >> book) {
        books.push_back(book);
    }

    organize_books(w, books);

    return 0;
}