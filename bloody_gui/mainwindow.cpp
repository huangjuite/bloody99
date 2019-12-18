#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel *lblFirstName = new QLabel("First Name");
    QLabel *lblLastName = new QLabel("Last Name");

    QLineEdit *txtFirstName = new QLineEdit();
    QLineEdit *txtLastName = new QLineEdit();

    QPushButton *btnOk = new QPushButton("OK");
    QPushButton *btnCancel = new QPushButton("Cancel");

    QHBoxLayout *top = new QHBoxLayout;
    QHBoxLayout *bottom = new QHBoxLayout;
    QHBoxLayout *btnLayout = new QHBoxLayout;
    QHBoxLayout *imgeLayout = new QHBoxLayout;

    top->addWidget(lblFirstName);
    top->addWidget(txtFirstName);

    bottom->addWidget(lblLastName);
    bottom->addWidget(txtLastName);

    btnLayout->addStretch();
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);

    for (int i=0;i<52;i++) {
        QLabel *img = new QLabel;
        img->setPixmap(QPixmap(":/img/imgaes/card/1C.png"));
        img->show();

        image_label.push_back(img);
        imgeLayout->addWidget(img);
    }


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(top);
    mainLayout->addLayout(bottom);
    mainLayout->addLayout(btnLayout);
    mainLayout->addLayout(imgeLayout);

    this->centralWidget()->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

