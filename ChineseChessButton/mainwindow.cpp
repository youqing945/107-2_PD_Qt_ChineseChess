#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chess.h"
#include "team.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //black.general.button->setParent(this);
    //black.kelly->setParent(this);
    //initialSetButtons();
    //black.general.button->setIcon(QPixmap(":/chessman/b_bishop"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//======
//functions
//======

//set buttons' parent
void MainWindow::initialSetButtons(){
    //black
    /*black.general.button->setParent(this);
    black.guard1.button->setParent(this);
    black.guard2.button->setParent(this);
    black.bishop1.button->setParent(this);
    black.bishop2.button->setParent(this);
    black.chariot1.button->setParent(this);
    black.chariot2.button->setParent(this);
    black.horse1.button->setParent(this);
    black.horse2.button->setParent(this);
    black.cannon1.button->setParent(this);
    black.cannon2.button->setParent(this);
    black.pawn1.button->setParent(this);
    black.pawn2.button->setParent(this);
    black.pawn3.button->setParent(this);
    black.pawn4.button->setParent(this);
    black.pawn5.button->setParent(this);
    black.general.button->setFlat(1);
    black.guard1.button->setFlat(1);
    black.guard2.button->setFlat(1);
    black.bishop1.button->setFlat(1);
    black.bishop2.button->setFlat(1);
    black.chariot1.button->setFlat(1);
    black.chariot2.button->setFlat(1);
    black.horse1.button->setFlat(1);
    black.horse2.button->setFlat(1);
    black.cannon1.button->setFlat(1);
    black.cannon2.button->setFlat(1);
    black.pawn1.button->setFlat(1);
    black.pawn2.button->setFlat(1);
    black.pawn3.button->setFlat(1);
    black.pawn4.button->setFlat(1);
    black.pawn5.button->setFlat(1);
    //red
    red.general.button->setParent(this);
    red.guard1.button->setParent(this);
    red.guard2.button->setParent(this);
    red.bishop1.button->setParent(this);
    red.bishop2.button->setParent(this);
    red.chariot1.button->setParent(this);
    red.chariot2.button->setParent(this);
    red.horse1.button->setParent(this);
    red.horse2.button->setParent(this);
    red.cannon1.button->setParent(this);
    red.cannon2.button->setParent(this);
    red.pawn1.button->setParent(this);
    red.pawn2.button->setParent(this);
    red.pawn3.button->setParent(this);
    red.pawn4.button->setParent(this);
    red.pawn5.button->setParent(this);
    red.general.button->setFlat(1);
    red.guard1.button->setFlat(1);
    red.guard2.button->setFlat(1);
    red.bishop1.button->setFlat(1);
    red.bishop2.button->setFlat(1);
    red.chariot1.button->setFlat(1);
    red.chariot2.button->setFlat(1);
    red.horse1.button->setFlat(1);
    red.horse2.button->setFlat(1);
    red.cannon1.button->setFlat(1);
    red.cannon2.button->setFlat(1);
    red.pawn1.button->setFlat(1);
    red.pawn2.button->setFlat(1);
    red.pawn3.button->setFlat(1);
    red.pawn4.button->setFlat(1);
    red.pawn5.button->setFlat(1);*/
}
