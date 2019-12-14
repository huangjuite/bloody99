#include<vector>
#include<stdio.h>
#include<iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define cards_of_hand 5

class pocker_card;
class player;

typedef struct cards
{
    char suit;
    int point;
}card;

class pocker_card
{
    private:
        vector<card>deck;
    public:
        pocker_card();
        void shuffel();
        void show();
        void deal(player *);
};

class player
{
    private:
        vector<card>hand;
    public:
        void setCards(card);
        void show();
};