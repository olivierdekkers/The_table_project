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


void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->setBrush(color);

  painter->drawRect(-width/2,-height/2,width,height);
}
