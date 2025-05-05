# DFA String Checker (C++)

This is a simple C++ program that checks if a string is accepted by a **DFA (Deterministic Finite Automaton)**.

You give it a DFA (states, transitions, symbols, etc.) and a string, and it tells you whether that string is accepted or not.

---

## How it works

1. You enter:
   - Number of states and input symbols
   - The transition table (what state you go to on a certain input)
   - The input symbols (like `0` and `1`)
   - Accepting (final) states
   - The starting state
   - A string to check

## Important Notes

- Input for "Enter 2 input symbols:" needs to be 48, 49 (ASCII number) if you want to input 0, 1.

2. It runs the DFA step-by-step on the string.

3. It tells you if the string is **accepted** or **not accepted**.

---

## Example

Here’s an example input that checks if a string ends in `01`:

Enter number of states and input symbols:
3 2

Enter the transition table:
arTrans[0][0] = 1
arTrans[0][1] = 0
arTrans[1][0] = 1
arTrans[1][1] = 2
arTrans[2][0] = 1
arTrans[2][1] = 0

Enter 2 input symbols:
48 49

Enter number of accepting states:
1

Enter the accepting state numbers:
2

Enter initial state:
0

Enter input string:
1101

Output:
The string is accepted by the DFA.

