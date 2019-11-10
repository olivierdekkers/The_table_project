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
  int angle = 0.0;
  for(int angle_count= 0; angle_count < 6; ++angle_count){
      angle = 360.0/6.0*angle_count*3.14159265358/180.0;
      int xcoo1 = Center_XCoord+size*sin(angle);
      int ycoo1 = Center_YCoord+size*cos(angle);
      points[angle_count]=QPoint(xcoo1,ycoo1);
  }
  calc_points();
}

ZesHoek::ZesHoek(double size)
  :color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)),
    size(size), Center_XCoord(0),Center_YCoord(0), nummer(QRandomGenerator::global()->bounded(13))
{
    calc_points();
}
ZesHoek::ZesHoek(double size, std::vector<int> &possible_fiels, int *len)
  :color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)),
    size(size), Center_XCoord(0),Center_YCoord(0)
{
  int rand = QRandomGenerator::global()->bounded(*len);
  field_type = possible_fiels[rand];
  possible_fiels.erase(possible_fiels.begin()+rand);
  --*len;
    calc_points();
}
ZesHoek::ZesHoek(double size, std::vector<int> &possible_fiels, int *len, int xCoord, int yCoord)
  :color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)),
    size(size), Center_XCoord(xCoord),Center_YCoord(yCoord)
{
  int rand = QRandomGenerator::global()->bounded(*len);
  field_type = possible_fiels[rand];
  possible_fiels.erase(possible_fiels.begin()+rand);
  --*len;
    calc_points();
}

ZesHoek::ZesHoek(QPoint p1, int corner, ZesHoek &p2):nummer(QRandomGenerator::global()->bounded(13)){
   int x_movement = p2.points[corner].x()-p1.x();
   int y_movement = p2.points[corner].y()-p1.y();
   size = p2.size;
   color = p2.color;
   Center_XCoord = p2.Center_XCoord+x_movement;
   Center_YCoord = p2.Center_YCoord+y_movement;
   for(int i = 0; i < 6; ++i){
       points[i]=QPoint(p2.points[i].x()+x_movement,p2.points[i].y()+y_movement);

   }
    calc_points();
}
ZesHoek::ZesHoek(QPoint p1 , int corner, ZesHoek &p2, std::vector<int> &possible_fiels, int *len)
  :color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)),
    Center_XCoord(0),Center_YCoord(0)
{
   int x_movement = p2.points[corner].x()-p1.x();
   int y_movement = p2.points[corner].y()-p1.y();
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
    calc_points();
}
ZesHoek::ZesHoek(ZesHoek &p2):nummer(QRandomGenerator::global()->bounded(13)){
   size = p2.size;
   color = p2.color;
   Center_XCoord = p2.Center_XCoord;
   Center_YCoord = p2.Center_YCoord;
   std::copy(std::begin(p2.points), std::end(p2.points), std::begin(points));
    calc_points();
}

void ZesHoek::paint(QPainter *painter)
{
    painter->setClipping(true);
    QPainterPath path(points[0]);
    path.lineTo(points[1]);
    path.lineTo(points[2]);
    path.lineTo(points[3]);
    path.lineTo(points[4]);
    path.lineTo(points[5]);
    path.closeSubpath();
    painter->setClipPath(path);
    QRadialGradient radialGradient(QPointF(size,size),size*2);
    //radialGradient.setColorAt(0,Qt::transparent);
    radialGradient.setColorAt(1,QColor(255,0,0));
    QRect rect(0,0,size*2,size*2);
    //painter->fillRect(rect,radialGradient);
    painter->drawPixmap(rect,pixmap);
    painter->drawPixmap(points[5].x(),points[0].y(),pixmap);
    painter->clipPath();


    painter->setClipping(false);

    //painter->drawPolygon(points,6);
    if(nummer.get_number() != 0){
        nummer.paint(painter,Center_XCoord,Center_YCoord,20);
    }
}

void ZesHoek::set_rand_color(){
    color = (QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256));
}

void ZesHoek::setPos(int x, int y){
    Center_XCoord = x;
    Center_YCoord = y;
    calc_points();
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

void ZesHoek::calc_points(void){
    int full_length2 = size/1.1;
    int full_length = size;
    int half_length = size/2;
    points[0] = QPoint(Center_XCoord - half_length,Center_YCoord-full_length2);
    points[1] = QPoint(Center_XCoord + half_length,Center_YCoord-full_length2);
    points[2] = QPoint(Center_XCoord + full_length,Center_YCoord);
    points[3] = QPoint(Center_XCoord + half_length,Center_YCoord+full_length2);
    points[4] = QPoint(Center_XCoord - half_length,Center_YCoord+full_length2);
    points[5] = QPoint(Center_XCoord - full_length,Center_YCoord);
    if(field_type == 0){
        pixmap = QPixmap("/home/olivier/Pictures/socPictures/socGame/desert.jpg");
    }
    else if(field_type == 2){
        pixmap = QPixmap("/home/olivier/Pictures/socPictures/socGame/grain2.jpeg");
    }
    else if(field_type == 3){
        pixmap = QPixmap("/home/olivier/Pictures/socPictures/socGame/weiland.jpg");
    }
    else if(field_type == 4){
        pixmap = QPixmap("/home/olivier/Pictures/socPictures/socGame/forrest.jpg");
        QRect rect(10,10,780,580);
        pixmap = pixmap.copy(rect);
    }
    else if(field_type == 5){
        pixmap = QPixmap("/home/olivier/Pictures/socPictures/socGame/mountain.jpeg");
    }
    else if(field_type == 6){
        pixmap = QPixmap("/home/olivier/Pictures/socPictures/socGame/mine.jpg");
    }
    pixmap = pixmap.scaled(size*2, size*2);
}
