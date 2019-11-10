#include <QtWidgets>

#include "clickwidget.h"
#include "basemoveableobjects.h"
#include "iostream"
#include "qmath.h"


static QString hotSpotMimeDataKey() { return QStringLiteral("application/x-hotspot"); }
//! [0]
ClickWidget::ClickWidget(QColor color, QString location, QWidget *parent) : QWidget (parent)
{
    this->setWindowFlag(Qt::Window);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_NoSystemBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);
    int widget_size = 216;
    setMinimumSize(widget_size, widget_size);
    setMaximumSize(widget_size, widget_size);
    setAcceptDrops(true);

    int size =54;
    int radius = size * 1.5;
    QPoint widgetPoitns[10];
    for(int i = 7; i >= 0; i--){
        widgetPoitns[i] = QPoint(radius * cos(i * 360/8*3.1415/180)+widget_size/2-size/2,radius * sin(i * 360/8*3.1415/180)+widget_size/2-size/2);
    }

    QString temp = location;
    temp.append(QString("village.png"));
    QString vil= temp;
    QLabel *village = new BaseMoveableObjects(this,color, vil,size,1);
    village->move(widgetPoitns[0]);
    //village->show();
    village->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("city.png");
    QString city= temp;
    QLabel *stad = new BaseMoveableObjects(this,color, city,size,2);
    stad->move(widgetPoitns[1]);
    //stad->show();
    stad->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("metropool.png");
    QString metropool= temp;
    QLabel *netropol = new BaseMoveableObjects(this,color, metropool,size, 4);
    netropol->move(widgetPoitns[2]);
    //netropol->show();
    netropol->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("knight1.png");
    QString k1= temp;
    QLabel *knight1 = new BaseMoveableObjects(this,color, k1,size, 0);
    knight1->move(widgetPoitns[3]);
    //knight1->show();
    knight1->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("knight2.png");
    QString k2= temp;
    QLabel *knight2 = new BaseMoveableObjects(this,color, k2,size, 0);
    knight2->move(widgetPoitns[4]);
    //knight2->show();
    knight2->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("knight3.png");
    QString k3= temp;
    QLabel *knight3 = new BaseMoveableObjects(this,color, k3,size, 0);
    knight3->move(widgetPoitns[5]);
    //knight3->show();
    knight3->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("road.png");
    QString road= temp;
    weg = new BaseMoveableObjects(color, road,size/2, 0);
    weg->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("helmet.png");
    QString helmet= temp;
    QLabel *helm = new BaseMoveableObjects(this,color, helmet,size/2, 0);
    helm->move(widgetPoitns[6].x()+size/4,widgetPoitns[6].y()+size/4);
    //helm->show();
    helm->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("wall.jpeg");
    QString wall= temp;
    QLabel *muur = new BaseMoveableObjects(this,color, wall,size+15, 0);
    muur->move(widgetPoitns[7].x()-12, widgetPoitns->y()-muur->pixmap()->height());
    //muur->show();
    muur->setAttribute(Qt::WA_DeleteOnClose);

}
//! [0]
ClickWidget::ClickWidget(ClickWidget &OldWidget){
}

void ClickWidget::dragEnterEvent(QDragEnterEvent *event)
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

void ClickWidget::dragMoveEvent(QDragMoveEvent *event)
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

void ClickWidget::dropEvent(QDropEvent *event)
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

        if (event->source() != this) {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

//! [1]
void ClickWidget::mousePressEvent(QMouseEvent *event)
{
    BaseMoveableObjects *child = static_cast<BaseMoveableObjects*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();
    int val = child->value;

    if(event->button() == Qt::RightButton){
        emit yourSignal(pixmap, val);
        //emit yourSignal(pixmap);
        this->close();
        return;
    }

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

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
void ClickWidget::mouseDoubleClickEvent(QMouseEvent *event){
    BaseMoveableObjects *child = static_cast<BaseMoveableObjects*>(childAt(event->pos()));
    //QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();
    int value = child->value;
    emit yourSignal(pixmap, value);
    this->close();
}

void ClickWidget::closeEvent(QCloseEvent *CloseEvent){
    int size = 69;
     QPixmap pixmap= QPixmap(size,size);
     pixmap.fill(Qt::transparent);
     QPainter *painter = new QPainter(&pixmap);
     painter->setBrush(QColor(255,255,255));
     painter->drawEllipse(0,0,size,size);
     emit yourSignal(pixmap, 3);
}
