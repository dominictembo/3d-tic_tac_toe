#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// The 3D game board
char board[3][3][3];

// Function to draw the 3D game board
void draw_board() {
    for (int i = 0; i < 3; i++) {
        printf("Layer %d:\n", i + 1);
        for (int j = 0; j < 3; j++) {
            printf(" %c | %c | %c\n", board[i][j][0], board[i][j][1], board[i][j][2]);
            printf("---+---+---\n");
        }
        printf("\n");
    }
}

// Function to handle player move
void player_move(char player) {
    int layer, row, col;
    printf("Player %c, enter your move (layer, row, and column): ", player);
    scanf("%d %d %d", &layer, &row, &col);
    layer--; row--; col--; // adjust for 0-based indexing
    if (layer < 0 || layer > 2 || row < 0 || row > 2 || col < 0 || col > 2) {
        printf("Invalid move, try again.\n");
        player_move(player);
    } else if (board[layer][row][col] != ' ') {
        printf("Cell already occupied, try again.\n");
        player_move(player);
    } else {
        board[layer][row][col] = player;
    }
}

// Function to handle computer move
void computer_move(char player) {
    int layer, row, col;
    srand(time(NULL)); // seed random number generator
    do {
        layer = rand() % 3;
        row = rand() % 3;
        col = rand() % 3;
    } while (board[layer][row][col] != ' ');
    board[layer][row][col] = player;
    printf("Computer places %c in layer %d, row %d, column %d\n", player, layer + 1, row + 1, col + 1);
}

// Function to check for win
int check_win(char player) {
    // Check layers
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j][0] == player && board[i][j][1] == player && board[i][j][2] == player) {
                return 1;
            }
            if (board[i][0][j] == player && board[i][1][j] == player && board[i][2][j] == player) {
                return 1;
            }
            if (board[i][0][0] == player && board[i][1][1] == player && board[i][2][2] == player) {
                return 1;
            }
            if (board[i][0][2] == player && board[i][1][1] == player && board[i][2][0] == player) {
                return 1;
            }
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[0][i][j] == player && board[1][i][j] == player && board[2][i][j] == player) {
                return 1;
            }
        }
    }
    // Check rows
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[j][0][i] == player && board[j][1][i] == player && board[j][2][i] == player) {
                return 1;
            }
        }
    }
    // Check diagonals
    if ((board[0][0][0] == player && board[1][1][1] == player && board[2][2][2] == player) ||
        (board[0][0][2] == player && board[1][1][1] == player && board[2][2][0] == player) ||
        (board[0][2][0] == player && board[1][1][1] == player && board[2][0][2] == player) ||
        (board[0][2][2] == player && board[1][1][1] == player && board[2][0][0] == player)) {
        return 1 ;
    }
    return 0;
}

int main() {
    int game_mode;
    printf("Welcome to 3D Tic Tac Toe!\n");
    printf("Created by 'the codefather'\n");
    printf("Enter 1 for Player vs Player, 2 for Player vs Computer: ");
    scanf("%d", &game_mode);

    // Initialize the 3D game board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                board[i][j][k] = ' ';
            }
        }
    }

    char player = 'X';
    int game_over = 0;

    while (!game_over) {
        draw_board();
        if (game_mode == 1) {
            player_move(player);
        } else {
            if (player == 'X') {
                player_move(player);
            } else {
                computer_move(player);
            }
        }
        if (check_win(player)) {
            draw_board();
            printf("Player %c wins!\n", player);
            game_over = 1;
        } else {
            player = (player == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}
