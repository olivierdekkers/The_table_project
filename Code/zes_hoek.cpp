#include "zes_hoek.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <iostream>



ZesHoek::ZesHoek()
  :color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)),
    size(30), Center_XCoord(0),Center_YCoord(0), nummer(QRandomGenerator::global()->bounded(13))
{
  double angle = 0.0;
  for(int angle_count= 0; angle_count < 6; ++angle_count){
      angle = 360.0/6.0*angle_count*3.14159265358/180.0;
      double xcoo1 = Center_XCoord+size*sin(angle);
      double ycoo1 = Center_YCoord+size*cos(angle);
      points[angle_count]=QPoint(xcoo1,ycoo1);
  }
}

ZesHoek::ZesHoek(double size)
  :color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)),
    size(size), Center_XCoord(0),Center_YCoord(0), nummer(QRandomGenerator::global()->bounded(13))
{
  double angle = 0.0;
  for(int angle_count= 0; angle_count < 6; ++angle_count){
      angle = 360.0/6.0*angle_count*3.14159265358/180.0;
      double xcoo1 = Center_XCoord+size*sin(angle);
      double ycoo1 = Center_YCoord+size*cos(angle);
      points[angle_count]=QPoint(xcoo1,ycoo1);
  }
}
ZesHoek::ZesHoek(double size, std::vector<int> &possible_fiels, int *len)
  :color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)),
    size(size), Center_XCoord(0),Center_YCoord(0)
{
  double angle = 0.0;
  for(int angle_count= 0; angle_count < 6; ++angle_count){
      angle = 360.0/6.0*angle_count*3.14159265358/180.0;
      double xcoo1 = Center_XCoord+size*sin(angle);
      double ycoo1 = Center_YCoord+size*cos(angle);
      points[angle_count]=QPoint(xcoo1,ycoo1);
  }
  int rand = QRandomGenerator::global()->bounded(*len);
  field_type = possible_fiels[rand];
  possible_fiels.erase(possible_fiels.begin()+rand);
  --*len;
}

ZesHoek::ZesHoek(QPoint p1, int corner, ZesHoek &p2):nummer(QRandomGenerator::global()->bounded(13)){
   double x_movement = p2.points[corner].x()-p1.x();
   double y_movement = p2.points[corner].y()-p1.y();
   size = p2.size;
   color = p2.color;
   Center_XCoord = p2.Center_XCoord+x_movement;
   Center_YCoord = p2.Center_YCoord+y_movement;
   for(int i = 0; i < 6; ++i){
       points[i]=QPoint(p2.points[i].x()+x_movement,p2.points[i].y()+y_movement);

   }
}
ZesHoek::ZesHoek(QPoint p1 , int corner, ZesHoek &p2, std::vector<int> &possible_fiels, int *len)
  :color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)),
    size(size), Center_XCoord(0),Center_YCoord(0)
{
   double x_movement = p2.points[corner].x()-p1.x();
   double y_movement = p2.points[corner].y()-p1.y();
   size = p2.size;
   color = p2.color;
   Center_XCoord = p2.Center_XCoord+x_movement;
   Center_YCoord = p2.Center_YCoord+y_movement;
   for(int i = 0; i < 6; ++i){
       points[i]=QPoint(p2.points[i].x()+x_movement,p2.points[i].y()+y_movement);

   }
  int rand = QRandomGenerator::global()->bounded(*len);
  field_type = possible_fiels[rand];
  possible_fiels.erase(possible_fiels.begin()+rand);
  --*len;
}
ZesHoek::ZesHoek(ZesHoek &p2):nummer(QRandomGenerator::global()->bounded(13)){
   size = p2.size;
   color = p2.color;
   Center_XCoord = p2.Center_XCoord;
   Center_YCoord = p2.Center_YCoord;
   std::copy(std::begin(p2.points), std::end(p2.points), std::begin(points));
}

void ZesHoek::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(field_type == 0){
      painter->setBrush(QColor(244,164,96));
      painter->drawPolygon(points,6);
    }
    else if(field_type == 2){
      painter->setBrush(QColor(50,255,50));
      painter->drawPolygon(points,6);
      nummer.paint(painter,option,widget,Center_XCoord,Center_YCoord,int(20));
    }
    else if(field_type == 3){
      painter->setBrush(QColor(0,200,0));
      painter->drawPolygon(points,6);
      nummer.paint(painter,option,widget,Center_XCoord,Center_YCoord,int(20));
    }
    else if(field_type == 4){
      painter->setBrush(QColor(255,255,0));
      painter->drawPolygon(points,6);
      nummer.paint(painter,option,widget,Center_XCoord,Center_YCoord,int(20));
    }
    else if(field_type == 5){
      painter->setBrush(QColor(100,100,100));
      painter->drawPolygon(points,6);
      nummer.paint(painter,option,widget,Center_XCoord,Center_YCoord,int(20));
    }
    else if(field_type == 6){
      painter->setBrush(QColor(255,100,0));
      painter->drawPolygon(points,6);
      nummer.paint(painter,option,widget,Center_XCoord,Center_YCoord,int(20));
    }
}

void ZesHoek::set_rand_color(){
    color = (QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256));
}

void ZesHoek::setPos(int x, int y){
    Center_XCoord = x;
    Center_YCoord = y;
    double angle = 0.0;
    for(int angle_count= 0; angle_count < 6; ++angle_count){
        angle = 360.0/6.0*angle_count*3.14159265358/180.0;
        double xcoo1 = Center_XCoord+size*sin(angle);
        double ycoo1 = Center_YCoord+size*cos(angle);
        points[angle_count]=QPoint(xcoo1,ycoo1);
    }
}

int ZesHoek::get_XCoord(){
    return Center_XCoord;
}

int ZesHoek::get_YCoord(){
    return Center_YCoord;
}

int ZesHoek::calc_width(){
    int xsmallest = 0;
    int xlargest = 0;
    for(int i = 0; i < 6; ++i){
        if(points[i].x() < xsmallest){
            xsmallest = points[i].x();
        }
        else if(points[i].x() > xlargest){
            xlargest = points[i].x();
        }
    }
    return xsmallest*-1+xlargest;
}

int ZesHoek::calc_heigth(){
    int ysmallest = 0;
    int ylargest = 0;
    for(int i = 0; i < 6; ++i){
        if(points[i].y() < ysmallest){
            ysmallest = points[i].y();
        }
        else if(points[i].x() > ylargest){
            ylargest = points[i].y();
        }
    }
    return ysmallest*-1+ylargest;
}

double ZesHoek::get_size(){
    return size;
}
