#ifndef BASEMOVEABLEOBJECTS_H
#define BASEMOVEABLEOBJECTS_H

#include <QLabel>
#include "QSizePolicy"
#include "QPainter"

class BaseMoveableObjects: public QLabel
{
public:
    BaseMoveableObjects(QWidget *parent, QColor col, QString url, int size, int value):QLabel(parent), color(col), scale(size), value(value){
        x = 10;
        y = 10;
        QPixmap pixmap(size, size);
        pixmap.fill(Qt::transparent);
        QPixmap picture(url);
        picture = picture.scaled(size,size);
        QPainter *painter = new QPainter(&pixmap);
        QRegion r(QRect(0/2,0/2,size,size),QRegion::Ellipse);
        painter->setClipRegion(r);
        painter->drawPixmap(0,0,picture);
        QBrush brush(color);
        QPen pen(brush,10);
        painter->setPen(pen);
        painter->drawEllipse(0,0,size,size);
        setPixmap(pixmap);
        setScaledContents(true);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        painter->setClipping(false);
    }

    BaseMoveableObjects(QColor col, QString url, int size, int value): color(col), scale(size), value(value){
        x = 10;
        y = 10;
        QPixmap pixmap(size, size);
        pixmap.fill(Qt::transparent);
        QPixmap picture(url);
        picture = picture.scaled(size,size);
        QPainter *painter = new QPainter(&pixmap);
        QRegion r(QRect(0/2,0/2,size,size),QRegion::Ellipse);
        painter->setClipRegion(r);
        painter->drawPixmap(0,0,picture);
        QBrush brush(color);
        QPen pen(brush,10);
        painter->setPen(pen);
        painter->drawEllipse(0,0,size,size);
        setPixmap(pixmap);
        setScaledContents(true);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        painter->setClipping(false);
    }
    QRectF boundingRect() const;
    int scale, x,y, value;
    QColor color;
};

#endif // BASEMOVEABLEOBJECTS_H
