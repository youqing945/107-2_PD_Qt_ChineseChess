#ifndef CHESS_H
#define CHESS_H
#include <QPushButton>

class Chess
{
public:
    Chess();
    QPushButton *button;
    int type;
    int position[2];
    int originalPos[2];
    bool exist = true;
};

#endif // CHESS_H
