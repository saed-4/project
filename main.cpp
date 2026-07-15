#include <iostream>
using namespace std;

// =====================================================================
// ONE simple class: TicTacToe
// ---------------------------------------------------------------------
// This is basically your original code, just wrapped inside a class.
//
// The only OOP idea used here is ENCAPSULATION:
//   - board[][], current_marker, current_player used to be GLOBAL
//     variables that any function could mess with.
//   - Now they are PRIVATE members. Only the class's own functions
//     (called "member functions" or "methods") can touch them.
//   - Everything else (main) just calls playGame() from outside.
//
// That's it. Same logic as before, same function names, just moved
// inside a class. Easy to explain: "I turned my variables + functions
// into one object instead of leaving them floating around globally."
// =====================================================================
class TicTacToe {
private:
    char board[3][3];
    char current_marker;
    int current_player;

    // Function to print the visual layout of the game board
    void drawBoard() {
        cout << "\n";
        cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n";
        cout << "---|---|---\n";
        cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n";
        cout << "---|---|---\n";
        cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n";
        cout << "\n";
    }

    // Function to place a marker on the board based on slot number (1-9)
    bool placeMarker(int slot) {
        int row = (slot - 1) / 3;
        int col = (slot - 1) % 3;

        if (slot >= 1 && slot <= 9 && board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = current_marker;
            return true;
        }
        return false;
    }

    // Function to check all horizontal, vertical, and diagonal win configurations
    int checkWinner() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return current_player;
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return current_player;
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return current_player;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return current_player;

        return 0; // No winner yet
    }

public:
    // Constructor: runs automatically when we create a TicTacToe object.
    // It sets up the board with 1-9, just like your original global
    // initialization did.
    TicTacToe() {
        char start = '1';
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                board[r][c] = start++;
    }

    // Main game logic loop (same as your original playGame())
    void playGame() {
        cout << "Player 1, choose your marker (X or O): ";
        cin >> current_marker;

        while (current_marker != 'X' && current_marker != 'O') {
            cout << "Invalid marker! Please choose 'X' or 'O': ";
            cin >> current_marker;
        }

        current_player = 1;
        int player_won = 0;

        for (int turn = 0; turn < 9; turn++) {
            drawBoard();
            int slot;
            cout << "Player " << current_player << "'s turn (" << current_marker << "). Enter slot (1-9): ";
            cin >> slot;

            while (!placeMarker(slot)) {
                cout << "Invalid move or slot occupied! Try another slot (1-9): ";
                cin >> slot;
            }

            player_won = checkWinner();
            if (player_won != 0) {
                drawBoard();
                cout << "Congratulations! Player " << player_won << " wins!\n";
                return;
            }

            current_player = (current_player == 1) ? 2 : 1;
            current_marker = (current_marker == 'X') ? 'O' : 'X';
        }

        drawBoard();
        cout << "It's a draw/tie game!\n";
    }
};

int main() {
    cout << "=================================\n";
    cout << "   WELCOME TO TIC-TAC-TOE IN C++ \n";
    cout << "=================================\n";

    TicTacToe game;   // creating an "object" of the class
    game.playGame();  // calling its method

    return 0;
}