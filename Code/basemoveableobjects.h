#ifndef BASEMOVEABLEOBJECTS_H
#define BASEMOVEABLEOBJECTS_H

#include <QLabel>
#include "QSizePolicy"
#include "QPainter"

class BaseMoveableObjects: public QLabel
{
public:
    BaseMoveableObjects(QFrame *parent, QColor col, QString url, int size):QLabel(parent), color(col), scale(size){
        x = 10;
        y = 10;
        QPixmap pixmap(url);
        pixmap = pixmap.scaled(size,size);
        QPainter *painter = new QPainter(&pixmap);
        painter->setPen (color);
        painter->drawRect(0,0,size,size);
        setPixmap(pixmap);
        setScaledContents(true);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }
    QRectF boundingRect() const;
    int scale, x,y;
    QColor color;
};

#endif // BASEMOVEABLEOBJECTS_H
