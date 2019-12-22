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


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void timer_slot();


private:
    Ui::MainWindow *ui;
    QVector<QLabel*> image_label;
    QTimer *timer;


};
#endif // MAINWINDOW_H
