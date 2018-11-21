#include "gamewindow.h"

#include <QtWidgets>
#include "playingfield.h"

GameWindow::GameWindow()
{
    board = new PlayingField();

    nextButton = new QPushButton(tr("&next player"));
    nextButton->setFocusPolicy(Qt::NoFocus);

    connect(nextButton, &QPushButton::clicked, board, &PlayingField::next);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board,0,0);
}
