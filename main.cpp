#include <iostream>
#include <string>
#include "SimpleCalc.cpp"

using namespace std;

int main() {
    credit();
    string formula;
    while (1) {
        formula = "";
        cout << ":  ";
        getline(cin, formula);
        if (toUpperCase(formula).compare("HELP") == 0)
            help();
        else if (toUpperCase(formula).compare("EXIT") == 0)
            break;
        else
            continuousCalculator<float> (formula);
        cout << "\n";
    }
    // stack<float>* s = new stack<float>;
    // s->push(9);
    // s->push(8);
    // float r = s->pop();
    // r = s->pop();
    // s -> traverse();
    // cout << r << endl;
    return 0;
}