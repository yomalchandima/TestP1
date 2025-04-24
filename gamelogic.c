// game_logic.c

#include "types.h"

void initializePlayers(Player players[]) {
    const char* colours[NUM_PLAYERS] = {"Red", "Blue", "Green", "Yellow"};
    const char colourInitials[NUM_PLAYERS] = {'R', 'B', 'G', 'Y'};
    
    for (int i = 0; i < NUM_PLAYERS; i++) {
        strcpy(players[i].colour, colours[i]);
        
        for (int j = 0; j < NUM_PIECES; j++) {
            sprintf(players[i].pieces[j], "%c%d", colourInitials[i], j + 1);
            players[i].piecePositions[j] = -1; // All pieces start at base
        }
        players[i].piecesHome = 0;
        players[i].finished = 0;
        printf("The %s player has four (04) pieces named %c1, %c2, %c3, and %c4.\n", 
               players[i].colour, colourInitials[i], colourInitials[i], colourInitials[i], colourInitials[i]);
    }
}

void rollDice(Player *player) {
    player->roll = (rand() % 6) + 1; // Dice Roll (1-6)
    printf("[%s] player rolled [%d].\n", player->colour, player->roll);
}

int findFirstPlayer(Player players[]) {
    int maxRoll = players[0].roll;
    int firstPlayerIndex = 0;
    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (players[i].roll > maxRoll) {
            maxRoll = players[i].roll;
            firstPlayerIndex = i;
        }
    }
    return firstPlayerIndex;
}

int isCapturedByOpponent(Player players[], int position, const char *currentColor) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (strcmp(players[i].colour, currentColor) != 0) {
            for (int j = 0; j < NUM_PIECES; j++) {
                if (players[i].piecePositions[j] == position) {
                    return i; // Return index of opponent player
                }
            }
        }
    }
    return -1; // No opponent captures this position
}

void movePiece(Player players[], int playerIndex, int pieceIndex) {
    Player *player = &players[playerIndex];
    int newPosition = player->piecePositions[pieceIndex] + player->roll;

    if (newPosition >= BOARD_SIZE) {
        newPosition -= BOARD_SIZE;
    }

    if (player->piecePositions[pieceIndex] >= HOME_STRAIGHT_START) {
        if (newPosition == BOARD_SIZE - 1) {
            player->piecesHome++;
            player->piecePositions[pieceIndex] = -2; // Piece has reached home and is no longer on the board
            printf("Piece %s has reached home!\n", player->pieces[pieceIndex]);
        } else if (newPosition < BOARD_SIZE - 1) {
            player->piecePositions[pieceIndex] = newPosition;
            printf("Piece %s moved to position %d\n", player->pieces[pieceIndex], newPosition);
        } else {
            printf("Cannot move piece %s. Roll ignored.\n", player->pieces[pieceIndex]);
        }
    } else {
        int opponentIndex = isCapturedByOpponent(players, newPosition, player->colour);
        if (opponentIndex != -1) {
            printf("Piece %s captures piece at position %d\n", player->pieces[pieceIndex], newPosition);
            for (int j = 0; j < NUM_PIECES; j++) {
                if (players[opponentIndex].piecePositions[j] == newPosition) {
                    players[opponentIndex].piecePositions[j] = -1;
                    printf("Piece %s has been captured and returned to base.\n", players[opponentIndex].pieces[j]);
                    break;
                }
            }
        }
        player->piecePositions[pieceIndex] = newPosition;
        printf("Piece %s moved to position %d\n", player->pieces[pieceIndex], newPosition);
    }
}

int selectPiece(Player *player) {
    for (int i = 0; i < NUM_PIECES; i++) {
        if (player->piecePositions[i] >= 0 && player->piecePositions[i] < BOARD_SIZE) {
            return i;
        }
    }
    return -1;
}

int getPieceFromBase(Player *player) {
    for (int i = 0; i < NUM_PIECES; i++) {
        if (player->piecePositions[i] == -1) {
            return i;
        }
    }
    return -1;
}

void showPlayerStatus(Player players[]) {
    printf("\n===== Player Status =====\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        int onBoard = 0, atBase = 0, atHome = 0;

        for (int j = 0; j < NUM_PIECES; j++) {
            if (players[i].piecePositions[j] == -1) {
                atBase++;
            } else if (players[i].piecePositions[j] == -2) {
                atHome++;
            } else {
                onBoard++;
            }
        }

        printf("[%s] player now has %d/4 pieces on the board, %d/4 pieces at base, and %d/4 pieces at home.\n", 
                players[i].colour, onBoard, atBase, atHome);
        printf("============================\n");
        printf("Location of pieces [%s]:\n", players[i].colour);
        printf("============================\n");
        
        for (int j = 0; j < NUM_PIECES; j++) {
            if (players[i].piecePositions[j] == -1) {
                printf("Piece %s —> Base\n", players[i].pieces[j]);
            } else if (players[i].piecePositions[j] == -2) {
                printf("Piece %s —> Home\n", players[i].pieces[j]);
            } else if (players[i].piecePositions[j] >= HOME_STRAIGHT_START) {
                int cellNumber = players[i].piecePositions[j] - HOME_STRAIGHT_START;
                printf("Piece %s —> %s/homepath/%d\n", players[i].pieces[j], players[i].colour, cellNumber);
            } else {
                printf("Piece %s —> L%d\n", players[i].pieces[j], players[i].piecePositions[j]);
            } 
        }
        printf("\n");
    }
}

void playRound(Player players[], int firstPlayerIndex) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        int currentPlayerIndex = (firstPlayerIndex + i) % NUM_PLAYERS;
        Player *currentPlayer = &players[currentPlayerIndex];
        if (currentPlayer->finished) {
            continue; // Skip player if they have finished the game
        }
        
        int rollsInRow = 0;

        do {
            rollDice(currentPlayer);
            rollsInRow++;

            if (currentPlayer->roll == 6) {
                if (rollsInRow == 3) {
                    printf("Player %s rolled a six for the third consecutive time. Roll ignored.\n", currentPlayer->colour);
                    break;
                }

                int pieceToMove = getPieceFromBase(currentPlayer);
                if (pieceToMove != -1) {
                    currentPlayer->piecePositions[pieceToMove] = 0; // Move to 'X'
                    printf("Player %s moves piece %s from base to 'X'.\n", currentPlayer->colour, currentPlayer->pieces[pieceToMove]);
                } else {
                    pieceToMove = selectPiece(currentPlayer);
                    if (pieceToMove != -1) {
                        movePiece(players, currentPlayerIndex, pieceToMove);
                    } else {
                        printf("Player %s has no pieces to move. Roll ignored.\n", currentPlayer->colour);
                        break;
                    }
                }
            } else {
                int pieceToMove = selectPiece(currentPlayer);
                if (pieceToMove != -1) {
                    movePiece(players, currentPlayerIndex, pieceToMove);
                } else {
                    printf("Player %s has no available moves. Roll ignored.\n", currentPlayer->colour);
                    break;
                }
                break;
            }
        } while (currentPlayer->roll == 6);

        if (currentPlayer->piecesHome == NUM_PIECES) {
            currentPlayer->finished = 1;
        }

        showPlayerStatus(players);
    }
}

