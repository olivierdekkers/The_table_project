#ifndef PLAYER_H
#define PLAYER_H

#include "field_number.h"
#include "docks.h"
#include <QPainter>

class Player
{
public:
    Player(QColor new_color, int fieldWidth, int fieldHeight);
    Player(QColor new_color, int fieldWidth, int fieldHeight, Player *nextPlayer);
    void add_player(Player *new_player);
    bool operator == (const Player& refernce) const ;

    Player* getNextPlayer(void);
    Docks player_docks[9];
    fieldNumber attached_fields[27];
    Player *next_player;
    QColor color;
    int width;
    int height;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif // PLAYER_H
