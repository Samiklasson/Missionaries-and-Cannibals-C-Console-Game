#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function prototypes
void displayState(int leftM, int leftC, int rightM, int rightC, bool boatLeft);
bool isValidMove(int m, int c, bool boatLeft, int leftM, int leftC, int rightM, int rightC);
bool isSideSafe(int M, int C);
bool bothSidesSafe(int leftM, int leftC, int rightM, int rightC);
void performMove(int &leftM, int &leftC, int &rightM, int &rightC, bool &boatLeft, int m, int c);
bool checkWin(int leftM, int leftC, int rightM, int rightC);
bool readMove(int &m, int &c, bool &quit);

int main() {
    // Initial state
    int leftMissionaries = 3, leftCannibals = 3;
    int rightMissionaries = 0, rightCannibals = 0;
    bool boatOnLeft = true;      // boat starts on the left bank
    int moveCount = 0;

    cout << "=======================================\n";
    cout << "  Missionaries and Cannibals Game\n";
    cout << "=======================================\n";
    cout << "Rules:\n";
    cout << " - Move all 6 people to the right bank.\n";
    cout << " - The boat can carry 1 or 2 people.\n";
    cout << " - On either bank, missionaries must never be outnumbered by cannibals.\n";
    cout << " - Enter 'q' at any prompt to quit.\n";
    cout << "=======================================\n\n";

    while (true) {
        displayState(leftMissionaries, leftCannibals, rightMissionaries, rightCannibals, boatOnLeft);

        // Prompt for move
        int m, c;
        bool quit = false;
        cout << "Move from " << (boatOnLeft ? "left" : "right") << " to "
             << (boatOnLeft ? "right" : "left") << " (M C): ";
        if (!readMove(m, c, quit)) {
            if (quit) {
                cout << "Game quit. Thanks for playing!\n";
                break;
            }
            cout << "Invalid input. Please enter two numbers.\n";
            continue;
        }

        // Validate move
        if (!isValidMove(m, c, boatOnLeft, leftMissionaries, leftCannibals,
                         rightMissionaries, rightCannibals)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        // Perform the move (temporary)
        int tempLM = leftMissionaries, tempLC = leftCannibals;
        int tempRM = rightMissionaries, tempRC = rightCannibals;
        bool tempBoat = boatOnLeft;
        performMove(tempLM, tempLC, tempRM, tempRC, tempBoat, m, c);

        // Check safety after move
        if (!bothSidesSafe(tempLM, tempLC, tempRM, tempRC)) {
            cout << "Unsafe move! Undoing.\n";
            continue;   // discard temporary changes
        }

        // Commit the move
        leftMissionaries = tempLM;
        leftCannibals = tempLC;
        rightMissionaries = tempRM;
        rightCannibals = tempRC;
        boatOnLeft = tempBoat;
        moveCount++;

        // Check win
        if (checkWin(leftMissionaries, leftCannibals, rightMissionaries, rightCannibals)) {
            displayState(leftMissionaries, leftCannibals, rightMissionaries, rightCannibals, boatOnLeft);
            cout << "\n🎉 Congratulations! You won the game in " << moveCount << " moves.\n";
            break;
        }
    }

    return 0;
}

// ------------------------------------------------------------
// Displays the current state of both banks and boat location
// ------------------------------------------------------------
void displayState(int leftM, int leftC, int rightM, int rightC, bool boatLeft) {
    cout << "\n--- Current State ---\n";
    cout << "Left bank:  ";
    for (int i = 0; i < leftM; i++) cout << "M ";
    for (int i = 0; i < leftC; i++) cout << "C ";
    cout << (leftM == 0 && leftC == 0 ? "(empty)" : "");
    cout << "\nRight bank: ";
    for (int i = 0; i < rightM; i++) cout << "M ";
    for (int i = 0; i < rightC; i++) cout << "C ";
    cout << (rightM == 0 && rightC == 0 ? "(empty)" : "");
    cout << "\nBoat is on the " << (boatLeft ? "left" : "right") << " bank.\n";
    cout << "----------------------\n";
}

// ------------------------------------------------------------
// Reads a move from the user. Returns true if two integers
// were read; sets 'quit' if user enters 'q'.
// ------------------------------------------------------------
bool readMove(int &m, int &c, bool &quit) {
    string input;
    cin >> input;
    if (input == "q" || input == "Q") {
        quit = true;
        return false;
    }
    // Try to parse second integer
    string rest;
    cin >> rest;
    if (rest == "q" || rest == "Q") {
        quit = true;
        return false;
    }
    // Convert to integers
    try {
        m = stoi(input);
        c = stoi(rest);
    } catch (...) {
        return false;   // conversion failed
    }
    return true;
}

// ------------------------------------------------------------
// Checks if a move is legal (people available, boat capacity)
// ------------------------------------------------------------
bool isValidMove(int m, int c, bool boatLeft, int leftM, int leftC,
                 int rightM, int rightC) {
    if (m < 0 || c < 0) return false;
    if (m + c == 0) return false;
    if (m + c > 2) return false;

    if (boatLeft) {
        if (m > leftM || c > leftC) return false;
    } else {
        if (m > rightM || c > rightC) return false;
    }
    return true;
}

// ------------------------------------------------------------
// Safety check for one bank: missionaries must not be outnumbered
// if there is at least one missionary.
// ------------------------------------------------------------
bool isSideSafe(int M, int C) {
    if (M == 0) return true;
    return M >= C;
}

// ------------------------------------------------------------
// Checks both banks for safety.
// ------------------------------------------------------------
bool bothSidesSafe(int leftM, int leftC, int rightM, int rightC) {
    return isSideSafe(leftM, leftC) && isSideSafe(rightM, rightC);
}

// ------------------------------------------------------------
// Moves people from the bank where the boat is to the other bank.
// ------------------------------------------------------------
void performMove(int &leftM, int &leftC, int &rightM, int &rightC,
                 bool &boatLeft, int m, int c) {
    if (boatLeft) {
        leftM -= m;
        leftC -= c;
        rightM += m;
        rightC += c;
    } else {
        rightM -= m;
        rightC -= c;
        leftM += m;
        leftC += c;
    }
    boatLeft = !boatLeft;   // boat changes side
}

// ------------------------------------------------------------
// Win condition: all people on the right bank.
// ------------------------------------------------------------
bool checkWin(int leftM, int leftC, int rightM, int rightC) {
    return (leftM == 0 && leftC == 0 && rightM == 3 && rightC == 3);
}
