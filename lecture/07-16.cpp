#include <iostream>
#include <string>
using namespace std;

struct Location {
    string tambon;
    string province; 
};

struct Flower {
    int id;
    string name;
    float price;
    Location location;
};

int main() {
    Flower flower_th[10];

    for (int i = 0; i < 3; i++) {
        cout << "No. " << i + 1 << endl;
        cout << "ID: ";
        cin >> flower_th[i].id;
        cin.ignore();

        cout << "Flower Name: ";
        getline(cin, flower_th[i].name);

        cout << "Price: ";
        cin >> flower_th[i].price;
        cin.ignore();

        cout << "Sub-District: ";
        getline(cin, flower_th[i].location.tambon);

        cout << "Provience: ";
        getline(cin, flower_th[i].location.province);

        cout << "---------------------------" << endl;
    }

    cout << "\nFlower Info:\n";
    for (int i = 0; i < 3; i++) {
        cout << "ID: " << flower_th[i].id << endl;
        cout << "Name: " << flower_th[i].name << endl;
        cout << "Price: " << flower_th[i].price << " บาท" << endl;
        cout << "From: Sub-District " << flower_th[i].location.tambon
             << ", Provience " << flower_th[i].location.province << endl;
        cout << "---------------------------" << endl;
    }

    return 0;
}
