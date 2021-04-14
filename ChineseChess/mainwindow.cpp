#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);

    this->setWindowTitle("Chinese Chess");

    //set the background picture
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/ccmap/src/bavkground1.png")));
    this->setPalette(palette);

    //==========

    gameover = true;

    startGame = new QPushButton("Start", this);
    startGame->setGeometry(1200, 450, 200, 100);
    connect(startGame, SIGNAL(clicked(bool)), this, SLOT(startGame_slot()));

    placeGame = new QPushButton("Place", this);
    placeGame->setGeometry(1200, 600, 200, 100);
    connect(placeGame, SIGNAL(clicked(bool)), this, SLOT(placeGame_slot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialNowChessMap(){
    memset(nowChessMap, 0, 90*sizeof(int));
    //black
    nowChessMap[4][0]=1; //general/將
    nowChessMap[3][0]=2; //guard/士
    nowChessMap[5][0]=2;
    nowChessMap[2][0]=3; //bishop/象
    nowChessMap[6][0]=3;
    nowChessMap[1][0]=5; //horse/馬
    nowChessMap[7][0]=5;
    nowChessMap[0][0]=4; //chariot/車
    nowChessMap[8][0]=4;
    nowChessMap[1][2]=6; //cannon/包
    nowChessMap[7][2]=6;
    for(int i=0; i<=4; i++) nowChessMap[2*i][3]=7; //pawn/卒

    //red
    nowChessMap[4][9]=-1; //general/帥
    nowChessMap[3][9]=-2; //guard/仕
    nowChessMap[5][9]=-2;
    nowChessMap[2][9]=-3; //bishop/相
    nowChessMap[6][9]=-3;
    nowChessMap[1][9]=-5; //horse/傌
    nowChessMap[7][9]=-5;
    nowChessMap[0][9]=-4; //chariot/俥
    nowChessMap[8][9]=-4;
    nowChessMap[1][7]=-6; //cannon/炮
    nowChessMap[7][7]=-6;
    for(int i=0; i<=4; i++) nowChessMap[2*i][6]=-7; //pawn/兵

    initialCanMove();
    clickedX=-100;
    clickedY=-100;
    setGame = false;

}

void MainWindow::initialCanMove(){
    for(int i=0; i<=8; i++)for(int j=0; j<=9; j++)canMove[i][j]=nowChessMap[i][j];
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(20<event->pos().x() && event->pos().x()<=1000 &&
            60<event->pos().y() && event->pos().y()<=1150 && !gameover){
        int x = event->pos().x() / 10, y = event->pos().y() / 10;
        if(!(x==12||x==23||x==34||x==45||x==56||x==67||x==78||x==89)
                &&!(y==16||y==27||y==38||y==49||y==60||y==71||y==82||y==93||y==104)){
            for(int i=0; i<9; i++){
                if(x<=12+i*11){
                    x=i;
                    break;
                }
            }
            for(int i=0; i<10; i++){
                if(y<=16+i*11){
                    y=i;
                    break;
                }
            }
            if(canMove[x][y]==10) moveOrEat(clickedX, clickedY, nowChessMap[clickedX][clickedY], x, y);
            else if(nowChessMap[x][y]==0){
                initialCanMove();
                return;
            }
            else if(stepNumber%2==0 && nowChessMap[x][y]>0){
                initialCanMove();
                canMoveCheck(x, y, nowChessMap[x][y]);
            }
            else if(stepNumber%2==1 && nowChessMap[x][y]<0){
                initialCanMove();
                canMoveCheck(x, y, nowChessMap[x][y]);
            }
            else{
                initialCanMove();
                return;
            }
            clickedX=x;
            clickedY=y;
            this->repaint();
        }
    }
}

void MainWindow::canMoveCheck(int x, int y, int value){
    bool skip = false; //for cannon
    if(value == 1){ //black general
        if(x-1>=3 && nowChessMap[x-1][y]<=0) canMove[x-1][y]=10;
        if(x+1<=5 && nowChessMap[x+1][y]<=0) canMove[x+1][y]=10;
        if(y-1>=0 && nowChessMap[x][y-1]<=0) canMove[x][y-1]=10;
        if(y+1<=2 && nowChessMap[x][y+1]<=0) canMove[x][y+1]=10;
    }
    else if(value == 2){ //black guard
        if(x-1>=3 && y-1>=0 &&nowChessMap[x-1][y-1]<=0) canMove[x-1][y-1]=10;
        if(x-1>=3 && y+1<=2 &&nowChessMap[x-1][y+1]<=0) canMove[x-1][y+1]=10;
        if(x+1<=5 && y-1>=0 &&nowChessMap[x+1][y-1]<=0) canMove[x+1][y-1]=10;
        if(x+1<=5 && y+1<=2 &&nowChessMap[x+1][y+1]<=0) canMove[x+1][y+1]=10;
    }
    else if(value == 3){ //black bishop
        if(x-2>=0 && y-2>=0 && nowChessMap[x-2][y-2]<=0) canMove[x-2][y-2]=10;
        if(x-2>=0 && y+2<=4 && nowChessMap[x-2][y+2]<=0) canMove[x-2][y+2]=10;
        if(x+2<=8 && y-2>=0 && nowChessMap[x+2][y-2]<=0) canMove[x+2][y-2]=10;
        if(x+2<=8 && y+2<=4 && nowChessMap[x+2][y+2]<=0) canMove[x+2][y+2]=10;
    }
    else if(value == 4){ //black chariot
        for(int i=1; i<9; i++){ //right
            if(x+i<=8 && nowChessMap[x+i][y]==0) canMove[x+i][y]=10;
            else if(x+i<=8 && nowChessMap[x+i][y]<0){
                canMove[x+i][y]=10;
                break;
            }
            else break;
        }
        for(int i=1; i<9; i++){ //left
            if(x-i>=0 && nowChessMap[x-i][y]==0) canMove[x-i][y]=10;
            else if(x-i>=0 && nowChessMap[x-i][y]<0){
                canMove[x-i][y]=10;
                break;
            }
            else break;
        }
        for(int i=1; i<10; i++){ //down
            if(y+i<=9 && nowChessMap[x][y+i]==0) canMove[x][y+i]=10;
            else if(y+i<=9 && nowChessMap[x][y+i]<0){
                canMove[x][y+i]=10;
                break;
            }
            else break;
        }
        for(int i=1; i<10; i++){ //up
            if(y-i>=0 && nowChessMap[x][y-i]==0) canMove[x][y-i]=10;
            else if(y-i>=0 && nowChessMap[x][y-i]<0){
                canMove[x][y-i]=10;
                break;
            }
            else break;
        }
    }
    else if(value == 5){ //black horse
        if(x-2>=0 && y-1>=0 && nowChessMap[x-1][y]==0 && nowChessMap[x-2][y-1]<=0) canMove[x-2][y-1]=10;
        if(x-1>=0 && y-2>=0 && nowChessMap[x][y-1]==0 && nowChessMap[x-1][y-2]<=0) canMove[x-1][y-2]=10;
        if(x-2>=0 && y+1<=9 && nowChessMap[x-1][y]==0 && nowChessMap[x-2][y+1]<=0) canMove[x-2][y+1]=10;
        if(x-1>=0 && y+2<=9 && nowChessMap[x][y+1]==0 && nowChessMap[x-1][y+2]<=0) canMove[x-1][y+2]=10;
        if(x+2<=8 && y-1>=0 && nowChessMap[x+1][y]==0 && nowChessMap[x+2][y-1]<=0) canMove[x+2][y-1]=10;
        if(x+1<=8 && y-2>=0 && nowChessMap[x][y-1]==0 && nowChessMap[x+1][y-2]<=0) canMove[x+1][y-2]=10;
        if(x+2<=8 && y+1<=9 && nowChessMap[x+1][y]==0 && nowChessMap[x+2][y+1]<=0) canMove[x+2][y+1]=10;
        if(x+1<=8 && y+2<=9 && nowChessMap[x][y+1]==0 && nowChessMap[x+1][y+2]<=0) canMove[x+1][y+2]=10;
    }
    else if(value == 6){ //black cannon
        skip=false; //right
        for(int i=1; i<=8; i++){
            if(x+i<=8 && nowChessMap[x+i][y]==0 && !skip) canMove[x+i][y]=10;
            else if(x+i<=8 && nowChessMap[x+i][y]!=0 && !skip) skip=true;
            else if(x+i<=8 && nowChessMap[x+i][y]<0 && skip){
                canMove[x+i][y]=10;
                break;
            }
        }
        skip=false; //left
        for(int i=1; i<=8; i++){
            if(x-i>=0 && nowChessMap[x-i][y]==0 && !skip) canMove[x-i][y]=10;
            else if(x-i>=0 && nowChessMap[x-i][y]!=0 && !skip) skip=true;
            else if(x-i>=0 && nowChessMap[x-i][y]<0 && skip){
                canMove[x-i][y]=10;
                break;
            }
        }
        skip=false; //down
        for(int i=1; i<=9; i++){
            if(y+i<=9 && nowChessMap[x][y+i]==0 && !skip) canMove[x][y+i]=10;
            else if(y+i<=9 && nowChessMap[x][y+i]!=0 && !skip) skip=true;
            else if(y+i<=9 && nowChessMap[x][y+i]<0 && skip){
                canMove[x][y+i]=10;
                break;
            }
        }
        skip=false; //up
        for(int i=1; i<=9; i++){
            if(y-i>=0 && nowChessMap[x][y-i]==0 && !skip) canMove[x][y-i]=10;
            else if(y-i>=0 && nowChessMap[x][y-i]!=0 && !skip) skip=true;
            else if(y-i>=0 && nowChessMap[x][y-i]<0 && skip){
                canMove[x][y-i]=10;
                break;
            }
        }
    }
    else if(value == 7){ //black pawn
        if(y<=4) canMove[x][y+1]=10;
        else{
            if(x-1>=0 && nowChessMap[x-1][y]<=0) canMove[x-1][y]=10;
            if(x+1<=8 && nowChessMap[x+1][y]<=0) canMove[x+1][y]=10;
            if(y+1<=9 && nowChessMap[x][y+1]<=0) canMove[x][y+1]=10;
        }
    }
    //====================
    else if(value == -1){ //red general
        if(x-1>=3 && nowChessMap[x-1][y]>=0) canMove[x-1][y]=10;
        if(x+1<=5 && nowChessMap[x+1][y]>=0) canMove[x+1][y]=10;
        if(y-1>=7 && nowChessMap[x][y-1]>=0) canMove[x][y-1]=10;
        if(y+1<=9 && nowChessMap[x][y+1]>=0) canMove[x][y+1]=10;
    }
    else if(value == -2){ //red guard
        if(x-1>=3 && y-1>=7 &&nowChessMap[x-1][y-1]>=0) canMove[x-1][y-1]=10;
        if(x-1>=3 && y+1<=9 &&nowChessMap[x-1][y+1]>=0) canMove[x-1][y+1]=10;
        if(x+1<=5 && y-1>=7 &&nowChessMap[x+1][y-1]>=0) canMove[x+1][y-1]=10;
        if(x+1<=5 && y+1<=9 &&nowChessMap[x+1][y+1]>=0) canMove[x+1][y+1]=10;
    }
    else if(value == -3){ //red bishop
        if(x-2>=0 && y-2>=5 && nowChessMap[x-2][y-2]>=0) canMove[x-2][y-2]=10;
        if(x-2>=0 && y+2<=9 && nowChessMap[x-2][y+2]>=0) canMove[x-2][y+2]=10;
        if(x+2<=8 && y-2>=5 && nowChessMap[x+2][y-2]>=0) canMove[x+2][y-2]=10;
        if(x+2<=8 && y+2<=9 && nowChessMap[x+2][y+2]>=0) canMove[x+2][y+2]=10;
    }
    else if(value == -4){ //red chariot
        for(int i=1; i<9; i++){ //right
            if(x+i<=8 && nowChessMap[x+i][y]==0) canMove[x+i][y]=10;
            else if(x+i<=8 && nowChessMap[x+i][y]>0){
                canMove[x+i][y]=10;
                break;
            }
            else break;
        }
        for(int i=1; i<9; i++){ //left
            if(x-i>=0 && nowChessMap[x-i][y]==0) canMove[x-i][y]=10;
            else if(x-i>=0 && nowChessMap[x-i][y]>0){
                canMove[x-i][y]=10;
                break;
            }
            else break;
        }
        for(int i=1; i<10; i++){ //down
            if(y+i<=9 && nowChessMap[x][y+i]==0) canMove[x][y+i]=10;
            else if(y+i<=9 && nowChessMap[x][y+i]>0){
                canMove[x][y+i]=10;
                break;
            }
            else break;
        }
        for(int i=1; i<10; i++){ //up
            if(y-i>=0 && nowChessMap[x][y-i]==0) canMove[x][y-i]=10;
            else if(y-i>=0 && nowChessMap[x][y-i]>0){
                canMove[x][y-i]=10;
                break;
            }
            else break;
        }
    }
    else if(value == -5){ //red horse
        if(x-2>=0 && y-1>=0 && nowChessMap[x-1][y]==0 && nowChessMap[x-2][y-1]>=0) canMove[x-2][y-1]=10;
        if(x-1>=0 && y-2>=0 && nowChessMap[x][y-1]==0 && nowChessMap[x-1][y-2]>=0) canMove[x-1][y-2]=10;
        if(x-2>=0 && y+1<=9 && nowChessMap[x-1][y]==0 && nowChessMap[x-2][y+1]>=0) canMove[x-2][y+1]=10;
        if(x-1>=0 && y+2<=9 && nowChessMap[x][y+1]==0 && nowChessMap[x-1][y+2]>=0) canMove[x-1][y+2]=10;
        if(x+2<=8 && y-1>=0 && nowChessMap[x+1][y]==0 && nowChessMap[x+2][y-1]>=0) canMove[x+2][y-1]=10;
        if(x+1<=8 && y-2>=0 && nowChessMap[x][y-1]==0 && nowChessMap[x+1][y-2]>=0) canMove[x+1][y-2]=10;
        if(x+2<=8 && y+1<=9 && nowChessMap[x+1][y]==0 && nowChessMap[x+2][y+1]>=0) canMove[x+2][y+1]=10;
        if(x+1<=8 && y+2<=9 && nowChessMap[x][y+1]==0 && nowChessMap[x+1][y+2]>=0) canMove[x+1][y+2]=10;
    }
    else if(value == -6){ //red cannon
        skip=false; //right
        for(int i=1; i<=8; i++){
            if(x+i<=8 && nowChessMap[x+i][y]==0 && !skip) canMove[x+i][y]=10;
            else if(x+i<=8 && nowChessMap[x+i][y]!=0 && !skip) skip=true;
            else if(x+i<=8 && nowChessMap[x+i][y]>0 && skip){
                canMove[x+i][y]=10;
                break;
            }
        }
        skip=false; //left
        for(int i=1; i<=8; i++){
            if(x-i>=0 && nowChessMap[x-i][y]==0 && !skip) canMove[x-i][y]=10;
            else if(x-i>=0 && nowChessMap[x-i][y]!=0 && !skip) skip=true;
            else if(x-i>=0 && nowChessMap[x-i][y]>0 && skip){
                canMove[x-i][y]=10;
                break;
            }
        }
        skip=false; //down
        for(int i=1; i<=9; i++){
            if(y+i<=9 && nowChessMap[x][y+i]==0 && !skip) canMove[x][y+i]=10;
            else if(y+i<=9 && nowChessMap[x][y+i]!=0 && !skip) skip=true;
            else if(y+i<=9 && nowChessMap[x][y+i]>0 && skip){
                canMove[x][y+i]=10;
                break;
            }
        }
        skip=false; //up
        for(int i=1; i<=9; i++){
            if(y-i>=0 && nowChessMap[x][y-i]==0 && !skip) canMove[x][y-i]=10;
            else if(y-i>=0 && nowChessMap[x][y-i]!=0 && !skip) skip=true;
            else if(y-i>=0 && nowChessMap[x][y-i]>0 && skip){
                canMove[x][y-i]=10;
                break;
            }
        }
    }
    else if(value == -7){ //red pawn
        if(y>=5) canMove[x][y-1]=10;
        else{
            if(x-1>=0 && nowChessMap[x-1][y]>=0) canMove[x-1][y]=10;
            if(x+1<=8 && nowChessMap[x+1][y]>=0) canMove[x+1][y]=10;
            if(y-1>=0 && nowChessMap[x][y-1]>=0) canMove[x][y-1]=10;
        }
    }
}

void MainWindow::moveOrEat(int eatX, int eatY, int eatValue, int eatenX, int eatenY){
    stepNumber++;
    nowChessMap[eatX][eatY]=0;
    nowChessMap[eatenX][eatenY]=eatValue;
    initialCanMove();
    end();
}

void MainWindow::end(){
    gameover=true;
    int bossMeet[4]={0, 0, 0, 0};
    for(int i=3; i<6; i++)
        for(int j=0; j<3; j++)
            if(nowChessMap[i][j]==1){
                gameover=false;
                bossMeet[0]=i;
                bossMeet[1]=j;
            }
    if(!gameover){
        gameover=true;
        for(int i=3; i<6; i++)
            for(int j=7; j<10; j++)
                if(nowChessMap[i][j]==-1){
                    gameover=false;
                    bossMeet[2]=i;
                    bossMeet[3]=j;
                }
    }
    if(!gameover)
        if(bossMeet[0]==bossMeet[2]){
            gameover=true;
            for(int i=bossMeet[1]+1; i<bossMeet[3]; i++)
                if(nowChessMap[bossMeet[0]][i]!=0){
                    gameover=false;
                    break;
                }
            if(gameover==true) stepNumber++;
        }
    if(gameover==true){
        QString winner = (stepNumber%2==0? "紅棋":"黑棋");
        stepNumber=0;
        QMessageBox::information(this, "對局結果：", winner+"取得勝利！", QMessageBox::Yes);
    }

}

//SLOT==========================
//==============================
void MainWindow::startGame_slot(){
    qDebug() << "start";

    clickedX = 0;
    clickedY = 0;
    stepNumber = 0;
    wholeTime = 0;
    gameover = false;
    setGame = false;
    startGame->setText("Restart");
    initialNowChessMap();
    this->repaint();
}

void MainWindow::placeGame_slot(){
    setGame = true;
    placeGame->hide();
}

//==============================

void MainWindow::paintEvent(QPaintEvent *){
    QPainter paint(this);
    paint.drawImage(QRect(0, 0, 1020, 1200), QImage(":/ccmap/src/map/Chessmap.png"));
    for(int i=0; i<9; i++)
        for(int j=0; j<10; j++){
            switch (nowChessMap[i][j]) {
            case 1: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/b_general.png")); break;
            case 2: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/b_guard.png")); break;
            case 3: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/b_bishop.png")); break;
            case 4: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/b_chariot.png")); break;
            case 5: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/b_horse.png")); break;
            case 6: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/b_cannon.png")); break;
            case 7: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/b_pawn.png")); break;
            case -1: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/r_general.png")); break;
            case -2: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/r_guard.png")); break;
            case -3: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/r_bishop.png")); break;
            case -4: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/r_chariot.png")); break;
            case -5: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/r_horse.png")); break;
            case -6: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/r_cannon.png")); break;
            case -7: paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/chess/src/chess/r_pawn.png")); break;
            default: break;
            }
            if(canMove[i][j]==10) paint.drawImage(QRect(20+110*i, 60+110*j, 100, 100), QImage(":/choose/src/choose/canmove.png"));
        }
    paint.drawImage(QRect(20+110*clickedX, 60+110*clickedY, 100, 100), QImage(":/choose/src/choose/lastmove.png"));
    if(stepNumber%2==0) paint.drawImage(QRect(1010, 280, 100, 100), QImage(":/choose/whosturn"));
    else paint.drawImage(QRect(1010, 830, 100, 100), QImage(":/choose/whosturn"));

}
