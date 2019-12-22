#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>
#include<semaphore.h>
#include "sockop.h"
#include "cards.h"

//Clubs : c, Diamond : d, Hearts : h, Spades : s;
using namespace std;

#define num_of_player 1
#define BUFSIZE 1024
pocker_card cards;
vector<player> players;
vector<pthread_t>threads;
vector<sem_t>mysem;
bool f = false, g = false;
char snd[BUFSIZE], rcv[BUFSIZE];
sem_t game_sem;
int turn_count;
bool turn_flag; //clockwise = true, counterclockwise =false;

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

void rule(card c, int i, int j)
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
            turn_flag = -turn_flag;
            break;
        case 5:
            turn_count = j;
            break;
        case 7:
            cards.change_one_card(&players[i], &players[j]);
            break;
        case 9:
            cards.change_all_card(&players[i], &players[j]);
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
    sem_t sem;
    sem_init(&sem, 0, 0);
    mysem.push_back(sem);
    int *connfd = (int*)address;
    int mynum = *connfd-4;
    player myplayer;
    players.push_back(myplayer);
    string s;
    while(1)
    {
        if(!g)
            continue;
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
        break;
    }
    cout<<"out"<<endl;
    sem_wait(&game_sem);
    turn_count++;
    printf("count = %d, %d\n", turn_count, mynum);
    sem_post(&game_sem);
    while(1)
    {
        sem_wait(&mysem[mynum]);
        cout<<"in "<<mynum<<endl;
        sprintf(snd, "input data\n");
        write(*connfd, snd, strlen(snd));
        memset(rcv, 0, BUFSIZE);
        read(*connfd, rcv, BUFSIZE);
        printf("in thread %s\n", rcv);
        sem_post(&game_sem);
    }
}

void *total_game(void *data)
{
    while(1)
    {
        if(players.size()>=num_of_player+1)
            break;
    }
    initial();
    g = true;
    sem_init(&game_sem, 0, 1);
    //wait for all player is ok;
    while(1)
    {
        if(turn_count==mysem.size())
            break;
    }
    cout<<"all player is ok"<<endl;
    turn_flag = true;
    turn_count = 0;
    while(1)
    {
        sem_wait(&game_sem);
        sem_post(&mysem[turn_count]);
        if(turn_flag == true)
        {
            turn_count++;
            if(turn_count>=mysem.size())
                turn_count = 0;
        }
        else
        {
            turn_count--;
            if(turn_count<=0)
                turn_count = mysem.size();
        }
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    players.clear();
    threads.clear();
    mysem.clear();
    turn_count = 0;
    int *new_client, sockfd;
    struct sockaddr_in addr_cln;
    socklen_t sLen = sizeof(addr_cln);
    size_t len=0;
    ssize_t read;
    sockfd = passivesock(argv[1], "tcp", 30);
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

    //test
    /*player p1,p2;
    players.push_back(p1);
    players.push_back(p2);
    initial();
    cout<<"***\n";
    players[0].show();
    cout<<"***\n";
    players[1].show();
    cout<<"***\n";
    cards.change_all_card(&players[0],&players[1]);
    players[0].show();
    cout<<"%%%\n";
    players[1].show();
    cout<<"%%%\n";
    cards.change_one_card(&players[0],&players[1]);
    players[0].show();
    cout<<"111\n";
    players[1].show();
    cout<<"2222\n";*/
}