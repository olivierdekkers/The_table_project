#include <QtWidgets>

#include <math.h>

#include "player.h"
#include <QApplication>
#include "gamewindow.h"
QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
QT_END_NAMESPACE

//! [0]
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    GameWindow window;
    window.show();
//! [0]

//! [1]
    // QGraphicsScene scene;
    // scene.setSceneRect(-100, -100, 200, 200);
//! [1]
//! [2]
    // scene.setItemIndexMethod(QGraphicsScene::NoIndex);
//! [2]

//! [3]
//!

    //QGraphicsView view(&scene);
    //view.setRenderHint(QPainter::Antialiasing);
    //view.setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
//! //[4] //! [5]
    //view.setCacheMode(QGraphicsView::CacheBackground);
    //view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view.setDragMode(QGraphicsView::ScrollHandDrag);
//! //[5] //! [6]
    //view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Test"));
    //view.resize(400, 300);
    //view.show();

    //QTimer timer;
    //QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    //timer.start(1000 / 33);

    return app.exec();
}
//! [6]
