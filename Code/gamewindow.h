#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QFrame>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class PlayingField;

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow();

    PlayingField *board;
    QLabel *createLabel(const QString &text);
    QPushButton *nextButton;
};

#endif // GAMEWINDOW_H
