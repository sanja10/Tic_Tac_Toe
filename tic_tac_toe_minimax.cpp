#include <bits/stdc++.h>

using namespace std;

// Length of the board
#define SIDE 3

string PLAYER1, PLAYER2;
char AI = 'X' , notAI = 'O';
void showBoard(char board[][SIDE]) {
    
    printf("\n\n");
    
    printf("\t\t\t %c | %c | %c \n",
           board[0][0],
           board[0][1],
           board[0][2]);
    
    printf("\t\t\t-----------\n");
    
    printf("\t\t\t %c | %c | %c \n",
           board[1][0],
           board[1][1],
           board[1][2]);
    
    printf("\t\t\t-----------\n");
    
    printf("\t\t\t %c | %c | %c \n",
           board[2][0],
           board[2][1],
           board[2][2]);
    
    return;
}

void showInstructions() {
    
    printf("\t\t\t Tic-Tac-Toe\n\n");
    printf("Choose a cell numbered  as below and play\n\n");
    
    printf("\t\t\t [1,1] | [1,2] | [1,3] \n");
    printf("\t\t\t-------------------------\n");
    printf("\t\t\t [2,1] | [2,2] | [2,3] \n");
    printf("\t\t\t-------------------------\n");
    printf("\t\t\t [3,1] | [3,2] | [3,3] \n");
    
    printf("-\t-\t-\t-\t-\t"
           "-\t-\t-\t-\t-\n\n");
    
    return;
}

void initialise(char board[][SIDE], int moves[]) {
    
    // Initiate the random number generator so that the same
    // configuration doesn't arises
    srand(time(NULL));
    
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            board[i][j] = ' ';
    
    for (int i = 0; i < SIDE * SIDE; i++)
        moves[i] = i;
    
    // randomise the moves
    random_shuffle(moves, moves + SIDE * SIDE);
    
    return ;
}

void declareWinner(string whoseTurn) {
    
    if (whoseTurn == PLAYER1)
        cout << PLAYER1 << " has won\n";
    else
        cout << PLAYER2 << " has won\n";
    
    return;
    
}

// Function that returns true if any of the row is crossed 
// with the same player's move
bool rowCrossed(char board[][SIDE], char &c) {
    
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != ' ') {
            c = board[i][0];
            return true;
        }
    }
    
    return false;
    
}

// Function that returns true if any of the column is  
// crossed with the same player's move
bool columnCrossed(char board[][SIDE], char &c) {
    
    for (int i = 0; i < SIDE; i++)
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != ' ') {
            c = board[0][i];
            return true;
        }
    
    return false;
    
}


// Function that returns true if any of the diagonal is  
// crossed with the same player's move
bool diagonalCrossed(char board[][SIDE], char &c) {
    
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != ' ') {
        c = board[0][0];
        return true;
    }
    
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != ' ') {
        c = board[0][2];
        return true;
    }
    
    return false;
    
}


bool gameOver(char board[][SIDE]) {
    char c = ' ';
    return (rowCrossed(board, c) ||
            columnCrossed(board, c) ||
            diagonalCrossed(board, c));
    
}

int evaluate(char board[][SIDE]) {
    char c = ' ';
    if (rowCrossed(board, c)) {
        if (c == AI)
            return +10;
        else
            return -10;
    }
    
    if (columnCrossed(board, c)) {
        if (c == AI)
            return +10;
        else
            return -10;
    }
    
    if (diagonalCrossed(board, c)) {
        if (c == AI)
            return +10;
        else
            return -10;
    }
    
    return 0;
}

bool isMoveLeft(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int minimax(char board[][SIDE], int depth, bool isMax, int alpha, int beta) {
    
    int score = evaluate(board);
    if (score == 10 || score == -10)
        return score;
    
    if (isMoveLeft(board) == false)
        return 0;
    
    if (isMax) {
        
        int bestScore = -1000;
        
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    bestScore = max(bestScore, minimax(board, depth+1, !isMax, alpha, beta));
                    board[i][j] = ' ';
                    alpha = max(bestScore, alpha);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        
        return bestScore;
        
    } else {
        int bestScore = 1000;
        
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = notAI;
                    bestScore = min(bestScore, minimax(board, depth+1, !isMax, alpha, beta));
                    board[i][j] = ' ';
                    beta = min(bestScore, beta);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        
        return bestScore;
    }
    
}

pair<int, int> findBestMove(char board[][SIDE]) {
    
    int bestVal = -1000;
    pair<int,int> bestMove;
    bestMove.first = -1;
    bestMove.second = -1;
    
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false, -1000, 1000);
                board[i][j] = ' ';
                
                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMove.first = i;
                    bestMove.second = j;
                }
            }
        }
    }
    
    return bestMove;
}

void playTicTacToe(string whoseTurn) {
    
    char board[SIDE][SIDE];
    int moves[SIDE * SIDE];
    
    initialise(board, moves);
    
    showInstructions();
    
    int moveIndex = 0, x, y;
    int r, c;
    
    while (gameOver(board) == false &&
           moveIndex != SIDE * SIDE) {
        
        if (whoseTurn == PLAYER1) {
            // Label for player1 wrong choice of row and column
            player1:
                cout << PLAYER1 << " Enter the respective row and colum to insert X :\n";
                cin >> r >> c;
                
                if (r <= 3 && c <= 3) {
                    if (board[r-1][c-1] == ' ')
                        board[r-1][c-1] = notAI;
                    
                    else {
                        cout << "You cannot overlap on already filled position:\n";
                        goto player1;
                    }
                
                }
                
                // Input is not valid
                else {
                    cout << "\nInput is not "
                        << "valid please enter "
                        << "right one\n";
    
                    goto player1;
                }
                
                showBoard(board);
                moveIndex++;
                whoseTurn = PLAYER2;
        }
        else if (whoseTurn == PLAYER2) {
            /*// Label for player2 wrong choice of row and column
            player2:
                cout << PLAYER2 << " Enter the respective row and colum to insert O :\n";
                cin >> r >> c;
                
                if (r <= 3 && c <= 3) {
                    //[r-1][c-1]
                    if (board[r-1][c-1] == ' ')
                        board[r-1][c-1] = notAI;
                    
                    else {
                        cout << "You cannot overlap on already filled position:\n";
                        goto player2;
                    }
                
                }
                
                // Input is not valid
                else {
                    cout << "\nInput is not "
                        << "valid please enter "
                        << "right one\n";
    
                    goto player2;
                }
        */      
                pair<int,int> move = findBestMove(board);
                board[move.first][move.second] = AI;
                showBoard(board);
                moveIndex++;
                whoseTurn = PLAYER1;
        
        }
        
        }
    
    if (gameOver(board) == false &&
        moveIndex == SIDE * SIDE)
        printf("It's a draw\n");
    else {
        if (whoseTurn == PLAYER1)
            whoseTurn = PLAYER2;
        else if (whoseTurn == PLAYER2)
            whoseTurn = PLAYER1;
        
        declareWinner(whoseTurn);
    }
    
    return;
}

int main() {
    
    cout << "Enter name of first Player: ";
    cin >> PLAYER1;
    
    PLAYER2 = "AI";
    
    srand(time(0));
    
    int toss = rand() % 2;
    
    if (toss == 1) {
        cout << "Player " << PLAYER1 << " win the toss" << endl;
        notAI = 'X';
        AI = 'O';
        playTicTacToe(PLAYER1);
    }
    else {
        cout << "Player " << PLAYER2 << " win the toss" << endl;
        AI = 'X';
        notAI = 'O';
        playTicTacToe(PLAYER2);
    }
    
    
    return 0;
}
