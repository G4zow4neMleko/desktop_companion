#include "food.h"

food::food(QGraphicsItem *parent, QRandomGenerator *Core)
{
    setParentItem(parent);
    core = Core;
    pos_x = 12;

}

QRectF food::boundingRect() const
{
    return QRectF(0,0,24,20);
}

void food::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     painter->drawPixmap(0,0, food_type[food_num]);
     Q_UNUSED(option);
     Q_UNUSED(widget);
}
