#include "optionscontainer.h"

optionsContainer::optionsContainer(QGraphicsItem *parent, QScreen *Screen) : QObject(), QGraphicsItem()
{
    screen_width = Screen->geometry().width();
    screen_height = Screen->geometry().height();
    width = 150;
    setVisible(false);
    setParentItem(parent);
    setPos(parent->boundingRect().width()/2 + 2,parent->boundingRect().height()/2 + 2);

    timer_update = new QTimer();
    connect(timer_update, &QTimer::timeout, this, &optionsContainer::Update);
    timer_update->start(25);

    options.append(new option(this,"feed"));
    connect(options.back(), &option::clicked,this,&optionsContainer::OptionClickedEmit);
    options.append(new option(this,"f"));
    options.append(new option(this,"f"));
    options.append(new option(this,"f"));
    options.append(new option(this,"EXIT"));
    connect(options.back(), &option::clicked,options.back(),[]()
    {
        QCoreApplication::quit();
    });

    for(auto &x: options)
    {
        x->setPos(2,(x->boundingRect().height()+5) * options.indexOf(x) +5);
    }

    height = (options[0]->boundingRect().height()+5) * options.size() +5;
}

void optionsContainer::Update()
{
    if( (parentItem()->pos().x() + parentItem()->boundingRect().width()/2 + width + 2) > screen_width)
        setPos(parentItem()->boundingRect().width()/2 - 2 - width, pos().y());
    else
        setPos(parentItem()->boundingRect().width()/2 + 2, pos().y());

    if( (parentItem()->pos().y() + parentItem()->boundingRect().height()/2 + height + 2) > screen_height)
        setPos(pos().x(), parentItem()->boundingRect().height()/2 - 2 - height);
    else
        setPos(pos().x(), parentItem()->boundingRect().height()/2 + 2);
}

void optionsContainer::OptionClickedEmit()
{
    emit OptionClicked();
}

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

