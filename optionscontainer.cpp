#include "optionscontainer.h"

optionsContainer::optionsContainer(QGraphicsItem *parent) : QObject(), QGraphicsItem()
{
    height = 250;
    width = 150;
    setVisible(false);
    setPos(parent->pos().x()+parent->boundingRect().width()/2, parent->pos().y()+parent->boundingRect().height()/2);

    options.append(new option(this,"dzieki"));
    options.append(new option(this,"dziala"));
    options.append(new option(this,"alaizd"));

    for(auto &x: options)
    {
        x->setPos(2,(x->boundingRect().height()+5) * options.indexOf(x) +5);
    }
}

//void optionsContainer::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//    for(auto &x: options)
//        scene()->sendEvent(x, event);
//}

//void optionsContainer::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
//{
//    for(auto &x: options)
//        scene()->sendEvent(x, event);
//}

QRectF optionsContainer::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void optionsContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawRect(0,0,width,height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
