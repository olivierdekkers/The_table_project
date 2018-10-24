#ifndef RESOURCE_TYLE_H
#define RESOURCE_TYLE_H

#include "field_number.h"
#include "zes_hoek.h"

class resource_tyle
{
public:
    resource_tyle(int typeField, fieldNumber field_number, ZesHoek zeshoek);

private:
    ZesHoek field;
    int resource;
    fieldNumber field_number;

};

#endif // RESOURCE_TYLE_H
