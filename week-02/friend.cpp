#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

typedef struct dummy {
    string name;
    int hp;
    int atk;
    int def;
    int ener;
} Dummy;

typedef struct dummystate {
    Dummy* base; 
    int cur_hp;
    int energy;
    bool powered; // x2
    bool is_powerup_active;
    int powerup_turns_left;

    int curr_atk; 
    int curr_def;
} DummyState;

typedef struct powerup {
    int p;
    float atk;
    float def;
    int cooldown;
} PowerUp;

typedef struct battlecontext {
    DummyState* attacker;
    DummyState* defender;
    PowerUp* att_powerup;
    PowerUp* def_powerup;
    int* attacker_i;
    int* defender_i;
    bool is_miena_turn;
} Battle;

vector<string> split(const string& str, char space = ' ') {
    vector<string> res;
    string temp;
    for(char ch : str) {
        if(ch == space && !temp.empty()) {
            res.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    if(!temp.empty()) {
        res.push_back(temp);
    }
    return res;
}

PowerUp inPower() {
    string str;
    getline(cin, str);
    vector<string> tmp = split(str);

    PowerUp x;
    if(tmp.size() == 4) {
        x.p = stoi(tmp[0]);
        x.atk = stof(tmp[1]);
        x.def = stof(tmp[2]);
        x.cooldown = stoi(tmp[3]);
    } else {
        x = {0, 0.0f, 0.0f, 0};
    }
    return x;
}

Dummy inDummy() {
    string str;
    getline(cin, str);
    vector<string> tmp = split(str);

    Dummy x;
    if(tmp.size() == 5) {
        x.name = tmp[0];
        x.hp = stoi(tmp[1]);
        x.atk = stoi(tmp[2]);
        x.def = stoi(tmp[3]);
        x.ener = stoi(tmp[4]);
    } else { x = {"", 0, 0, 0, 0}; }
    return x;
}

Battle getBattle(
    int turn,
    vector<DummyState>& miena_list, vector<DummyState>& luna_list,
    PowerUp& miena, PowerUp& luna,
    int& miena_i, int& luna_i,
    int& miena_cd, int& luna_cd
) {
    bool is_miena_turn = (turn % 2 == 1);

    // return
    DummyState& attacker = is_miena_turn ? miena_list[miena_i] : luna_list[luna_i];
    DummyState& defender = is_miena_turn ? luna_list[luna_i] : miena_list[miena_i];
    PowerUp& att_powerup = is_miena_turn ? miena : luna;
    PowerUp& def_powerup = is_miena_turn ? luna : miena;
    int& attacker_i = is_miena_turn ? miena_i : luna_i;
    int& defender_i = is_miena_turn ? luna_i : miena_i;

    return {&attacker, &defender, &att_powerup, &def_powerup, &attacker_i, &defender_i, is_miena_turn};
}

string plural(int n) {
    if(n > 1) return "s";
    else return "";
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    PowerUp miena, luna;
    vector<Dummy> miena_dummy, luna_dummy;

    miena = inPower();
    for (int i = 0; i < n; i++) {
        miena_dummy.push_back(inDummy());
    }
    luna = inPower();
    for (int i = 0; i < n; i++) {
        luna_dummy.push_back(inDummy());
    }

    vector<DummyState> miena_list, luna_list;
    for (int i = 0; i < n; i++) {
        int miena_cooldown = (i == miena.p) ? miena.cooldown : -1;
        int luna_cooldown = (i == luna.p) ? luna.cooldown : -1;

        miena_list.push_back({
            &miena_dummy[i], miena_dummy[i].hp, 0, false, true, miena_cooldown, miena_dummy[i].atk, miena_dummy[i].def
        });

        luna_list.push_back({
            &luna_dummy[i], luna_dummy[i].hp, 0, false, true, luna_cooldown, luna_dummy[i].atk, luna_dummy[i].def
        });
    }

    int turn = 1;
    int miena_i = 0, luna_i = 0;
    int miena_cd = 0, luna_cd = 0;
    bool is_miena = false;

    while (true) {
        Battle context = getBattle(turn, miena_list, luna_list, miena, luna, miena_i, luna_i, miena_cd, luna_cd);

        DummyState* attacker = context.attacker;
        DummyState* defender = context.defender;
        PowerUp* attacker_powerup = context.att_powerup;
        PowerUp* defender_powerup = context.def_powerup;
        int* attacker_i = context.attacker_i;
        int* defender_i = context.defender_i;

        int defender_prev_hp = defender->cur_hp;
        int attacker_prev_power = attacker->powerup_turns_left;
        int attacker_prev_energy = attacker->energy;

        attacker->curr_atk = attacker->base->atk;
        defender->curr_def = defender->base->def;

        if(*attacker_i == (int)attacker_powerup->p && attacker->powerup_turns_left > 0) {
            attacker->curr_atk *= attacker_powerup->atk;
            attacker->powerup_turns_left--;
            // cout << "------------------------------------------------------ " 
            //   << attacker->base->name << " Use PowerUP " << endl;
        }

        // cout << attacker->base->name << attacker_powerup->p << endl;

        if(*defender_i == (int)defender_powerup->p && defender->powerup_turns_left > 0) {
            defender->curr_def *= defender_powerup->def;
        }

        if(attacker->energy == attacker->base->ener) {
            attacker->curr_atk *= 2;
            attacker->energy = -1;
            // cout << "------------------------------------------------------ " 
            //   << attacker->base->name << " Use Energy " << endl;
        }

        // cal dmg
        int dmg = pow(attacker->curr_atk, 2) / defender->curr_def;
        defender->cur_hp -= dmg;

        if(attacker->energy < attacker->base->ener) {
            attacker->energy++;
        }
        
        if (defender->cur_hp <= 0) {
            if (context.is_miena_turn)  luna_i++;
            else                        miena_i++;
            defender->energy = 0;  // reset energy
        }

        // hell log
        // cout << "=== Turn " << turn << " ===" << endl;
        // cout << attacker->base->name << " HP: " << attacker->cur_hp << endl;
        // cout << attacker->base->name << " ATK: " << attacker->curr_atk << " DEF: " << attacker->curr_def 
        //   << " Energy: " << attacker_prev_energy << "/" << attacker->base->ener<< " -> " << attacker->energy << "/" << attacker->base->ener
        //   << " PowTurn: " << attacker_prev_power << " -> " << attacker->powerup_turns_left << endl;
        // cout << defender->base->name << " HP: " << defender_prev_hp << " -> " << defender->cur_hp << " (-" << dmg << ")" << endl;
        // cout << defender->base->name << " ATK: " << defender->curr_atk << " DEF: " << defender->curr_def
        //   << " Ener: " << defender->energy << "/" << defender->base->ener
        //   << " PowTurn: " << defender->powerup_turns_left << endl;
        // if(defender->cur_hp <= 0) cout << "------------------------------------------------------ Dummy " 
        //                             << defender->base->name << " Eliminate " << endl;

        if (miena_i >= n) {
            is_miena = false;
            break;
        }
        if (luna_i >= n) {
            is_miena = true;
            break;
        } 

        turn++;
    }

    // cout << "=============================================" << endl;
    if (is_miena)
        cout << "Miena is victorious with " << miena_dummy.size() - miena_i << " character" << plural(miena_dummy.size() - miena_i) << " left.\n";
    else
        cout << "Luna is victorious with " << luna_dummy.size() - luna_i << " character" << plural(luna_dummy.size() - luna_i) << " left.\n";
    cout << "The battle took " << turn << " turn" << plural(turn) << ".";

    return 0;
}


/*
1
0 1.25 1.10 5
Gale 2000 50 30 3
0 2 0.6 3
Gwynn 2000 40 40 4

Miena is victorious with 1 character left.
The battle took 31 turns.

2
0 1.25 1.00 3
York 500 50 30 3
Pers 600 40 40 4
0 1.75 0.75 3
Anya 900 40 60 4
Sylph 750 50 30 3

Luna is victorious with 2 characters left.
The battle took 26 turns.

1
0 2.0 0.1 1
Hidebehind 200 100 20 2
0 1.25 1 3
Golem 450 45 50 3

Miena is victorious with 1 character left.
The battle took 1 turn.
*/