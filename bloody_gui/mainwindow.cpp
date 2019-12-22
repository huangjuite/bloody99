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

    image_label[30]->show();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()) ,this, SLOT(timer_slot()));
    timer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer_slot()
{
    cout << "yap" <<endl;
}

