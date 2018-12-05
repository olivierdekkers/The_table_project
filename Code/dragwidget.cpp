#include <QtWidgets>

#include "dragwidget.h"
#include "basemoveableobjects.h"


static QString hotSpotMimeDataKey() { return QStringLiteral("application/x-hotspot"); }
//! [0]
DragWidget::DragWidget(QColor color, QWidget *parent )
    : QFrame(parent)
{
    int size = 200;
    setMinimumSize(size, size);
    setMaximumSize(size, size);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    size /=3;
    QString vil= R"(/home/olivier/Pictures/village_platte.png)";
    QLabel *village = new BaseMoveableObjects(this,color, vil,size);
    village->move(0, 0);
    village->show();
    village->setAttribute(Qt::WA_DeleteOnClose);

    QString city= R"(/home/olivier/Pictures/city_platte.png)";
    QLabel *stad = new BaseMoveableObjects(this,color, city,size);
    stad->move(size, 0);
    stad->show();
    stad->setAttribute(Qt::WA_DeleteOnClose);

    QString metropool= R"(/home/olivier/Pictures/metropool_platte.png)";
    QLabel *netropol = new BaseMoveableObjects(this,color, metropool,size);
    netropol->move(2*size, 0);
    netropol->show();
    netropol->setAttribute(Qt::WA_DeleteOnClose);

    QString k1= R"(/home/olivier/Pictures/knight_1_platte.png)";
    QLabel *knight1 = new BaseMoveableObjects(this,color, k1,size);
    knight1->move(0, size);
    knight1->show();
    knight1->setAttribute(Qt::WA_DeleteOnClose);
    QString k2= R"(/home/olivier/Pictures/knight_2_platte.png)";
    QLabel *knight2 = new BaseMoveableObjects(this,color, k2,size);
    knight2->move(size, size);
    knight2->show();
    knight2->setAttribute(Qt::WA_DeleteOnClose);
    QString k3= R"(/home/olivier/Pictures/knight_3_platte.png)";
    QLabel *knight3 = new BaseMoveableObjects(this,color, k3,size);
    knight3->move(2*size, size);
    knight3->show();
    knight3->setAttribute(Qt::WA_DeleteOnClose);

    QString road= R"(/home/olivier/Pictures/weg_platte.png)";
    QLabel *weg = new BaseMoveableObjects(this,color, road,size);
    weg->move(0, 2*size);
    weg->show();
    weg->setAttribute(Qt::WA_DeleteOnClose);

    QString helmet= R"(/home/olivier/Pictures/helmet.jpg)";
    QLabel *helm = new BaseMoveableObjects(this,color, helmet,size/4);
    helm->move(size, 2*size);
    helm->show();
    helm->setAttribute(Qt::WA_DeleteOnClose);
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
