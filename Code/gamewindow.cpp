#include "gamewindow.h"

#include <QtWidgets>
#include "playingfield.h"
#include <iostream>
#include "dragwidget.h"
#include "QString"
#include "baseGamewidget.h"
#include "movablefieldsnumber.h"

GameWindow::GameWindow()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    int width = rec.width();
    int height = rec.height()-50;
    setWindowTitle(tr("Colonisten"));
    resize(width, height);
    width = this->width();
    height = this->height();
    QColor pink = QColor(249,197,216);
    QColor blue = QColor (106,142,226);
    QColor red = QColor (23,227,101);
    QColor strakke = QColor (23,227,217);
    Player *player = new Player(blue,width*2,height,QString("/home/olivier/Pictures/socPictures/socLewisSr/"));
    player->add_player(new   Player(pink,width*2,height,player,QString("/home/olivier/Pictures/socPictures/socPlatte/")));
    player->add_player(new Player(red,width*2,height,player,QString("/home/olivier/Pictures/socPictures/socVincent/")));
    //player->add_player(new Player(strakke,width*2,height,player,QString("/home/olivier/Pictures/socPictures/socStrakke/")));
    board = new PlayingField(width, height, player);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board,0,0,3,3);
    //layout->addWidget(new DragWidget(pink,QString("/home/olivier/Pictures/socPictures/socPlatte/")),0,0,1,1);
    //layout->addWidget(new DragWidget(blue,QString("/home/olivier/Pictures/socPictures/socLewisSr/")),0,2,1,1);
    //layout->addWidget(new DragWidget(red,QString("/home/olivier/Pictures/socPictures/socVincent/")),2,2,1,1);
    //layout->addWidget(new DragWidget(strakke,QString("/home/olivier/Pictures/socPictures/socStrakke/")),2,0,1,1);

    //layout->addWidget(new DragWidget(QColor(255,105,180),QString("/home/olivier/Pictures/socPictures/socLewisSr/")),2,0,1,1);
    //layout->addWidget(new BaseGameWidget(QColor(0,0,0),QString("/home/olivier/Pictures/socPictures/socGame/")),0,1,1,1);
    setLayout(layout);
}

/*void GameWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        board->next();
    }
}
*/
