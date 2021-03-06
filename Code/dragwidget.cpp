#include <QtWidgets>

#include "dragwidget.h"
#include "basemoveableobjects.h"
#include "iostream"


static QString hotSpotMimeDataKey() { return QStringLiteral("application/x-hotspot"); }
//! [0]
DragWidget::DragWidget(QColor color, QString location, QWidget *parent)
    : QFrame(parent)
{
    int size = 200;
    setMinimumSize(size, size);
    setMaximumSize(size, size);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    size /=3;
    QString temp = location;
    temp.append(QString("village.png"));
    QString vil= temp;
    QLabel *village = new BaseMoveableObjects(this,color, vil,size, 1);
    village->move(0, 0);
    village->show();
    village->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("city.png");
    QString city= temp;
    QLabel *stad = new BaseMoveableObjects(this,color, city,size, 2);
    stad->move(size, 0);
    stad->show();
    stad->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("metropool.png");
    QString metropool= temp;
    QLabel *netropol = new BaseMoveableObjects(this,color, metropool,size, 4);
    netropol->move(2*size, 0);
    netropol->show();
    netropol->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("knight1.png");
    QString k1= temp;
    QLabel *knight1 = new BaseMoveableObjects(this,color, k1,size, 0);
    knight1->move(0, size);
    knight1->show();
    knight1->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("knight2.png");
    QString k2= temp;
    QLabel *knight2 = new BaseMoveableObjects(this,color, k2,size, 0);
    knight2->move(size, size);
    knight2->show();
    knight2->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("knight3.png");
    QString k3= temp;
    QLabel *knight3 = new BaseMoveableObjects(this,color, k3,size, 0);
    knight3->move(2*size, size);
    knight3->show();
    knight3->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("road.png");
    QString road= temp;
    QLabel *weg = new BaseMoveableObjects(this,color, road,size/2, 0);
    weg->move(0, 2*size);
    weg->show();
    weg->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("helmet.png");
    QString helmet= temp;
    QLabel *helm = new BaseMoveableObjects(this,color, helmet,size/2, 0);
    helm->move(size, 2*size);
    helm->show();
    helm->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("wall.jpeg");
    QString wall= temp;
    QLabel *muur = new BaseMoveableObjects(this,color, wall,size+15, 0);
    muur->move(2*size, 2*size);
    muur->show();
    muur->setAttribute(Qt::WA_DeleteOnClose);
}
//! [0]

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
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

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
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

void DragWidget::dropEvent(QDropEvent *event)
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

        if (event->source() == this) {
            //event->setDropAction(Qt::MoveAction);
            //event->accept();
            //newIcon->show();
            //newIcon->setAttribute(Qt::WA_DeleteOnClose);
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

//! [1]
void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

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

    //QPixmap tempPixmap = pixmap;
    //QPainter painter;
    //painter.begin(&tempPixmap);
    //painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    //painter.end();

    //child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
