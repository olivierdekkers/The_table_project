#include "player.h"

Player::Player(QColor new_color, int fieldWidth, int fieldHeight, QString location)
{
    widget = new ClickWidget(new_color,location);
    color = new_color;
    width = fieldWidth;
    height = fieldHeight;
    next_player = this;
    score = 3;
}
Player::Player(QColor new_color, int fieldWidth, int fieldHeight, Player *nextPlayer, QString location){
    widget = new ClickWidget(new_color,location);
    color = new_color;
    width = fieldWidth;
    height = fieldHeight;
    next_player = nextPlayer;
    score = 3;
}

bool Player::operator ==( const Player& reference) const {
    return  (this->color == reference.color);
}

void Player::add_player(Player *new_player){
    if (*next_player == *(new_player->next_player)){
        next_player = new_player;
    }
    else{
        next_player->add_player(new_player);
    }
}

Player* Player::getNextPlayer(void){
    widget->close();
    emit signalClickWidget(next_player->widget);
    //next_player->widget = new ClickWidget(next_player->widget);
    return next_player;
}

void Player::paint(QPainter *painter)
{
  painter->setBrush(Qt::white);
  QRadialGradient radialGradient(QPointF(width/4,height/2),height);
  radialGradient.setColorAt(0,color);
  radialGradient.setColorAt(0.25,color);
  radialGradient.setColorAt(0.5,color);
  radialGradient.setColorAt(1,Qt::white);
  QRect rect(0,0,width,height);
  painter->fillRect(rect,radialGradient);
}

void Player::counterConnect(int increase){
    std::cout << 3 << std::endl;
    this->score += increase;
    std::cout << this->score << std::endl;
}
