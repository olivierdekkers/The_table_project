#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QFrame>
#include <QGraphicsItem>
#include "zes_hoek.h"
#include "docks.h"
#include "player.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include "basemoveableobjects.h"
#include <QDrag>

QT_BEGIN_NAMESPACE
class QDropEvent;
QT_END_NAMESPACE

class PlayingField : public QFrame
{
public:
    PlayingField(int width, int height,QWidget *parent =nullptr);

    PlayingField(const PlayingField &p2);

    void add_players(Player *new_player);
    void next(void);
protected:
    void paintEvent(QPaintEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    //void keyPressEvent(QPaintEvent *event);

private:
    Player *players;
    ZesHoek Fields[19];
    Docks docks[54];
    int width;
    int height;
    BaseMoveableObjects *base;
};

#endif // PLAYINGFIELD_H

