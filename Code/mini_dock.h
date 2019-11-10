#ifndef MINI_DOCKS_H
#define MINI_DOCKS_H

#include <QLabel>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <playingfield.h>


class Mini_dock: public QLabel
{
    Q_OBJECT
public:
    explicit Mini_dock(int size, PlayingField *parent):QLabel(parent),size(size),parent(parent){
      //QObject::connect(widget, SIGNAL(yourSignal(QPixmap)),this, SLOT(slotFunc(QPixmap)));
      pix= QPixmap(200/6,200/6);
      pix.fill(Qt::transparent);
      setPixmap(pix);
}
    ~Mini_dock(){}
    int size;
    QPixmap pix;

    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::RightButton){
              pix= QPixmap(200/6,200/6);
              pix.fill(Qt::transparent);
              setPixmap(pix);
        }
    }
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
            QPixmap map = *parent->players->widget->weg->pixmap();
            QPixmap result(*this->pixmap());
            QPainter painter(&result);
            QRectF target(pix.width()/2-map.width()/2,pix.height()/2-map.height()/2,map.width(),map.height());
            QRectF SourceRect(0,0,map.width(),map.height());
            painter.drawPixmap(target,map,SourceRect);
            setPixmap(result);
            this->show();
    }
    PlayingField *parent;
};

#endif // MINI_DOCKS_H
