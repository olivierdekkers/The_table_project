#include <iostream>
#include "playingfield.h"
#include <QPainter>
#include <qmath.h>
#include <QApplication>
#include <QDesktopWidget>
#include <docks.h>

PlayingField::PlayingField()
{
  //CenterPiece
  QRect rec = QApplication::desktop()->screenGeometry();
  int width = rec.height()/2;
  width /=5;
  static const int temp_possible_fields[19] = {2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,6,6,6,0};
  std::vector<int> possible_fields( temp_possible_fields, temp_possible_fields +sizeof (temp_possible_fields)/sizeof (temp_possible_fields[0]));
  int *len = new int(19);

  ZesHoek *zeshoek = new ZesHoek(width, possible_fields, len);
  zeshoek->setPos(0,0);
  Fields[0] = *zeshoek;
  //InnerRing
  for(int angle_count= 0; angle_count < 6; ++angle_count){
      ZesHoek *zeshoek = new ZesHoek(Fields[0].points[(angle_count+2)%6],angle_count,Fields[0], possible_fields, len);
      Fields[angle_count+1]=*zeshoek;
  }
  //outerring
  for(int angle_count= 0; angle_count < 6; ++angle_count){
      ZesHoek *zeshoek = new ZesHoek(Fields[angle_count+1].points[(angle_count+2)%6],angle_count,Fields[angle_count+1], possible_fields, len);
      Fields[2*angle_count+7]=*zeshoek;
      ZesHoek *zeshoek2 = new ZesHoek(Fields[angle_count+1].points[(angle_count+4)%6],angle_count,Fields[angle_count+1], possible_fields, len);
      Fields[2*angle_count+8]=*zeshoek2;
  }
  //static const int possible_field_number[18] = {5,2,6,3,8,10,9,12,11,4,8,10,9,4,5,6,3,11};
  static const int possible_field_number[18] = {2,6,3,8,10,9,12,11,4,8,5,10,9,4,5,6,3,11};
  int count = 0;
  for(int i = 18; i >=0; --i){
      if(Fields[i].field_type == 0){
          Fields[i].nummer = fieldNumber(0);
      }
      else{
          Fields[i].nummer = fieldNumber(possible_field_number[count]);
          ++count;
      }
  }
  QPoint points[54];
  int size = 0;
  bool not_in_there = 1;
  for(auto x : Fields){
      for(int corner =0 ; corner < 6; ++corner){
          for(int y =0; y < size; ++y){
              if(x.points[corner].x() == points[y].x() && x.points[corner].y() == points[y].y()){
                  not_in_there = 0;
                  break;
              }
          }
      if (not_in_there){
          points[size] = x.points[corner];
          size++;
      }
      not_in_there = 1;
      }
  }
  for(int i=0; i < 54; ++i){
      Docks *dock = new Docks();
      dock->setPos(points[i].x(),points[i].y());
      docks[i] = *dock;
  }
}


void PlayingField::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

  painter->setBrush(QColor(0,0,255));

  double angle = 0.0;
  QPoint waterPoint[6];
  for(int angle_count= 0; angle_count < 6; ++angle_count){
      angle = 360.0/6.0*angle_count*3.14159265358/180.0;
      double xcoo1 = Fields[0].get_size()*cos(angle)*6;
      double ycoo1 = Fields[0].get_size()*sin(angle)*6;
      waterPoint[int(angle_count)] = QPoint(xcoo1,ycoo1);
  }
  painter->drawPolygon(waterPoint,6);
  //painter->setBrush(QColor(255,255,255));

  //for(int angle_count= 0; angle_count < 6; ++angle_count){
  //    angle = 360.0/6.0*angle_count*3.14159265358/180.0;
  //    double xcoo1 = Fields[0].get_size()*cos(angle)*5;
  //    double ycoo1 = Fields[0].get_size()*sin(angle)*5;
  //    waterPoint[int(angle_count)] = QPoint(xcoo1,ycoo1);
  //}
  //painter->drawPolygon(waterPoint,6);

  int Number_of_fields=19;
  for(int i=0; i < Number_of_fields; ++i){
      Fields[i].paint(painter, option, widget);
  }
  int Number_of_points = 54;
  for(int j = 0; j < Number_of_points; ++j){
      docks[j].paint(painter,option,widget);
  }
}
