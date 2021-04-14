#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton *b_general;
    QPushButton *b_guard1;
    QPushButton *b_guard2;
    QPushButton *b_bishop1;
    QPushButton *b_bishop2;
    QPushButton *b_chariot1;
    QPushButton *b_chariot2;
    QPushButton *b_horse1;
    QPushButton *b_horse2;
    QPushButton *b_cannon1;
    QPushButton *b_cannon2;
    QPushButton *b_pawn1;
    QPushButton *b_pawn2;
    QPushButton *b_pawn3;
    QPushButton *b_pawn4;
    QPushButton *b_pawn5;
    QPushButton *r_general;
    QPushButton *r_guard1;
    QPushButton *r_guard2;
    QPushButton *r_bishop1;
    QPushButton *r_bishop2;
    QPushButton *r_chariot1;
    QPushButton *r_chariot2;
    QPushButton *r_horse1;
    QPushButton *r_horse2;
    QPushButton *r_cannon1;
    QPushButton *r_cannon2;
    QPushButton *r_pawn1;
    QPushButton *r_pawn2;
    QPushButton *r_pawn3;
    QPushButton *r_pawn4;
    QPushButton *r_pawn5;
    int b_allChess[8] = {0, 1, 2, 2, 2, 2, 2, 5};
    int r_allChess[8] = {0, 1, 2, 2, 2, 2, 2, 5};
    void initialSetButtons();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
