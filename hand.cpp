#include "hand.h"

Hand::Hand(QGraphicsItem *parent) : QObject(), QGraphicsItem()
{
    setParentItem(parent);
    height = 32;
    width = 32;
    frame_current = 0;
    pos_x = 20;
    pos_y = -5;
    setPos(pos_x,pos_y);

    QPixmap QPixmap(":/sprites/hand/hand.png");

    for(int i=0; i< (QPixmap.size().width()/width); ++i)
        frames.append(QPixmap.copy(i*width,0,width,height));


    timer_frame = new QTimer();
    connect(timer_frame, &QTimer::timeout, this, &Hand::nextFrame);
    timer_frame->start(120);

}

void Hand::nextFrame()
{
    frame_current = (frame_current+1) % (frames.length());
}

QRectF Hand::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void Hand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, frames[frame_current]);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
