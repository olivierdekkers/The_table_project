#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QFrame>
#include <QGraphicsItem>
#include "zes_hoek.h"
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
    Q_OBJECT
public:
    explicit PlayingField(int width, int height,Player *_players, QWidget *parent =nullptr);

    explicit PlayingField(const PlayingField &p2);

    void add_players(Player *new_player);
    void next(void);
    fieldNumber field[8];
    Player *players;
protected:
    void paintEvent(QPaintEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    //void keyPressEvent(QPaintEvent *event);

private:
    ZesHoek Fields[19];
    int width;
    int height;
    BaseMoveableObjects *base;
    QPixmap water;
    int x,y;
};

#endif // PLAYINGFIELD_H

