#ifndef MOVABLEFIELDSNUMBER_H
#define MOVABLEFIELDSNUMBER_H


#include <QLabel>
#include <playingfield.h>
#include "QSizePolicy"
#include "QPainter"
#include "iostream"
#include "QMouseEvent"
#include "clickwidget.h"

class movableFieldsNumber: public QLabel
{

public:
    movableFieldsNumber(PlayingField *parent, int size, int value ):QLabel(parent),scale(size),value(value), parent(parent){
      QPixmap pixmap= QPixmap(size,size);
      pixmap.fill(Qt::transparent);
      QPainter *painter = new QPainter(&pixmap);
      painter->setBrush(QColor(255,255,255));
      painter->drawEllipse(0,0,size,size);
      QColor color(0,0,0);
      if(value == 6 || value ==8){
          color = QColor(255,0,0);
      }
      QBrush brush(color);
      QPen pen(brush, 2);
      QFont font = painter->font();
      font.setBold(true);
      font.setPointSize(16);
      painter->setFont(font);
      painter->setPen(pen);
      if(value<10){
          painter->drawText(size/2-7,size/2+7,QString::number(value));
      }else{
          painter->drawText(size/2-11,size/2+7,QString::number(value));
      }
      setPixmap(pixmap);
    }

    QRectF boundingRect() const{
        return QRectF(0, 0,
                      30 + 3 * scale, 20 + 3 * scale);
    }
    PlayingField *parent;
    int scale, value;
};

#endif // MOVABLEFIELDSNUMBER_H
