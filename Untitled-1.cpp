#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <future>
#include <map>
#include <algorithm>
#include <omp.h>

using namespace std;

const int SIZE = 10;
char board[SIZE][SIZE];
mutex mtx;
int no_capture_moves = 0;

void initialize_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 4) board[i][j] = 'B';
                else if (i > 5) board[i][j] = 'W';
                else board[i][j] = '.';
            } else {
                board[i][j] = '.';
            }
        }
    }
}

void print_board() {
    cout << "    A B C D E F G H I J" << endl;
    cout << "   ---------------------" << endl;
    
    for (int i = 0; i < SIZE; i++) {
        cout << " " << (SIZE - i) << " |";
        
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        
        cout << "| " << (SIZE - i) << endl;
    }
    
    cout << "   ---------------------" << endl;
    cout << "    A B C D E F G H I J" << endl;
}

bool is_valid_move(const string& move) {
    if (move.length() != 5 || move[2] != ' ') return false;
    char col1 = move[0], col2 = move[3];
    int row1 = move[1] - '0', row2 = move[4] - '0';
    if (col1 < 'A' || col1 > 'J' || col2 < 'A' || col2 > 'J') return false;
    if (row1 < 1 || row1 > 10 || row2 < 1 || row2 > 10) return false;
    return true;
}

vector<string> generate_moves(char player, bool capture_only) {
    vector<string> moves;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == player || board[i][j] == (player == 'W' ? 'X' : 'Y')) {
                for (int di = -2; di <= 2; di += 4) {
                    for (int dj = -2; dj <= 2; dj += 4) {
                        int ni = i + di, nj = j + dj;
                        int mi = i + di / 2, mj = j + dj / 2;
                        if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE &&
                            board[mi][mj] != '.' && board[mi][mj] != player && board[ni][nj] == '.') {
                            moves.push_back(string(1, 'A' + j) + to_string(SIZE - i) + " " + string(1, 'A' + nj) + to_string(SIZE - ni));
                        }
                    }
                }
            }
        }
    }
    if (!capture_only && moves.empty()) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == player || board[i][j] == (player == 'W' ? 'X' : 'Y')) {
                    for (int di = -1; di <= 1; di += 2) {
                        for (int dj = -1; dj <= 1; dj += 2) {
                            int ni = i + di, nj = j + dj;
                            if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE && board[ni][nj] == '.') {
                                moves.push_back(string(1, 'A' + j) + to_string(SIZE - i) + " " + string(1, 'A' + nj) + to_string(SIZE - ni));
                            }
                        }
                    }
                }
            }
        }
    }
    return moves;
}

void make_move(string move) {
    int x1 = SIZE - (move[1] - '0');
    int y1 = move[0] - 'A';
    int x2 = SIZE - (move[4] - '0');
    int y2 = move[3] - 'A';
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = '.';
    if (abs(x2 - x1) == 2) {
        int capX = (x1 + x2) / 2;
        int capY = (y1 + y2) / 2;
        board[capX][capY] = '.';
        no_capture_moves = 0;
    } else {
        no_capture_moves++;
    }
    if (x2 == 0 && board[x2][y2] == 'W') board[x2][y2] = 'X';
    if (x2 == SIZE-1 && board[x2][y2] == 'B') board[x2][y2] = 'Y';
}

string best_move(char player) {
    vector<string> moves = generate_moves(player, true);
    if (moves.empty()) moves = generate_moves(player, false);
    if (moves.empty()) return "";
    return moves[0];
}

int main() {
    initialize_board();
    print_board();
    string player;
    cout << "Выберите цвет (W/B): ";
    cin >> player;
    bool player_white = (player == "W");
    while (true) {
        if (no_capture_moves >= 15) {
            cout << "Ничья!" << endl;
            break;
        }
        string move;
        if (player_white) {
            cout << "Ваш ход: ";
            cin.ignore();
            getline(cin, move);
            if (!is_valid_move(move)) {
                cout << "Неверный ввод. Попробуйте снова." << endl;
                continue;
            }
            make_move(move);
        }
        print_board();
        string ai_move = best_move(player_white ? 'B' : 'W');
        if (ai_move.empty()) {
            cout << "Вы победили!" << endl;
            break;
        }
        cout << "Ход компьютера: " << ai_move << endl;
        make_move(ai_move);
        print_board();
    }
    return 0;
}
