#ifndef BASEGAMEWIDGET_H
#define BASEGAMEWIDGET_H

#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

//! [0]
class BaseGameWidget : public QFrame
{
public:
    explicit BaseGameWidget(QColor colorQWidget,QString map, QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};
//! [0]

#endif // BASEGAMEWIDGET_H
