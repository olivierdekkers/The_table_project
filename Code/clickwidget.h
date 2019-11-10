#ifndef CLICKWIDGET_H
#define CLICKWIDGET_H

#include <QFrame>
#include <iostream>
#include <QLabel>
/*
QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE
*/

//! [0]
class ClickWidget : public QWidget
{
    Q_OBJECT
public:
    ClickWidget(QColor color, QString location, QWidget *parent = nullptr);
    ClickWidget(ClickWidget &widget);
    QLabel *weg;
signals:
    void yourSignal(QPixmap, int);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *closeEvent);
    QPainterPath shape(){
        QPainterPath path;
        path.addEllipse(0,0,216,216);
        QPainterPath inner;
        inner.addEllipse(108-54/2,108-54/2,108+54/2,108+54/2);
        path.subtracted(inner);

        return path;
    }
};
//! [0]

#endif // DRAGWIDGET_H
