#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 99999

void set_deck(int deck[]);
void remove_from_deck(int value, int deck[]);

int get_card_value(char card[]);
int get_random_card(int deck[]);

int get_your_total(int your_total, int dealer_total, int deck[]);
int get_dealer_total(int dealer_total, int deck[]);

void check_win(int your_hand, int dealer_hand, int deck[]);
float calculate_odds(int arr[]);

int main()
{
    printf("============================\n");
    printf("| BLACKJACK ODD CALCULATOR |\n");
    printf("|       by sawsaw369       |\n");
    printf("============================\n");
    printf("\nEnter the cards on the table (2-10,J,Q,K,A)\n");
    
    int deck[52];
    set_deck(deck);
    
    char your_card1[2], your_card2[2], dealer_card[2];
    
    printf("\nYour first card: ");
    scanf("%s", your_card1);
    int your_value1 = get_card_value(your_card1);
    remove_from_deck(your_value1, deck);
    
    printf("Your second card: ");
    scanf("%s", your_card2);
    int your_value2 = get_card_value(your_card2);
    remove_from_deck(your_value2, deck);
    
    printf("The dealer's only card: ");
    scanf("%s", dealer_card);
    int dealer_value = get_card_value(dealer_card);
    remove_from_deck(dealer_value, deck);
    
    check_win(your_value1 + your_value2, get_card_value(dealer_card), deck);
}

void set_deck(int deck[])
{
    int count = 1;

    for(int i = 0; i < 52; i++)
    {
        if(i % 4 == 0 && count < 10)
            count++;
        if(i == 48)
            count++;
    
        deck[i] = count;
    }
}
void remove_from_deck(int value, int deck[])
{
    for(int i = 0; i < 52; i++)
        if(deck[i] == value)
        {
            deck[i] = 0;
            break;
        }
}

int get_card_value(char card[])
{
    if(card[0] == 'J' || card[0] == 'Q' || card[0] == 'K' || (card[0] == '1' && card [1] == '0'))
        return 10;
    else if(card[0] == 'A')
        return 11;
    else
        return card[0] - '0';
}
int get_random_card(int deck[])
{
    while(1)
    {
        int random_card = deck[rand() % 52];
        
        if(random_card != 0)
            return random_card;
    }
}

int get_your_total(int your_total, int dealer_total, int deck[])
{
    int total = your_total;
    
    if(dealer_total >= 7)
        while(total <= 15)
            total += get_random_card(deck);
    else
        while(total <= 11)
            total += get_random_card(deck);

    return total;
}
int get_dealer_total(int dealer_total,int deck[])
{
    int total = dealer_total;
    
    while(total < 17)
        total += get_random_card(deck);

    return total;
}

float calculate_odds(int arr[])
{
    int count = 0;
    for(int i = 0; i < MAX; i++)
        if(arr[i])
            count++;

    return (float) count / MAX * 100;
}
void check_win(int your_hand, int dealer_hand, int deck[])
{
    srand(time(NULL));
    
    int win[MAX];
    int push[MAX];

    for(int i = 0; i < MAX; i++)
    {
        int your_total = get_your_total(your_hand, dealer_hand, deck);
        int dealer_total = get_dealer_total(dealer_hand, deck);
    
        if(your_total > 21 && dealer_total <= 21)
        {
            win[i] = 0;
            push[i] = 0;
        }
        else if(your_total <= 21 && dealer_total > 21)
        {
            win[i] = 1;
            push[i] = 1;
        }
        else if(your_total < dealer_total)
        {
            win[i] = 0;
            push[i] = 0;
        }
        else if(your_total > dealer_total)
        {
            win[i] = 1;
            push[i] = 1;
        }
        else
        {
            win[i] = 0;
            push[i] = 1;
        }
    }

    float win_percent = calculate_odds(win);    
    float push_percent = calculate_odds(push) - win_percent;   
    float lose_percent = 100 - win_percent - push_percent;
    
    printf("Percent of winning:  %% %2.1f\n", win_percent);
    printf("Percent of pushing:  %% %2.1f\n", push_percent);
    printf("Percent of losing:  %% %2.1f\n", lose_percent);
}