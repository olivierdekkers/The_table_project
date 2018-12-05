#ifndef DOCKS_H
#define DOCKS_H

#include <QGraphicsItem>

class Docks
{
public:
    Docks();
    Docks(int size);
    Docks(Docks &p1);
    void paint(QPainter *painter);
    void setPos(int xcoord, int ycoord);
private:
    int Center_XCoord;
    int Center_YCoord;
    int size;
};

#endif // DOCKS_H
