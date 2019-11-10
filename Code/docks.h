#ifndef DOCKS_H
#define DOCKS_H

#include <QLabel>
#include <QGraphicsItem>
#include <QPixmap>
#include <clickwidget.h>
#include <QPainter>
#include <QMouseEvent>
#include <playingfield.h>


class Docks: public QLabel
{
    Q_OBJECT
public:
    explicit Docks(int size, PlayingField *parent, ClickWidget *widg):QLabel(parent),size(size),widget(widg),parent(parent){
        widget = widg;
      //QObject::connect(widget, SIGNAL(yourSignal(QPixmap)),this, SLOT(slotFunc(QPixmap)));
      pix= QPixmap(200/3*2,200/3*2);
      pix.fill(Qt::transparent);
      setPixmap(pix);
      collll = QColor(0,0,0);
      prevpix = pix;
}
    ~Docks(){}
    int size;
    QPixmap pix;
    QPixmap prevpix;
    ClickWidget *widget;
    QColor collll;

    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::RightButton){
            widget = parent->players->widget;
            QObject::connect(widget, SIGNAL(yourSignal(QPixmap, int)),this, SLOT(slotFunc(QPixmap, int)));
            widget->setVisible(true);
            widget->show();
            QPoint x = QCursor::pos();
            widget->move(x.x()-widget->size().width()/2,x.y()-widget->size().height()/2 );
        }
    }
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        if(parent->players->color != collll && collll != QColor(0,0,0)){
            setPixmap(prevpix);
        }
        else{
            widget = parent->players->widget;
            QObject::connect(widget, SIGNAL(yourSignal(QPixmap, int)),this, SLOT(slotFunc(QPixmap, int)));
            QPoint x = QCursor::pos();
            widget->move(x.x()-widget->size().width()/2,x.y()-widget->size().height()/2 );
            widget->setVisible(true);
            widget->setParent(parent);
            widget->show();
        }
    }
    PlayingField *parent;
public slots:
    void slotFunc(QPixmap map, int val){
        QPixmap result(*this->pixmap());
        collll = parent->players->color;
        prevpix = this->pixmap()->copy(0,0,this->pixmap()->width(), this->pixmap()->height());
        if (val != 3){
            parent->players->score += val;
            QPainter painter(&result);
            QRectF target(pix.width()/2-map.width()/2,pix.height()/2-map.height()/2,map.width(),map.height());
            QRectF SourceRect(0,0,map.width(),map.height());
            painter.drawPixmap(target,map,SourceRect);
    }
        else{
            result = QPixmap(this->pixmap()->width(), this->pixmap()->height());
            result.fill(Qt::transparent);
        }
        setPixmap(result);
        QObject::disconnect(widget, SIGNAL(yourSignal(QPixmap, int)),this, SLOT(slotFunc(QPixmap, int)));
        this->show();
        /*
        setPixmap(map);
        pixmap = map;
        QObject::disconnect(widget, SIGNAL(yourSignal(QPixmap)),this, SLOT(slotFunc(QPixmap)));
        this->show();
        */
    }
    void slotSetWidget(ClickWidget *clickwidget){
        widget = clickwidget;
          QObject::connect(widget, SIGNAL(yourSignal(QPixmap, int)),this, SLOT(slotFunc(QPixmap, int)));
    }
};

#endif // DOCKS_H
