#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>
#include <QLabel>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <pig.h>
#include <ob.h>
#include <yellowbird.h>
#include <blackbird.h>
#include <bluebird.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int ix=0,fx=0,iy=0,fy=0;
    int score=0;
    int presstime=0;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void re();
    void qquit();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QPushButton *quit_button;
    QPushButton *restart_button;
    b2Vec2 vel;
    QLabel *score_label;

    Ob *block1;
    Ob *block2;
    Ob *block3;
    Land *bot_bound;
    Land *up_bound;
    Land *left_bound;
    Land *right_bound;
    Pig *pig;
    Bird *birdie;
    Yellowbird *yellowb;
    Blackbird *blackb;
    Bluebird *blueb;
};

#endif // MAINWINDOW_H
