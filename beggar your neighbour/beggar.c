// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "beggar.h"
#include "shuffle.h"

// This function creates a new queue of the given size and initializes its fields.
Queue create_queue(int size, int total_players) {
    Queue queue;
    queue.cards = malloc(size * sizeof(int)); // allocate memory for the queue's cards array
    queue.front = 0; // initialize the front and rear indices to 0
    queue.rear = 0;
    queue.size = size; // set the size of the queue
    queue.total_players = total_players; // set the total number of players

    // initialize all cards in the queue to -1 (which represents an empty card)
    int i;
    for (i = 0; i < size; i++) {
        queue.cards[i] = -1;
    }

    // return the initialized queue
    return queue;
}

// This function checks whether the given queue is empty.
bool is_empty(Queue *queue) {
    // if the front and rear indices are the same, the queue is empty
    return queue->front == queue->rear;
}

// This function adds a card to the end of the given queue.
void enqueue(Queue *queue, int card) {
    queue->cards[queue->rear] = card; // add the card to the end of the queue
    queue->rear = (queue->rear + 1) % queue->size; // update the rear index, wrapping around if necessary
}

// This function removes and returns the card at the front of the given queue.
int dequeue(Queue *queue) {
    int card = queue->cards[queue->front]; // get the card at the front of the queue
    queue->front = (queue->front + 1) % queue->size; // update the front index, wrapping around if necessary
    return card; // return the removed card
}



Queue take_turn(Queue *player, Queue *pile, int *penalty) {
    // create a new queue to store the cards won by the player in this turn
    Queue reward = create_queue(pile->size, player->total_players);

    // if there is no penalty in effect
    if (*penalty == 0) {
        // take a card from the player's hand and add it to the pile
        int card = dequeue(player);
        enqueue(pile, card);

        // if the card is worth more than 11 points
        if (card >= 11) {
            // set the penalty to the difference between 15 and the card value
            *penalty = 15 - card;
        }
    } else {
        // if there is a penalty in effect, take a card from the player's hand
        int card = dequeue(player);

        // add the card to the reward queue (which will be returned to the player at the end of the turn)
        enqueue(&reward, card);

        // if the card is worth more than 11 points
        if (card >= 11) {
            // set the penalty to the difference between 15 and the card value
            *penalty = 15 - card;
        } else {
            // otherwise, decrease the penalty by 1
            (*penalty)--;
        }

        // if the penalty has been paid off
        if (*penalty == 0) {
            // return all cards in the reward queue to the player's hand
            while (!is_empty(&reward)) {
                int won_card = dequeue(&reward);
                enqueue(player, won_card);
            }

            // return all cards in the pile to the player's hand
            while (!is_empty(pile)) {
                int won_card = dequeue(pile);
                enqueue(player, won_card);
            }
        }
    }

    // return the reward queue to the calling function
    return reward;
}


int beggar(int Nplayers, int *deck, int talkative) {
    // Initialise the deck and players queue
    int deck_size = 52;
    Queue players[Nplayers];
    int i;

    // Initialize each player's queue with a portion of the deck
    for (i = 0; i < Nplayers; i++) {
        players[i] = create_queue(deck_size, Nplayers);
    }

    // Distribute the deck evenly among the players
    for (i = 0; i < deck_size; i++) {
        enqueue(&players[i % Nplayers], deck[i]);
    }

    // Create a queue to represent the pile of cards on the table
    Queue pile = create_queue(deck_size, Nplayers);
    int current_player = 0;
    int turns = 0;
    int penalty = 0;

    // Keep playing until the game is finished
    while (!finished(players)) {
        turns++;

        // Print the state of the game if the talkative flag is set
        if (talkative) {
            printf("Turn %d ", turns);

            if (penalty == 0) {
                printf("Top card in pile is %d, so player %d should lay a single card\n", pile.cards[pile.front], current_player);
            } else {
                printf("Top card is %d, so player %d should lay %d penalty cards\n", pile.cards[pile.front], current_player, penalty);
            }
        }

        // Perform the current player's turn and update the game state
        Queue reward = take_turn(&players[current_player], &pile, &penalty);

        // Print the decks
        if (talkative) {
            printf("Pile: ");
            for (i = pile.front; i != pile.rear; i = (i + 1) % pile.size) {
                printf("%d, ", pile.cards[i]);
            }
            printf("\n");

            for (i = 0; i < Nplayers; i++) {
                if (i == current_player) {
                    printf("* %d: ", i);
                } else {
                    printf("  %d: ", i);
                }

                int j;

                for (j = players[i].front; j != players[i].rear; j = (j + 1) % players[i].size) {
                    printf("%d, ", players[i].cards[j]);
                }
                printf("\n");
            }
        }

        // Move to the next player
        current_player = (current_player + 1) % Nplayers;

        // Free memory allocated for the reward queue
        free(reward.cards);
    }

    // Free memory allocated for each player's queue and the pile
    for (i = 0; i < Nplayers; i++) {
        free(players[i].cards);
    }
    free(pile.cards);

    // Return the total number of turns played
    return turns;
}



// This function takes a pointer to a Queue array representing the players in the game
int finished(Queue *players) {
    // Initialize a counter for the number of empty queues
    int empty_count = 0;
    // Get the total number of players from the first element of the players array
    int Nplayers = players[0].total_players;
    // Initialize a loop counter
    int i;
    // Loop over the players
    for (i = 0; i < Nplayers; i++) {
        // Check if the player's queue is not empty and the front card is not a dummy card (-1)
        if (!is_empty(&players[i]) && players[i].cards[players[i].front] != -1) {
            // If the queue is not empty and the front card is not a dummy card, increment the empty queue counter
            empty_count++;
        }
    }
    // Check if all but one queue is empty
    return empty_count == Nplayers - 1;
}



// This function takes two parameters, the number of players in the game and the number of games to simulate
Stats statistics(int Nplayers, int games) {
    // Create a new Stats struct to hold the statistics
    Stats stats;
    // Initialize the shortest game to a very large number
    stats.shortest = 100000;
    // Initialize the longest game to 0
    stats.longest = 0;
    // Initialize the average game length to 0.0
    stats.average = 0.0f;

    // Initialize the total number of turns to 0.0
    float total_turns = 0.0f;

    // Initialize a loop counter
    int i;

    // Loop over the number of games to simulate
    for (i = 0; i < games; i++) {
        // Create a new deck of cards
        int deck[52];
        // Initialize a loop counter
        int j;
        // Loop over the deck and fill it with cards
        for (j = 0; j < 52; j++) {
            // Fill the deck with cards in sequence
            deck[j] = j % 13 + 2;
        }

        // Shuffle the deck using the shuffle() function
        shuffle(deck, 52, -1);

        // Play the game and get the number of turns it took to finish
        int turns = beggar(Nplayers, deck, 0);
        // Add the number of turns to the total number of turns
        total_turns += (float)turns;

        // If this game was shorter than the shortest game seen so far
        if (turns < stats.shortest) {
            // Update the shortest game length
            stats.shortest = turns;
        }

        // If this game was longer than the longest game seen so far
        if (turns > stats.longest) {
            // Update the longest game length
            stats.longest = turns;
        }
    }

    // If no games were played (i.e. shortest was not updated) set average to -1.0f to indicate an error
    if (stats.shortest == 100000) {
        stats.average = -1.0f;
    } else {
        // Calculate the average game length
        stats.average = total_turns / (float) games;
    }

    // Return the Stats struct
    return stats;
}
