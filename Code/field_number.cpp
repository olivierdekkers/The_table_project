#include "field_number.h"
#include <QPainter>
#include <QString>

fieldNumber::fieldNumber(){
}
fieldNumber::fieldNumber(int set_value){
    value = set_value;
}


void fieldNumber::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget, int x_coordinate,int y_coordinate, int size){

  painter->setBrush(QColor(255,255,255));
  painter->drawEllipse(QPoint(x_coordinate,y_coordinate),size,size);
  if(value<10){
      painter->drawText(x_coordinate-5,y_coordinate+5,QString::number(value));
  }else{
      painter->drawText(x_coordinate-9,y_coordinate+5,QString::number(value));
  }
}
