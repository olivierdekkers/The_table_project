#include <QtWidgets>
#include "basemoveableobjects.h"


QRectF BaseMoveableObjects::boundingRect() const
{
    return QRectF(x - 30 - scale, y - 30 - scale,
                  30 + 3 * scale, 20 + 3 * scale);
}
