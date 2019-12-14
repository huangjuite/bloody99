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

void *show(void *thread)
{
    pthread_exit(NULL);
}

int main(int argc, char ** argv)
{
    srand(time(NULL));
    pocker_card cards;
    player player1;
    cards.shuffel();
    cards.show();
    cards.deal(&player1);
    printf("***\n");
    player1.show();
}