#include "QTimer"
#include <iostream>
#include "playingfield.h"
#include <QPainter>
#include <qmath.h>
#include <QApplication>
#include <QDesktopWidget>
#include "QStyleOption"
#include "dragwidget.h"
#include "field_number.h"
#include "QRandomGenerator"
#include "movablefieldsnumber.h"
#include "clickwidget.h"
#include <docks.h>
#include "mini_dock.h"

PlayingField::PlayingField(int width, int height, Player *_players,QWidget *parent)
    : QFrame(parent), width(width), height(height), players(_players)

{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    //CenterPiece
    static const int temp_possible_fields[19] = {
        2,2,2,2,
        3,3,3,3,
        4,4,4,4,
        5,5,5,
        6,6,6,
        0};
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
    static const int possible_field_number[18] = {2,6,3,8,10,9,12,11,4,8,5,9,4,5,6,3,10,11};
    int count = 0;
    for(int i = 18; i >=0; i--){
      if(Fields[i].field_type == 0){
          Fields[i].nummer = fieldNumber(0);
          x = Fields[i].get_XCoord();
          y = Fields[i].get_YCoord();
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
      Docks *dock = new Docks(size, this,players->widget);
      //QObject::connect(players, SIGNAL(signalClickWidget(ClickWidget*)),dock, SLOT(slotSetWidget(ClickWidget*)));
      dock->move(points[i].x()-dock->pix.width()/2,points[i].y()-dock->pix.height()/2);
      dock->show();
    }

    for(int i=0; i < 54; ++i){
        for(int j=0; j < 54; ++j){
            if(i != j){
                if( ( points[i].x() - points[j].x()) *( points[i].x() - points[j].x()) + ( points[i].y() - points[j].y()) *( points[i].y() - points[j].y()) < 10000 ){
                    Mini_dock *mdock = new Mini_dock(size, this);
                    mdock->move( (points[i].x() + points[j].x())/2-mdock->pixmap()->width()/2,(points[i].y() + points[j].y())/2-mdock->pixmap()->height()/2 );
                    mdock->show();
                }
            }
        }
    }
    QString location = "/home/olivier/Pictures/socPictures/socGame/";
    water = QPixmap("/home/olivier/Pictures/socPictures/socGame/water.png");
    water = water.scaled(width,height);

    for(int i = 0; i < 19; ++i){
        if (Fields[i].nummer.value != 0){
            movableFieldsNumber *tamp = new movableFieldsNumber(this,size, Fields[i].nummer.value);
            tamp->move(Fields[i].get_XCoord()-size/2, Fields[i].get_YCoord()-size/2);
            tamp->show();
            tamp->setAttribute(Qt::WA_DeleteOnClose);
        }
    }

    QColor color(255,255,255);
    size =200/3;
    QString temp = location;
    temp.append(QString("boat.png"));
    QString boot= temp;
    QLabel *boat = new BaseMoveableObjects(this,color, boot,size, 0);
    boat->move(width/14-size/2, height/4-size/2);
    boat->show();
    boat->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("handelaar.png");
    QString handelaar= temp;
    QLabel *merchant = new BaseMoveableObjects(this,color, handelaar,size*2/3, 0);
    merchant->move(width/3, 0);
    merchant->show();
    merchant->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("vikings.png");
    QString struikrovers= temp;
    QLabel *bandits = new BaseMoveableObjects(this,color, struikrovers,size, 0);
    bandits->move(width/3+size, 0);
    bandits->show();
    bandits->setAttribute(Qt::WA_DeleteOnClose);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    QPoint portPoints[9] = {
        QPoint(width/3+size*2, height*2/10-size),
        QPoint(width/3-size, height*2/10+size),
        QPoint(width/4+size, height/2+size/2),
        QPoint(width/3+size/2, 8*height/10-size/2),
        QPoint(width/2-size/2, height*9/10),
        QPoint(width*2/3-8*size/5, 8*height/10-size/2),
        QPoint(width*3/4-size*2, height/2+size/2),
        QPoint(width*2/3, height*2/10+size),
        QPoint(width*2/3-size*3, height*2/10-size),
    };
    int loca = QRandomGenerator::global()->bounded(8);
    temp = location;
    temp.append(QString("ironOre.png"));
    QString ore= temp;
    QLabel *ironOre = new BaseMoveableObjects(this,color, ore,size, 0);
    ironOre->move(portPoints[loca]);
    ironOre->show();
    loca = (loca +1)%9;

    temp = location;
    temp.append("grain.jpeg");
    QString grain= temp;
    QLabel *graan = new BaseMoveableObjects(this,color, grain,size, 0);
    graan->move(portPoints[loca]);
    graan->show();
    graan->setAttribute(Qt::WA_DeleteOnClose);
    loca = (loca +1)%9;

    temp = location;
    temp.append(QString("threeone.jpeg"));
    QString threeone= temp;
    QLabel *drieeen = new BaseMoveableObjects(this,color, threeone,size, 0);
    drieeen->move(portPoints[loca]);
    drieeen->show();
    drieeen->setAttribute(Qt::WA_DeleteOnClose);
    loca = (loca +1)%9;

    temp = location;
    temp.append("wood.jpg");
    QString wood= temp;
    QLabel *hout = new BaseMoveableObjects(this,color, wood,size, 0);
    hout->move(portPoints[loca]);
    hout->show();
    hout->setAttribute(Qt::WA_DeleteOnClose);
    loca = (loca +1)%9;

    temp = location;
    temp.append(QString("steen.jpg"));
    QString stone= temp;
    QLabel *steen = new BaseMoveableObjects(this,color, stone,size, 0);
    steen->move(portPoints[loca]);
    steen->show();
    steen->setAttribute(Qt::WA_DeleteOnClose);
    loca = (loca +1)%9;

    drieeen = new BaseMoveableObjects(this,color, threeone,size, 0);
    drieeen->move(portPoints[loca]);
    drieeen->show();
    drieeen->setAttribute(Qt::WA_DeleteOnClose);
    loca = (loca +1)%9;

    drieeen = new BaseMoveableObjects(this,color, threeone,size, 0);
    drieeen->move(portPoints[loca]);
    drieeen->show();
    drieeen->setAttribute(Qt::WA_DeleteOnClose);
    loca = (loca +1)%9;

    temp = location;
    temp.append(QString("scheep.jpeg"));
    QString scheep= temp;
    QLabel *schaap = new BaseMoveableObjects(this,color, scheep,size, 0);
    schaap->move(portPoints[loca]);
    schaap->show();
    schaap->setAttribute(Qt::WA_DeleteOnClose);
    loca = (loca +1)%9;

    drieeen = new BaseMoveableObjects(this,color, threeone,size, 0);
    drieeen->move(portPoints[loca]);
    drieeen->show();
    drieeen->setAttribute(Qt::WA_DeleteOnClose);
}

void PlayingField::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);

    QPainter painter(this);
    players->paint(&painter);
    painter.setBrush(QColor(0,0,255));

    double angle = 0.0;
    QPoint waterPoint[6];
    QPainterPath path;
    for(int angle_count= 0; angle_count < 6; ++angle_count){
        angle = 360.0/6.0*angle_count*3.14159265358/180.0;
        double xcoo1 = width/2+Fields[0].get_size()*cos(angle)*6;
        double ycoo1 = height/2+Fields[0].get_size()*sin(angle)*6;
        if(angle_count == 0){
            path.moveTo(QPoint(xcoo1,ycoo1));
        }
        else{
            path.lineTo(QPoint(xcoo1,ycoo1));
        }
    }
    path.closeSubpath();
    painter.setClipping(true);
    painter.setClipPath(path);
    painter.drawPixmap(0,0,water);
    painter.setClipping(false);

    //painter->setBrush(QColor(255,255,255));

    //for(int angle_count= 0; angle_count < 6; ++angle_count){
    //    angle = 360.0/6.0*angle_count*3.14159265358/180.0;
    //    double xcoo1 = Fields[0].get_size()*cos(angle)*5;
    //    double ycoo1 = Fields[0].get_size()*sin(angle)*5;
    //    waterPoint[int(angle_count)] = QPoint(xcoo1,ycoo1);
    //}
    //painter->drawPolygon(waterPoint,6);

    int Number_of_fields=19;
    QPainter paint(this);
    for(int i=0; i < Number_of_fields; ++i){
        Fields[i].paint(&paint);
    }
    field[0].setValue(0);
    field[0].paint(&painter, width/14, height/4,20);
    field[1].setValue(1);
    field[1].paint(&painter, width/12, height/2,20);
    field[2].setValue(2);
    field[2].paint(&painter, width/6, height-2*height/10,20);
    field[3].setValue(3);
    field[3].paint(&painter, width*5 /6, height-2*height/10,20);
    field[4].setValue(4);
    field[4].paint(&painter, width*9 /10, height/2,20);
    field[5].setValue(5);
    field[5].paint(&painter, width*4.5 /6, height/10,20);
    field[6].setValue(6);
    field[6].paint(&painter, width*3/12, height*2/10,20);
    field[7].setValue(7);
    field[7].paint(&painter, width/4, height/2,20);

}

void PlayingField::add_players(Player *new_player){
    players = new_player;
}

void PlayingField::next(void){
  players = players->getNextPlayer();
    QPainter paint(this);
    fieldNumber *field = new fieldNumber(0);
    field->paint(&paint, x, y,20);
    //field->setValue(players->value);
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

        if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
            child->close();
        } else {
            child->show();
            child->setPixmap(pixmap);
        }
}

void PlayingField::mouseDoubleClickEvent(QMouseEvent *event){
    BaseMoveableObjects *child = static_cast<BaseMoveableObjects*>(childAt(event->pos()));
    //QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child){
        next();
        return;
    }
}
