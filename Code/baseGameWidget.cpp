#include <QtWidgets>

#include "baseGamewidget.h"
#include "basemoveableobjects.h"
#include "iostream"
#include "movablefieldsnumber.h"


static QString hotSpotMimeDataKey() { return QStringLiteral("application/x-hotspot"); }
//! [0]
BaseGameWidget::BaseGameWidget(QColor color, QString location, QWidget *parent)
    : QFrame(parent)
{
    int size = 200;
    setMinimumSize(size, size);
    setMaximumSize(size, size);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

    size /=3;
    QString temp = location;
    temp.append(QString("boat.png"));
    QString boot= temp;
    QLabel *boat = new BaseMoveableObjects(this,color, boot,size, 0);
    boat->move(0, 0);
    boat->show();
    boat->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("handelaar.png");
    QString handelaar= temp;
    QLabel *merchant = new BaseMoveableObjects(this,color, handelaar,size, 0);
    merchant->move(size, 0);
    merchant->show();
    merchant->setAttribute(Qt::WA_DeleteOnClose);

    temp = location;
    temp.append("vikings.png");
    QString struikrovers= temp;
    //QLabel *bandits = new BaseMoveableObjects(this,color, struikrovers,size);
    //bandits->move(2*size, 0);
    //bandits->show();
    //bandits->setAttribute(Qt::WA_DeleteOnClose);
      //QLabel *tamp = new movableFieldsNumber(this,size, 3,1, 1);
}
//! [0]

void BaseGameWidget::dragEnterEvent(QDragEnterEvent *event)
{
    //if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    //    if (event->source() == this) {
    //        event->setDropAction(Qt::MoveAction);
    //        event->accept();
    //    } else {
    //        event->acceptProposedAction();
    //    }
    //} else {
    //    event->ignore();
    //}
}

void BaseGameWidget::dragMoveEvent(QDragMoveEvent *event)
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

void BaseGameWidget::dropEvent(QDropEvent *event)
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
void BaseGameWidget::mousePressEvent(QMouseEvent *event)
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
