// types.h

#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_PLAYERS 4
#define NUM_PIECES 4
#define BOARD_SIZE 52
#define HOME_STRAIGHT_START 47

typedef struct {
    char colour[10];  // Colour name (e.g., "Red", "Blue")
    char pieces[NUM_PIECES][3]; // Array to store piece names (e.g., "R1", "G2")
    int piecePositions[NUM_PIECES]; // Piece positions on the board (-1 means at base, -2 means at home)
    int piecesHome;
    int roll;
    int finished;  // 0: Still playing, 1: Finished all pieces
} Player;

// Function declarations
void initializePlayers(Player players[]);
void rollDice(Player *player);
int findFirstPlayer(Player players[]);
int isCapturedByOpponent(Player players[], int position, const char *currentColor);
void movePiece(Player players[], int playerIndex, int pieceIndex);
int selectPiece(Player *player);
int getPieceFromBase(Player *player);
void showPlayerStatus(Player players[]);
void playRound(Player players[], int firstPlayerIndex);

#endif // TYPES_H

