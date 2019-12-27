#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include <iostream>
#include <sstream>
#include <QTransform>
#include <QTimer>
using namespace std;

typedef struct{
    int number;
    int color;
    bool cover;
    int x;
    int y;
    QLabel *back;
    QLabel *image;
}card;

typedef struct{
    int x;
    int y;
    bool used;
}card_pos;

typedef struct{
    string name;
    vector<card> card_set;
    vector<card_pos> pose_set;
}player;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vector<player> players;
    void assign_card(player &pl, int color, int num);
    void show_card(player &pl,int n);
    void cover_card(player &pl,int n);
    void remove_card(player &pl,int n);

public slots:
    void timer_slot();

private:
    Ui::MainWindow *ui;
    QVector<QLabel*> image_label;
    QTimer *timer;
    int count;


};
#endif // MAINWINDOW_H
