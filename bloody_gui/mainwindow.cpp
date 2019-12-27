#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    char cards[]="CDHS";

    for (int i=0;i<52;i++) {
        stringstream cardName;
        cardName << ":/img/images/card/" << i%13+1 << cards[i/13] << ".png";
        cout << cardName.str()  << endl;
        QLabel *img = new QLabel(this);
        QTransform trans;
        trans.rotate(0);
        QPixmap pix(cardName.str().c_str());
        pix = pix.transformed(trans);
        img->setPixmap(pix);
        img->setGeometry(10*i,10*i,pix.width(),pix.height());
        img->setScaledContents(true);
//        img->show();
        img->hide();
        image_label.push_back(img);
    }

//    image_label[30]->show();


    player pl1;
    pl1.name = "kaikai";
    int initx = 10;
    int inity = 50;
    for(int i=0;i<5;i++){
        card_pos cpos;
        cpos.x = initx + i*20;
        cpos.y = inity;
        cpos.used = false;
        pl1.pose_set.push_back(cpos);
    }
    assign_card(pl1,3,13);

    players.push_back(pl1);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()) ,this, SLOT(timer_slot()));
    timer->start(2000);
    count = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer_slot()
{
    cout << count <<endl;
    if(count==0){
        show_card(players[0],0);
    }
    else if(count==1){
        cover_card(players[0],0);
    }
    else if(count==2){
        remove_card(players[0],0);
    }

    count ++ ;
}

void MainWindow::assign_card(player &pl, int color, int num)
{
    card new_card;
    new_card.back = new QLabel(this);
    for(int i=0;i<5;i++){
        if(!pl.pose_set[i].used){
            new_card.x = pl.pose_set[i].x;
            new_card.y = pl.pose_set[i].y;
            pl.pose_set[i].used = true;
        }
    }
    new_card.color = color;
    new_card.number = num;
    QPixmap pix(":/img/images/green_back.png");
    new_card.back->setPixmap(pix);
    new_card.back->show();
    new_card.back->setGeometry(new_card.x,new_card.y,pix.width(),pix.height());
    new_card.cover = true;
    new_card.image = image_label[color*13+num-1];
    new_card.image->setGeometry(new_card.x,new_card.y,pix.width(),pix.height());
    new_card.image->hide();
    pl.card_set.push_back(new_card);
}

void MainWindow::show_card(player &pl, int n)
{
//    cout << pl.name << endl;
    pl.card_set[n].back->hide();
    pl.card_set[n].image->show();
    pl.card_set[n].cover = false;
}

void MainWindow::cover_card(player &pl, int n)
{
    pl.card_set[n].image->hide();
    pl.card_set[n].back->show();
    pl.card_set[n].cover = true;
}

void MainWindow::remove_card(player &pl, int n)
{

    pl.card_set[n].back->hide();
    pl.card_set[n].image->hide();
//    free(pl.card_set[n].back);
    pl.card_set.erase(pl.card_set.begin()+n);
}

