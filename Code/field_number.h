#ifndef ZES_HOEK_NUMBER_H
#define ZES_HOEK_NUMBER_H

#include <QGraphicsItem>

class fieldNumber
{
public:
    fieldNumber();
    fieldNumber(int value);
    int get_number(){
        return value;
    }

    void paint(QPainter *painter, int x_coordinate,int y_coordinate, int size);
private:
    int value;

};

#endif // ZES_HOEK_NUMBER_H
