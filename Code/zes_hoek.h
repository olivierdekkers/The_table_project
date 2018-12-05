#ifndef ZES_HOEK_H
#define ZES_HOEK_H

#include <QGraphicsItem>
#include "field_number.h"

//! [0]
class ZesHoek
{
public:
    ZesHoek();
    ZesHoek(double size);
    ZesHoek(double size, std::vector<int> &possible_fiels, int *len);
    ZesHoek(double size, std::vector<int> &possible_fiels, int *len, int xCoord, int yCoord);
    ZesHoek(ZesHoek &p2);
    ZesHoek(QPoint p1, int corner, ZesHoek &zeshoek);
    ZesHoek(QPoint p1 , int corner, ZesHoek &p2, std::vector<int> &possible_fiels, int *len);
    void set_size(double new_size);
    void setPos(int x, int y);
    void set_rand_color();
    int get_XCoord();
    int get_YCoord();
    int calc_width();
    int calc_heigth();
    double get_size();

    void paint(QPainter *painter);

    QPoint points[6];
    int field_type;
    fieldNumber nummer;
private:
    QColor color;
    int Center_XCoord;
    int Center_YCoord;
    double size;
    void calc_points(void);
};
//! [0]

#endif // ZES_HOEK_H
