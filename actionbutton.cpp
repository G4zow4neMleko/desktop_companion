#include "actionbutton.h"

ActionButton::ActionButton(QScreen *Screen) : QObject(), QGraphicsItem()
{
    screen = Screen;
    screen_width = Screen->geometry().width();
    screen_height = Screen->geometry().height();
    pos_x = 100;
    pos_y = 100;
    width = 50;
    height = 50;
    color = Qt::red;

    timer_update = new QTimer();
    connect(timer_update, &QTimer::timeout, this, &ActionButton::Update);
    timer_update->start(10);

    timer_drag = new QTimer();
    connect(timer_drag, &QTimer::timeout, this, &ActionButton::SetDragTrue);
    timer_drag->setSingleShot(true);

//    timer_debug = new QTimer();
//    connect(timer_debug, &QTimer::timeout, this, &ActionButton::DebugT);
//    timer_debug->start(200);

}

QRectF ActionButton::boundingRect() const
{
    return QRectF(0,0,width,height);
};

void ActionButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setPos(pos_x,pos_y);
    painter->setBrush(color);
    painter->setPen(QPen(Qt::black, brush_thickness));
    painter->drawEllipse(0,0,width,height);
    painter->setPen(QPen(Qt::white, 3));
    painter->drawLine(10, height/2, width-10, height/2);
    painter->drawLine(width/2, 10, width/2, height-10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
};

void ActionButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!option_container)
    {
        option_container = new optionsContainer(this, screen);
        scene()->addItem(option_container);
    }

    timer_drag->start(750);

    Q_UNUSED(event);
};

void ActionButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if( option_container->isVisible() && !draggable)
        option_container->setVisible(false);
    else if(!option_container->isVisible() && draggable)
        option_container->setVisible(false);
    else
        option_container->setVisible(true);

    timer_drag->stop();
    draggable = false;
    brush_thickness = 1;
    Q_UNUSED(event);
}

void ActionButton::Update()
{
    if(draggable)
    {
        brush_thickness = 3;
        pos_x = cursor().pos().x()- width/2 +2;
        pos_y = cursor().pos().y()- height/2 +4;
    }

    if(pos_x+width > screen_width)
        pos_x = screen_width-width;
    else if(pos_x < 0)
        pos_x = 0;

    if(pos_y+height > screen_height)
        pos_y = screen_height-height;
    else if(pos_y < 0)
        pos_y = 0;


    this->update(boundingRect());
}

void ActionButton::DebugT()
{
    QTextStream(stdout) << boundingRect().width() << "\n";
}

void ActionButton::SetDragTrue()
{
    if(!draggable)
        draggable = true;
}

