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

#define num_of_player 1
#define BUFSIZE 1024
pocker_card cards;
vector<player> players;
vector<pthread_t>threads;
bool f = false, g = false;
int sem, semkey = 5555;

int P()
{
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = -1;
    sop.sem_flg = 0;

    if (semop(sem, &sop, 1) < 0)
    {
        printf("enter fail\n");
        return -1;
    }
    else
    {
        return 0;
    }
}

int V()
{
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = 1;
    sop.sem_flg = 0;

    if (semop(sem, &sop, 1) < 0)
    {
        printf("exit fail\n");
        return -1;
    }
    else
    {
        return 0;
    }
}

void *show(void *thread)
{
    pthread_exit(NULL);
}

void initial()
{
    cards.shuffel();
    cards.show();
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < cards_of_hand; j++)
        {
            cards.deal(&(players[i]));
        }
    }
}

void rule(card c)
{
    bool flag = true;
    switch (c.point)
    {
        case 1:
            if(c.suit=='s')
                cards.set_point(0);
            else
                cards.set_point(1);
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
            if(flag)
                cards.set_point(10);
            else
                cards.set_point(-10);
            break;
        case 11:
            break;
        case 12:
            if(flag)
                cards.set_point(20);
            else
                cards.set_point(-20);
            break;
        case 13:
            cards.set_point(99);
            break;
        default:
            cards.set_point(c.point);
            break;
    }
}

void *player_turn(void *address)
{
    int *connfd = (int*)address;
    int mynum = *connfd-4;
    player myplayer;
    players.push_back(myplayer);
    char snd[BUFSIZE], rcv[BUFSIZE];
    string s;
    while(1)
    {
        if(!g)
            continue;
        P();
        s="";
        vector<card>myhands = players[mynum].get_total_hand();
        for(int i=0 ; i<myhands.size() ; i++)
        {
            s = s+(myhands[i].suit)+" "+to_string(myhands[i].point)+"\n";
        }
        sprintf(snd, "%s", s.c_str());
        write(*connfd, snd, strlen(snd));
        read(*connfd, rcv, BUFSIZE);
        printf("%s\n", rcv);
        memset(rcv, 0, BUFSIZE);
        f = true;
    }
}

void *total_game(void *data)
{
    while(1)
    {
        if(players.size()>=num_of_player+1)
            break;
    }
    P();
    initial();
    V();
    g = true;
    while(1)
    {
        if(f)
        {
            printf("in total\n");
            f = false;
            V();
        }
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int *new_client, sockfd;
    struct sockaddr_in addr_cln;
    socklen_t sLen = sizeof(addr_cln);
    size_t len=0;
    ssize_t read;
    sockfd = passivesock(argv[1], "tcp", 30);
    sem = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0666);
    if(sem<0)
    {
        printf("sem create fail\n");
        exit(1);
    }
	if(semctl(sem, 0, SETVAL, 1)<0)
	{
		printf("fail to initialize semaphore\n");
		exit(1);
	}
    pthread_t game;
    int rc = pthread_create(&game, NULL, total_game, (void*)(-1));
    while(1)
    {
        new_client = new int;
        *new_client = accept(sockfd, (struct sockaddr *)&addr_cln, &sLen);
        printf("new connection:%d\n", *new_client);
        pthread_t new_th;
        threads.push_back(new_th);
        rc = pthread_create(&threads.back(), NULL, player_turn, (void *)new_client);
   }
}