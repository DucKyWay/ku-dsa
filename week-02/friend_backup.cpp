#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct dummy {
    string name;
    int hp;
    int atk;        int def;
    int energy;
} Dummy;

typedef struct dummystate {
    Dummy* base; 
    int cur_hp;     int curr_ener;
    int powerup_turns_left;
    int curr_atk;   int curr_def;
} DummyState;

typedef struct powerup {
    int p_index;
    float atk;      float def;
    int cooldown;
} PowerUp;

typedef struct battlecontext {
    DummyState* attacker;       DummyState* defender;
    PowerUp* att_powerup;       PowerUp* def_powerup;
    int* attacker_i;            int* defender_i;
    bool is_miena_turn;
} Battle;

PowerUp inPower() {
    PowerUp x;
    cin >> x.p_index >> x.atk >> x.def >> x.cooldown;
    return x;
}
Dummy inDummy() {
    Dummy x;
    cin >> x.name >> x.hp >> x.atk >> x.def >> x.energy;
    return x;
}

Battle getBattle(
    int turn,
    vector<DummyState>& miena_list, vector<DummyState>& luna_list,
    PowerUp& miena, PowerUp& luna,
    int& miena_i, int& luna_i
) {
    bool is_miena_turn = (turn % 2 == 1);

    DummyState* attacker = is_miena_turn ? &miena_list[miena_i] : &luna_list[luna_i];
    DummyState* defender = is_miena_turn ? &luna_list[luna_i] : &miena_list[miena_i];
    PowerUp* att_powerup = is_miena_turn ? &miena : &luna;
    PowerUp* def_powerup = is_miena_turn ? &luna : &miena;
    int* attacker_i = is_miena_turn ? &miena_i : &luna_i;
    int* defender_i = is_miena_turn ? &luna_i : &miena_i;

    Battle result;
    result.attacker = attacker;         result.defender = defender;
    result.att_powerup = att_powerup;   result.def_powerup = def_powerup;
    result.attacker_i = attacker_i;     result.defender_i = defender_i;
    result.is_miena_turn = is_miena_turn;
    return result;
}

string plural(int n) {
    if(n > 1) return "s";
    else return "";
}

int main() {
    int n;
    cin >> n;

    PowerUp miena, luna;
    vector<Dummy> miena_dummy, luna_dummy;
    miena_dummy.reserve(n);
    luna_dummy.reserve(n);

    miena = inPower();
    for (int i = 0; i < n; i++) miena_dummy.push_back(inDummy());
    luna = inPower();
    for (int i = 0; i < n; i++) luna_dummy.push_back(inDummy());

    vector<DummyState> miena_list, luna_list;
    miena_list.reserve(n);
    luna_list.reserve(n);
    for (int i = 0; i < n; i++) {
        int miena_cooldown = (i == miena.p_index) ? miena.cooldown : -1;
        int luna_cooldown = (i == luna.p_index) ? luna.cooldown : -1;

        miena_list.push_back({&miena_dummy[i], miena_dummy[i].hp, 0, miena_cooldown, miena_dummy[i].atk, miena_dummy[i].def});

        luna_list.push_back({&luna_dummy[i], luna_dummy[i].hp, 0, luna_cooldown, luna_dummy[i].atk, luna_dummy[i].def});
    }

    int turn = 1;
    int miena_i = 0, luna_i = 0;
    bool is_miena = false;

    while (true) {
        Battle context = getBattle(turn, miena_list, luna_list, miena, luna, miena_i, luna_i);

        DummyState* attacker = context.attacker;
        DummyState* defender = context.defender;
        PowerUp* attacker_powerup = context.att_powerup;
        PowerUp* defender_powerup = context.def_powerup;
        int* attacker_i = context.attacker_i;
        int* defender_i = context.defender_i;

        // for log
        // int defender_prev_hp = defender->cur_hp;
        // int attacker_prev_power = attacker->powerup_turns_left;
        // int attacker_prev_curr_ener = attacker->curr_ener;

        attacker->curr_atk = attacker->base->atk;
        defender->curr_def = defender->base->def;

        if(*attacker_i == (int)attacker_powerup->p_index && attacker->powerup_turns_left > 0) {
            attacker->curr_atk *= attacker_powerup->atk;
            attacker->powerup_turns_left--;
            // cout << "------------------------------------------------------ " << attacker->base->name << " Use PowerUP " << endl;
        }

        if(*defender_i == (int)defender_powerup->p_index && defender->powerup_turns_left > 0) {
            defender->curr_def *= defender_powerup->def;
        }

        if(attacker->curr_ener == attacker->base->energy) {
            attacker->curr_atk *= 2;
            attacker->curr_ener = -1;
            // cout << "------------------------------------------------------ " << attacker->base->name << " Use Energy " << endl;
        }

        // cal dmg
        if(defender->curr_def < 1) defender->curr_def = 1;
        int dmg = (attacker->curr_atk * attacker->curr_atk) / defender->curr_def;
        defender->cur_hp -= dmg;

        if(attacker->curr_ener < attacker->base->energy) {
            attacker->curr_ener++;
        }
        
        if (defender->cur_hp <= 0) {
            if (context.is_miena_turn)  luna_i++;
            else                        miena_i++;
            defender->curr_ener = 0;  // reset energy
        }

        // hell log
        // cout << "=== Turn " << turn << " ===" << endl;
        // cout << attacker->base->name << " HP: " << attacker->cur_hp << endl;
        // cout << attacker->base->name << " ATK: " << attacker->curr_atk << " DEF: " << attacker->curr_def 
        //   << " Energy: " << attacker_prev_curr_ener << "/" << attacker->base->energy<< " -> " << attacker->curr_ener << "/" << attacker->base->energygy
        //   << " PowTurn: " << attacker_prev_power << " -> " << attacker->powerup_turns_left << endl;
        // cout << defender->base->name << " HP: " << defender_prev_hp << " -> " << defender->cur_hp << " (-" << dmg << ")" << endl;
        // cout << defender->base->name << " ATK: " << defender->curr_atk << " DEF: " << defender->curr_def
        //   << " Ener: " << defender->curr_ener << "/" << defender->base->energy
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