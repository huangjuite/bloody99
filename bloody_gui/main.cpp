#include "mainwindow.h"

#include <QApplication>

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow game_gui;
    game_gui.show();
    return a.exec();
}
