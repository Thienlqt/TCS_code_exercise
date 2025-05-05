#include <iostream>
#include <string>
using namespace std;

// Function to check if input string s is accepted by the DFA
bool validS(int q0, string s, int arFinalState[], int sizeF, int **arTrans, char arEdgeVal[], int sizeE) {
    int q = q0;  // Start from initial state

    for (char ch : s) {
        int j;
        for (j = 0; j < sizeE; j++) {
            if (arEdgeVal[j] == ch) break;
        }

        if (j == sizeE) return false;  // Invalid input character
        q = arTrans[q][j];  // Transition to next state
    }

    // Check if final state is accepting
    for (int i = 0; i < sizeF; i++) {
        if (q == arFinalState[i]) return true;
    }

    return false;
}

int main() {
    int n, m;  // n = number of states (rows), m = number of input symbols (columns)
    cout << "Enter number of states and input symbols: ";
    cin >> n >> m;

    // Allocate memory for transition table
    int** arTrans = new int*[n];
    for (int i = 0; i < n; i++) {
        arTrans[i] = new int[m];
    }

    // Input transition table
    cout << "Enter the transition table:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "arTrans[" << i << "][" << j << "] = ";
            cin >> arTrans[i][j];
        }
    }

    // Input edge (alphabet) values
    char* arEdgeVal = new char [m];
    cout << "Enter " << m << " input symbols (as int or ASCII of char): ";
    for (int i = 0; i < m; i++) {
        cin >> arEdgeVal[i];
    }

    // Input final (accepting) states
    int sizeF;
    cout << "Enter number of accepting states: ";
    cin >> sizeF;

    int* arFinalState = new int[sizeF];
    cout << "Enter the accepting state numbers: ";
    for (int i = 0; i < sizeF; i++) {
        cin >> arFinalState[i];
    }

    // Input initial state
    int q0;
    cout << "Enter initial state: ";
    cin >> q0;

    // Input the string to check
    string s;
    cout << "Enter input string: ";
    cin >> s;

    // Check if string is accepted
    bool result = validS(q0, s, arFinalState, sizeF, arTrans, arEdgeVal, m);

    if (result)
        cout << "The string is accepted by the DFA.\n";
    else
        cout << "The string is NOT accepted by the DFA.\n";

    // Free memory
    for (int i = 0; i < n; i++) {
        delete[] arTrans[i];
    }
    delete[] arTrans;
    delete[] arEdgeVal;
    delete[] arFinalState;

    return 0;
}
