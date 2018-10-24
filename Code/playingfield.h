#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QGraphicsItem>
#include "zes_hoek.h"
#include "docks.h"

class PlayingField : public QGraphicsItem
{
public:
    PlayingField();
    PlayingField(const PlayingField &p2);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override
    {
        qreal adjust = 1;
        return QRectF(-18-adjust, -18-adjust,18-adjust,18-adjust);
    }

private:
    ZesHoek Fields[19];
    Docks docks[54];
};

#endif // PLAYINGFIELD_H

