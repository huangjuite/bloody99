#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "sockop.h"
#include "cards.h"

//Clubs : c, Diamond : d, Hearts : h, Spades : s;
using namespace std;

pocker_card cards;
vector<player> players;

void *show(void *thread)
{
    pthread_exit(NULL);
}

void initial()
{
    cards.shuffel();
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < cards_of_hand; j++)
        {
            cards.deal(&(players[i]));
        }
    }
    players[0].show();
}

void rule(card c)
{
    switch (c.point)
    {
        case 1:
            break;
        case 4:
            break;
        case 5:
            break;
        case 7:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        default:
            cards.update(c.point);
            break;
    }
}

void total_game()
{
    initial();
    int x, i = 0;
    cin >> x;
    rule(players[i].get_hand(x));
    printf("%d\n", cards.get_point());
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    player player1;
    players.push_back(player1);
    total_game();
}