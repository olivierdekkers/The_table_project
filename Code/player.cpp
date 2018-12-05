#include "player.h"

Player::Player(QColor new_color, int fieldWidth, int fieldHeight)
{
    color = new_color;
    width = fieldWidth;
    height = fieldHeight;
    next_player = this;
}
Player::Player(QColor new_color, int fieldWidth, int fieldHeight, Player *nextPlayer){
    color = new_color;
    width = fieldWidth;
    height = fieldHeight;
    next_player = nextPlayer;
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
    return next_player;
}

void Player::paint(QPainter *painter)
{
  painter->setBrush(color);
  QRadialGradient radialGradient(QPointF(width/4,height/2),height);
  radialGradient.setColorAt(0,Qt::white);
  radialGradient.setColorAt(0.25,Qt::white);
  radialGradient.setColorAt(1,color);
  QRect rect(0,0,width,height);
  painter->fillRect(rect,radialGradient);
}
