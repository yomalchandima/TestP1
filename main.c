// main.c

#include "types.h"

int main() {
    srand(time(NULL));

    Player players[NUM_PLAYERS];
    initializePlayers(players);

    for (int i = 0; i < NUM_PLAYERS; i++) {
        rollDice(&players[i]);
    }

    int firstPlayerIndex = findFirstPlayer(players);
    printf("Player %s goes first!\n", players[firstPlayerIndex].colour);

    int winners[NUM_PLAYERS] = {0};
    int position = 1;

    while (position <= NUM_PLAYERS) {
        playRound(players, firstPlayerIndex);
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (players[i].finished && !winners[i]) {
                winners[i] = position++;
                printf("Player %s finishes in position %d!\n", players[i].colour, winners[i]);
            }
        }
    }

    printf("\nGame over!\n");

    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (winners[i] == 1) {
            
                printf("Player %s finished in position 1\n", players[i].colour);
		printf("[ %s  player wins!!!]\n",players[i].colour);
	}else{
		printf("player %s finished in position %d\n", players[i].colour, winners[i]);
            }
        }

    return 0;
}

