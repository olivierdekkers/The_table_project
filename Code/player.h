#ifndef PLAYER_H
#define PLAYER_H

#include "field_number.h"
#include <QPainter>
#include <clickwidget.h>

class Player: public QObject
{
    Q_OBJECT
public:
    Player(QColor new_color, int fieldWidth, int fieldHeight, QString location);
    Player(QColor new_color, int fieldWidth, int fieldHeight, Player *nextPlayer, QString location);
    void add_player(Player *new_player);
    bool operator == (const Player& refernce) const ;

    Player* getNextPlayer(void);
    fieldNumber attached_fields[27];
    Player *next_player;
    QColor color;
    int score;
    int width;
    int height;
    ClickWidget *widget;
    void paint(QPainter *painter);
signals:
    void signalClickWidget(ClickWidget*);

public slots:
    void counterConnect(int i);
};

#endif // PLAYER_H
