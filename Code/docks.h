#ifndef DOCKS_H
#define DOCKS_H

#include <QGraphicsItem>

class Docks
{
public:
    Docks();
    Docks(Docks &p1);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setPos(int xcoord, int ycoord);
private:
    int Center_XCoord;
    int Center_YCoord;
    int size;
};

#endif // DOCKS_H
