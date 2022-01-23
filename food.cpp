#include "food.h"

Food::Food(QGraphicsItem *parent, QRandomGenerator *core)
{
    setParentItem(parent);
    rng_core = core;
    width = 24;
    height = 20;
    pos_x = parent->boundingRect().width()/2 - width/2;
    pos_y = parent->boundingRect().height()/2 - height/2 + 4;
    setPos(pos_x,pos_y);

    QDir directory(":/sprites/food/");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);

    foreach(QString filename, images)
        food_type.append(QPixmap(":/sprites/food/"+filename));

    food_num = rng_core->bounded(food_type.length());

}

void Food::changeFood()
{
    food_num = rng_core->bounded(food_type.length());
}

QRectF Food::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     painter->drawPixmap(0,0, food_type[food_num]);
     Q_UNUSED(option);
     Q_UNUSED(widget);
}
