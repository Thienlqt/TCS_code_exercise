#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

using NFA = unordered_map<string, unordered_map<string, unordered_set<string>>>;


unordered_set<string> lambdaClosure(const unordered_set<string>& states, const NFA& nfa) {
    unordered_set<string> closure = states;
    vector<string> stack(states.begin(), states.end());

    while (!stack.empty()) {
        string state = stack.back();
        stack.pop_back();
        if (nfa.count(state) && nfa.at(state).count("lambda")) {
            for (const string& nextState : nfa.at(state).at("lambda")) {
                if (closure.find(nextState) == closure.end()) {
                    closure.insert(nextState);
                    stack.push_back(nextState);
                }
            }
        }
    }
    return closure;
}


unordered_set<string> move(const unordered_set<string>& states, const string& symbol, const NFA& nfa) {
    unordered_set<string> result;
    for (const string& state : states) {
        if (nfa.count(state) && nfa.at(state).count(symbol)) {
            result.insert(nfa.at(state).at(symbol).begin(), nfa.at(state).at(symbol).end());
        }
    }
    return result;
}


NFA readNFA() {
    NFA nfa;
    int numStates, numSymbols;

    cout << "Enter the number of states: ";
    cin >> numStates;
    cout << "Enter the number of input symbols: ";
    cin >> numSymbols;
    cin.ignore();

    for (int i = 0; i < numStates; i++) {
        string state;
        cout << "Enter state name: ";
        getline(cin, state);
        nfa[state] = {};

        for (int j = 0; j < numSymbols; j++) {
            string symbol, nextStatesStr;
            cout << "Enter transition symbol from " << state << ": ";
            getline(cin, symbol);
            cout << "Enter list of next states for " << state << " with " << symbol << ": ";
            getline(cin, nextStatesStr);

            unordered_set<string> nextStates;
            stringstream ss(nextStatesStr);
            string nextState;
            while (getline(ss, nextState, ',')) {
                nextStates.insert(nextState);
            }

            if (!nextStates.empty()) {
                nfa[state][symbol] = nextStates;
            }
        }
    }
    return nfa;
}

int main() {
    NFA nfa = readNFA();

    string q, symbol, statesStr;
    unordered_set<string> T;

    cout << "Enter initial state: ";
    cin >> q;
    cin.ignore();
    cout << "Enter a set of states (comma separated): ";
    getline(cin, statesStr);
    cout << "Enter input symbol: ";
    cin >> symbol;

    stringstream ss(statesStr);
    string tempState;
    while (getline(ss, tempState, ',')) {
        T.insert(tempState);
    }

    unordered_set<string> deltaStarQ = lambdaClosure(move(lambdaClosure({ q }, nfa), symbol, nfa), nfa);
    unordered_set<string> deltaStarT = lambdaClosure(move(lambdaClosure(T, nfa), symbol, nfa), nfa);

    cout << "Delta* of q with " << symbol << ": { ";
    for (const string& s : deltaStarQ) cout << s << " ";
    cout << "}" << endl;

    cout << "Delta* of T with " << symbol << ": { ";
    for (const string& s : deltaStarT) cout << s << " ";
    cout << "}" << endl;

    return 0;
}