#include <iostream>
#include "playingfield.h"
#include <QPainter>
#include <qmath.h>
#include <QApplication>
#include <QDesktopWidget>
#include <docks.h>
#include "QStyleOption"
#include "dragwidget.h"

PlayingField::PlayingField(int width, int height,QWidget *parent)
    : QFrame(parent), width(width), height(height)

{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    //CenterPiece
    static const int temp_possible_fields[19] = {2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,6,6,6,0};
    std::vector<int> possible_fields( temp_possible_fields, temp_possible_fields +sizeof (temp_possible_fields)/sizeof (temp_possible_fields[0]));
    int *len = new int(19);

    ZesHoek *zeshoek = new ZesHoek(height/11, possible_fields, len, width/2,height/2);
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
      Docks *dock = new Docks(height/40);
      dock->setPos(points[i].x(),points[i].y());
      docks[i] = *dock;
    }
}

void PlayingField::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);

    QPainter painter(this);
    players->paint(&painter);
    painter.setBrush(QColor(0,0,255));

    double angle = 0.0;
    QPoint waterPoint[6];
    for(int angle_count= 0; angle_count < 6; ++angle_count){
        angle = 360.0/6.0*angle_count*3.14159265358/180.0;
        double xcoo1 = width/2+Fields[0].get_size()*cos(angle)*6;
        double ycoo1 = height/2+Fields[0].get_size()*sin(angle)*6;
        waterPoint[int(angle_count)] = QPoint(xcoo1,ycoo1);
    }
    painter.drawPolygon(waterPoint,6);
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
        Fields[i].paint(&painter);
    }
    int Number_of_points = 54;
    for(int j = 0; j < Number_of_points; ++j){
        docks[j].paint(&painter);
    }
}

void PlayingField::add_players(Player *new_player){
    players = new_player;
}

void PlayingField::next(void){
  players = players->getNextPlayer();
  update();
}

void PlayingField::dragEnterEvent(QDragEnterEvent *event)
{

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void PlayingField::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void PlayingField::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

//! [1]
void PlayingField::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child){
        next();
        return;
    }

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
//! [1]

//! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
//! [2]

//! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());
//! [3]

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
