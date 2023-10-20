#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 99999

void setDeck(int deck[]);
void removeFromDeck(int value, int deck[]);
int getCardValue(char card[]);
int getRandomValue(int deck[]);
int getRandomPlayerTotal(int playerHandValue, int dealerHandValue, int deck[]);
int getRandomDealerTotal(int dealerHandValue, int deck[]);

int main()
{
    printf("=============================\n");
    printf("| BLACKJACK ODDS CALCULATOR |\n");
    printf("|          by sawyer        |\n");
    printf("=============================\n");

    int deck[52];
    setDeck(deck);

    char playerFirstCard[3], playerSecondCard[3], dealersOnlyCard[3];
    printf("\nEnter the cards on the table (2-10,J,Q,K,A)\n");

    printf("\nPlayer first card: ");
    scanf("%s", playerFirstCard);

    printf("Player second card: ");
    scanf("%s", playerSecondCard);

    printf("The dealer's only card: ");
    scanf("%s", dealersOnlyCard);

    removeFromDeck(getCardValue(playerFirstCard), deck);
    removeFromDeck(getCardValue(playerSecondCard), deck);
    removeFromDeck(getCardValue(dealersOnlyCard), deck);

    int playerHandValue = getCardValue(playerFirstCard) + getCardValue(playerSecondCard);
    int dealerHandValue = getCardValue(dealersOnlyCard);

    srand(time(NULL));

    int win = 0, push = 0, lose = 0;

    for (int i = 0; i < MAX; i++)
    {
        int temporaryDeck[52];
        for (int j = 0; j < 52; j++)
        {
            temporaryDeck[j] = deck[j];
        }

        int randomPlayerTotal = getRandomPlayerTotal(playerHandValue, dealerHandValue, temporaryDeck);
        int randomDealerTotal = getRandomDealerTotal(dealerHandValue, temporaryDeck);

        if (randomPlayerTotal > 21 && randomDealerTotal <= 21)
        {
            lose++;
        }
        else if (randomPlayerTotal <= 21 && randomDealerTotal > 21)
        {
            win++;
        }
        else if (randomPlayerTotal < randomDealerTotal)
        {
            lose++;
        }
        else if (randomPlayerTotal > randomDealerTotal)
        {
            win++;
        }
        else if ((randomPlayerTotal == randomDealerTotal) ||
                 (randomPlayerTotal > 21 && randomDealerTotal > 21))
        {
            push++;
        }
    }

    printf("\n");

    printf("Win Percentage: %% %.2f\n", (float)win / MAX * 100);
    printf("Push Percentage: %% %.2f\n", (float)push / MAX * 100);
    printf("Lose Percentage: %% %.2f\n", (float)lose / MAX * 100);

    return 0;
}

void setDeck(int deck[])
{
    int count = 1, i = 0;
    for (; i < 40; i++)
    {
        if (i % 4 == 0)
        {
            count++;
        }
        deck[i] = count;
    }
    for (; i < 52; i++)
    {
        deck[i] = 10;
    }
}

void removeFromDeck(int value, int deck[])
{
    for (int i = 0; i < 52; i++)
    {
        if (deck[i] == value)
        {
            deck[i] = 0;
            break;
        }
    }
}

int getCardValue(char card[])
{
    if (card[0] == 'J' || card[0] == 'Q' || card[0] == 'K' || (card[0] == '1' && card[1] == '0'))
    {
        return 10;
    }
    else if (card[0] == 'A')
    {
        return 11;
    }
    else
    {
        return card[0] - '0';
    }
}

int getRandomValue(int deck[])
{
    while (1)
    {
        int randnum = rand() % 52;
        int randomValue = deck[randnum];

        if (randomValue != 0)
        {
            return randomValue;
        }
    }
}

int getRandomPlayerTotal(int playerHandValue, int dealerHandValue, int deck[])
{
    if (dealerHandValue >= 7)
    {
        for (; playerHandValue <= 14;)
        {
            playerHandValue += getRandomValue(deck);
        }
    }
    else
    {
        for (; playerHandValue <= 11;)
        {
            playerHandValue += getRandomValue(deck);
        }
    }
    return playerHandValue;
}

int getRandomDealerTotal(int dealerHandValue, int deck[])
{
    for (; dealerHandValue < 17;)
    {
        dealerHandValue += getRandomValue(deck);
    }
    return dealerHandValue;
}
