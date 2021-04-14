#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialNowChessMap();
    void initialCanMove();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void canMoveCheck(int x, int y, int value);
    void moveOrEat(int eatX, int eatY, int eatValue, int eatenX, int eatenY);
    void end();

public slots:
    void startGame_slot();
    void placeGame_slot();

private:
    Ui::MainWindow *ui;
    int nowChessMap[9][10];
    int canMove[9][10];
    int clickedX;
    int clickedY;
    int stepNumber;
    int wholeTime;
    bool setGame;
    bool gameover;
    QLabel *whosTurn;
    QPushButton *startGame;
    QPushButton *placeGame;

};

#endif // MAINWINDOW_H
