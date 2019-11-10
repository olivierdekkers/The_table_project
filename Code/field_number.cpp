#include "field_number.h"
#include <QPainter>
#include <QString>

fieldNumber::fieldNumber(){
}
fieldNumber::fieldNumber(int set_value){
    value = set_value;
}


void fieldNumber::paint(QPainter *painter, int x_coordinate,int y_coordinate, int size){

  QPen oldpen = painter->pen();
  painter->setBrush(QColor(255,255,255));
  painter->drawEllipse(QPoint(x_coordinate,y_coordinate),size,size);
  xxxx = x_coordinate;
  yyyy = y_coordinate;
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
      painter->drawText(x_coordinate-7,y_coordinate+7,QString::number(value));
  }else{
      painter->drawText(x_coordinate-11,y_coordinate+7,QString::number(value));
  }
  painter->setPen(oldpen);

}
