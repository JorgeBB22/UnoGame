#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARDS 108
#define HAND_SIZE 7
#define NUM_PLAYERS 4

typedef struct {
    int color; // 0 = vermelho, 1 = verde, 2 = azul, 3 = amarelo, 4 = coringa
    int value; // 0 a 9, ou 10 = +2, 11 = pular, 12 = inverter, 13 = coringa, 14 = coringa +4
} Card;

typedef struct {
    Card hand[HAND_SIZE];
    int handSize;
} Player;

void initializeDeck(Card deck[]) {
    int i, j, index = 0;

    // Inicializar as cartas de cores
    for (i = 0; i < 4; i++) { // 4 cores
        for (j = 0; j <= 9; j++) { // 0 a 9
            deck[index].color = i;
            deck[index].value = j;
            index++;
            if (j != 0) { // Cada número tem 2 cópias, exceto 0
                deck[index].color = i;
                deck[index].value = j;
                index++;
            }
        }
    }

    // Cartas de ação
    for (i = 0; i < 4; i++) { // 4 cores
        deck[index].color = i;
        deck[index].value = 10; // +2
        index++;
        deck[index].color = i;
        deck[index].value = 11; // pular
        index++;
        deck[index].color = i;
        deck[index].value = 12; // inverter
        index++;
    }

    // Cartas coringa
    for (i = 0; i < 4; i++) {
        deck[index].color = 4; // coringa
        deck[index].value = 13; // coringa
        index++;
        deck[index].color = 4; // coringa
        deck[index].value = 14; // coringa +4
        index++;
    }
}

void shuffleDeck(Card deck[]) {
    int i;
    Card temp;
    int randIndex;

    for (i = 0; i < NUM_CARDS; i++) {
        randIndex = rand() % NUM_CARDS;
        temp = deck[i];
        deck[i] = deck[randIndex];
        deck[randIndex] = temp;
    }
}

void dealCards(Card deck[], Player players[]) {
    int i, j, index = 0;

    for (i = 0; i < NUM_PLAYERS; i++) {
        players[i].handSize = HAND_SIZE;
        for (j = 0; j < HAND_SIZE; j++) {
            players[i].hand[j] = deck[index++];
        }
    }
}

void printCard(Card card) {
    const char *colors[] = {"vermelho", "verde", "azul", "amarelo", "coringa"};
    const char *values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+2", "pular", "inverter", "coringa", "coringa +4"};

    printf("%s %s", colors[card.color], values[card.value]);
}

void printHand(Player player) {
    for (int i = 0; i < player.handSize; i++) {
        printCard(player.hand[i]);
        printf(" ");
    }
    printf("\n");
}

void userTurn(Player *player, Card *discardPileTop) {
    int choice;
    printf("Sua vez! Cartas na sua mão:\n");
    printHand(*player);
    
    printf("Escolha uma carta para jogar (0 a %d) ou -1 para comprar: ", player->handSize - 1);
    scanf("%d", &choice);
    
    if (choice == -1) {
        // Comprar uma carta
        printf("Você comprou uma carta!\n");
        // Implementar lógica de compra de carta aqui
    } else if (choice >= 0 && choice < player->handSize) {
        // Jogar a carta escolhida
        *discardPileTop = player->hand[choice];
        printf("Você jogou: ");
        printCard(*discardPileTop);
        printf("\n");

        // Remover a carta da mão
        for (int i = choice; i < player->handSize - 1; i++) {
            player->hand[i] = player->hand[i + 1];
        }
        player->handSize--;
    } else {
        printf("Escolha inválida!\n");
    }
}

void botTurn(Player *player, Card *discardPileTop) {
    // Simples estratégia de jogar a primeira carta válida ou comprar se não puder jogar
    printf("Bot jogando...\n");

    for (int i = 0; i < player->handSize; i++) {
        if (player->hand[i].color == discardPileTop->color || player->hand[i].value == discardPileTop->value || player->hand[i].color == 4) {
            *discardPileTop = player->hand[i];
            printf("Bot jogou: ");
            printCard(*discardPileTop);
            printf("\n");

            // Remover a carta da mão
            for (int j = i; j < player->handSize - 1; j++) {
                player->hand[j] = player->hand[j + 1];
            }
            player->handSize--;
            return;
        }
    }

    // Se não puder jogar, "comprar"
    printf("Bot não pode jogar e compra uma carta (não implementado).\n");
}

int main() {
    Card deck[NUM_CARDS];
    Player players[NUM_PLAYERS];
    Card discardPileTop;
    srand(time(NULL));

    initializeDeck(deck);
    shuffleDeck(deck);
    dealCards(deck, players);

    discardPileTop = deck[0]; // Começa com a primeira carta do baralho no monte de descarte

    while (1) {
        // Turno do usuário
        userTurn(&players[0], &discardPileTop);

        if (players[0].handSize == 0) {
            printf("Você venceu!\n");
            break;
        }

        // Turno dos bots
        for (int i = 1; i < NUM_PLAYERS; i++) {
            botTurn(&players[i], &discardPileTop);

            if (players[i].handSize == 0) {
                printf("Bot %d venceu!\n", i);
                return 0;
            }
        }
    }

    return 0;
}
