#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <cstdio>
using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
int precedence(char c) { // สะกดไง
    if(c == '*' || c == '/') return 2;
    if(c == '+' || c == '-') return 1;
    return 0;
}

bool doOperator(stack<double> &val, stack<char> &op) {
    if (op.empty() || val.size() < 2)
        return false;

    double b = val.top(); 
    val.pop();

    double a = val.top();
    val.pop();

    char o = op.top();
    op.pop();

    if (o == '+')
        val.push(a + b);
    else if (o == '-')
        val.push(a - b);
    else if (o == '*')
        val.push(a * b);
    else if (o == '/') {
        if (fabs(b) < 1e-12)
            return false;
        val.push(a / b);
    }
    else {
        return false;
    }
    return true;
}

int main() {

    string str;
    if (!getline(cin, str))
        return 0;

    stack<double> vals;
    stack<char> ops;
    bool expectValue = true; // true => num, "(" , +/- before num

    for (size_t i = 0; i < str.size();) {
        char c = str[i];

        if (c == ' ') {
            ++i;
            continue;
        }

        // not on this
        if (!(isdigit((char)c) || c == '.' || isOperator(c) || c == '(' || c == ')')) {
            cout << "ERROR : Invalid character" << endl;
            return 0;
        }

        // num
        if (isdigit((char)c) || c == '.' ||
            ((c == '+' || c == '-') && expectValue && i + 1 < str.size() &&
             (isdigit((char)str[i + 1]) || str[i + 1] == '.'))) {

            size_t j = i;
            if ((str[j] == '+' || str[j] == '-') && expectValue)
                j++; // op before num
            bool seenDigit = false, seenDot = false;
            while (j < str.size()) {
                char d = str[j];
                if (isdigit((char)d)) {
                    seenDigit = true;
                    j++;
                }
                else if (d == '.') {
                    if (seenDot)
                        break;
                    seenDot = true;
                    j++;
                } else {
                    break;
                }
            }
            if (!seenDigit) {
                cout << "ERROR : Invalid expression" << endl;
                return 0;
            }
            try {
                double v = stod(str.substr(i, j - i));
                vals.push(v);
            } catch (...) {
                cout << "ERROR : Invalid expression" << endl;
                return 0;
            }
            i = j;
            expectValue = false;
            continue;
        }

        if (c == '(') {
            ops.push(c);
            ++i;
            expectValue = true;
            continue;
        }
        if (c == ')') {
            bool matched = false;
            while (!ops.empty()) {
                if (ops.top() == '(') {
                    matched = true;
                    ops.pop();
                    break;
                }
                if (!doOperator(vals, ops)) {
                    cout << "ERROR : Invalid expression" << endl;
                    return 0;
                }
            }
            if (!matched) {
                cout << "ERROR : Unbalanced parenthesis" << endl;
                return 0;
            }
            ++i;
            expectValue = false;
            continue;
        }

        // op
        if (isOperator(c)) {
            if (expectValue) {
                cout << "ERROR : Invalid expression" << endl;
                return 0;
            }
            while (!ops.empty() && isOperator(ops.top()) && 
                    precedence(ops.top()) >= precedence(c)) {
                if (!doOperator(vals, ops)) {
                    cout << "ERROR : Invalid expression" << endl;
                    return 0;
                }
            }
            ops.push(c);
            ++i;
            expectValue = true;
            continue;
        }
    }

    // close
    while (!ops.empty()) {
        
        if (ops.top() == '(') {
            cout << "ERROR : Unbalanced parenthesis" << endl;
            return 0;
        }
        if (!doOperator(vals, ops)) {
            cout << "ERROR : Invalid expression" << endl;
            return 0;
        }
    }

    if (vals.size() != 1) {
        cout << "ERROR : Invalid expression" << endl;
        return 0;
    }

    printf("Final Result : %.2f\n", vals.top());
    return 0;
}

// 1+2+(-3.5*4)
// 9+(1.5+4)-2+1+((((2+1.4)+3)+1)
// 2+3$4
