#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 99999

int get_card_value(char card[])
{
    if(card[0] == 'J' || card[0] == 'Q' || card[0] == 'K' || (card[0] == '1' && card [1] == '0'))
        return 10;
    else if(!strcmp(card, "A"))
        return 11;
    else
        return card[0] - '0';
}

int get_random_card()
{
    int random_number = rand() % 13 + 1;
    
    char card[2];
    if(random_number == 10)
    {
        card[0] = '1';
        card[1] = '0';
    }
    else if(random_number == 1)
        card[0] = 'A';
    else if(random_number == 11)
        card[0] = 'J';
    else if(random_number == 12)
        card[0] = 'Q';
    else if(random_number == 13)
        card[0] = 'K';
    else
        card[0] = random_number + '0';

    int card_value = get_card_value(card);

    return card_value;
}

int get_your_total(int your_total, int dealer_total)
{
    int total = your_total;
    if(dealer_total >= 7)
        while(total <= 15)
            total += get_random_card();
    else
        while(total <= 11)
            total +=  get_random_card();
    return total;
}

int get_dealer_total(int dealer_total)
{
    int total = dealer_total;
    
    while(total < 17)
    {
        int card_value = get_random_card();
        total += card_value;
    }
    return total;
}

float calculate_odds(int save[]) 
{
    int count = 0;
    for(int i = 0; i < MAX; i++) 
    {
        if(save[i] == 1) 
        {
            count++;
        }
    }
    return ((float)count / MAX) * 100;
}

int check_win(int your_hand, int dealer_hand)
{
    srand(time(NULL));
    
    static int save[MAX];    
    for(int i = 0; i < MAX; i++)
    {
        int your_total = get_your_total(your_hand, dealer_hand);
        int dealer_total = get_dealer_total(dealer_hand);
    
        if(your_total > 21 && dealer_total <= 21)
            save[i] = 0;
        else if(your_total <= 21 && dealer_total > 21)
            save[i] = 1;
        else if(your_total < dealer_total)
            save[i] = 0;
        else if(your_total >= dealer_total)
            save[i] = 1;
    }
    float a = calculate_odds(save);
    
    printf("\nPercent of winning or pushing:  %% %2.1f\n",a);
}
int main()
{
    char card1[2], card2[2], card3[2];
    
    printf("=============================\n");
    printf("| BLACKJACK ODDS CALCULATOR |\n");
    printf("|       by sawsaw3639       |\n");
    printf("=============================\n");
    
    printf("\nEnter the cards on the table (2-10,J,Q,K,A)\n");
    printf("\nYour first card: ");
    scanf("%2s", card1);
    
    printf("Your second card: ");
    scanf("%2s", card2);
    
    printf("The dealer's only card: ");
    scanf("%2s", card3);

    int card1_value = get_card_value(card1);
    int card2_value = get_card_value(card2);
    
    int dealer_hand = get_card_value(card3);
    int your_hand = card1_value + card2_value;
    
    check_win(your_hand, dealer_hand);
}