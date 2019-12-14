#include "cards.h"

char suits[4] = {'c', 'd', 'h', 's'};

void swap(card *a, card *b)
{
    card temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

pocker_card::pocker_card()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j <= 13; j++)
        {
            card temp;
            temp.suit = suits[i];
            temp.point = j;
            deck.push_back(temp);
        }
    }
}
void pocker_card::shuffel()
{
    for (int i = 0; i < deck.size(); i++)
    {
        int r = i + (rand() % (52 - i));
        swap(&deck[i], &deck[r]);
    }
}
void pocker_card::show()
{
    for (int i = 0; i < deck.size(); i++)
    {
        printf("%c,%d\n", deck[i].suit, deck[i].point);
    }
}
void pocker_card::deal(player *temp)
{
    for (int i = 0; i < cards_of_hand; i++)
    {
        (*temp).setCards(deck.back());
        deck.pop_back();
    }
}

void player::setCards(card temp)
{
    hand.push_back(temp);
}
void player::show()
{
    for (int i = 0; i < hand.size(); i++)
    {
        printf("%c,%d\n", hand[i].suit, hand[i].point);
    }
};