#include "docks.h"
#include <QPainter>

Docks::Docks()
    :Center_XCoord(0), size(0), Center_YCoord(0)
{}
Docks::Docks(int newSize)
    :Center_XCoord(0), size(newSize), Center_YCoord(0)
{}

Docks::Docks(Docks &p1)
{
    Center_XCoord = p1.Center_XCoord;
    Center_YCoord = p1.Center_YCoord;
    size = p1.size;
}
void Docks::setPos(int x, int y){
    Center_XCoord = x;
    Center_YCoord = y;
}

void Docks::paint(QPainter *painter)
{
  painter->setBrush(QColor(255,255,255));

  painter->drawEllipse(QPoint(Center_XCoord,Center_YCoord),size,size);
}
