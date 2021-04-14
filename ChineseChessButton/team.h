#ifndef TEAM_H
#define TEAM_H
#include "chess.h"
#include <QPushButton>

class Team
{
public:
    Team();
    Chess general;
    Chess guard1;
    Chess guard2;
    Chess bishop1;
    Chess bishop2;
    Chess chariot1;
    Chess chariot2;
    Chess horse1;
    Chess horse2;
    Chess cannon1;
    Chess cannon2;
    Chess pawn1;
    Chess pawn2;
    Chess pawn3;
    Chess pawn4;
    Chess pawn5;
    int allChess[8] = {0, 1, 2, 2, 2, 2, 2, 5};
};

#endif // TEAM_H
