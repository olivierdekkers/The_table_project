#include "gamewindow.h"

#include <QtWidgets>
#include "playingfield.h"
#include <iostream>
#include "dragwidget.h"

GameWindow::GameWindow()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    int width = rec.width();
    int height = rec.height();
    setWindowTitle(tr("Colonisten"));
    resize(width, height);
    width = this->width();
    height = this->height();
    board = new PlayingField(width, height);
    Player *player = new   Player(QColor(0,255,0),width*2,height);
    player->add_player(new Player(QColor(255,0,0),width*2,height,player));
    player->add_player(new Player(QColor(0,0,255),width*2,height,player));
    player->add_player(new Player(QColor(255,105,180),width*2,height,player));
    board->add_players(player);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board,0,0,3,3);
    layout->addWidget(new DragWidget(QColor(0,255,0)),0,0,1,1);
    layout->addWidget(new DragWidget(QColor(255,0,0)),0,2,1,1);
    layout->addWidget(new DragWidget(QColor(0,0,255)),2,2,1,1);
    layout->addWidget(new DragWidget(QColor(255,105,180)),2,0,1,1);
    setLayout(layout);
}

/*void GameWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        board->next();
    }
}
*/
