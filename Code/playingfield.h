#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QFrame>
#include <QGraphicsItem>
#include "zes_hoek.h"
#include "docks.h"
#include "player.h"

class PlayingField : public QFrame
{
    Q_OBJECT

public:
    PlayingField(QWidget *parent =0);

    PlayingField(const PlayingField &p2);

    void add_players(Player *new_player);
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QPaintEvent *event);
    void next(void);

private:
    Player *players;
    ZesHoek Fields[19];
    Docks docks[54];
};

#endif // PLAYINGFIELD_H

