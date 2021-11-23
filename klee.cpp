#include "klee.h"
#include <QDir>

Klee::Klee(QScreen *screen):QObject(), QGraphicsItem()
{
    blink = 1;
    frame_current = 0;
    frame_delay = 200;
    current_sheet = "klee_idle";
    direction = "front";
    decision = 0;
    draggable = false;
    main_screen = screen;
    pos_x = screen->geometry().width()-600;
    pos_y = screen->geometry().height()-86-37;
    screen_width = screen->geometry().width();
    screen_height = screen->geometry().height();
    rng_core = QRandomGenerator().global()->generate();


    QDir directory(":/sprites");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);

    foreach(QString filename, images) {
        QVector<QPixmap> *frames = new QVector<QPixmap>;
        QPixmap QPixmap(":/sprites/"+filename);

        for(int i=0; i< (QPixmap.size().width()/64); ++i)
            (*frames).append(QPixmap.copy(i*64,0,64,86));

        filename.chop(4);
        animation_map.insert(filename, *frames);
        QTextStream(stdout) << filename+"\n";
    }

    timer_update = new QTimer();
    connect(timer_update, &QTimer::timeout, this, &Klee::Update);
    timer_update->start(25);

    timer_frame = new QTimer();
    connect(timer_frame, &QTimer::timeout, this, &Klee::nextFrame);
    timer_frame->start(frame_delay);

    timer_blink = new QTimer();
    connect(timer_blink, &QTimer::timeout, this, &Klee::Blink);
    timer_blink->start(4000);

    timer_decision = new QTimer();
    connect(timer_decision, &QTimer::timeout, this, &Klee::Decision);
    timer_decision->start(2300);

};


QRectF Klee::boundingRect() const
{
    return QRectF(0,0,screen_width,screen_height);
};

void Klee::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(direction == "right")
        painter->drawPixmap(pos_x,pos_y, animation_map[current_sheet][frame_current].transformed(QTransform().scale(-1,1)));
    else
        painter->drawPixmap(pos_x,pos_y, animation_map[current_sheet][frame_current]);

    Q_UNUSED(option);
    Q_UNUSED(widget);
};

void Klee::nextFrame()
{
    frame_current = (frame_current+1) % (animation_map[current_sheet].length() - (1*blink));
    if(blink == 0 && frame_current == (animation_map[current_sheet].length()-1) )
    {
       blink = 1;
    }
};

void Klee::Blink()
{
    if(current_sheet == "klee_catch_walk" || current_sheet == "klee_walk" || current_sheet == "klee_idle" || current_sheet == "klee_throw")
        blink = 0;
};

void Klee::Decision()
{
    switch(decision)
    {
    case 0:
        current_sheet = "klee_idle";
        direction = "front";
        timer_frame->stop();
        nextFrame();
        frame_delay = 200;
        timer_frame->start(frame_delay);
        break;
    case 1:
        current_sheet = "klee_walk";
        direction = "right";
        timer_frame->stop();
        nextFrame();
        frame_delay = 60;
        timer_frame->start(frame_delay);
        break;
    case 2:
        current_sheet = "klee_walk";
        direction = "left";
        timer_frame->stop();
        nextFrame();
        frame_delay = 60;
        timer_frame->start(frame_delay);
        break;
    }
    decision = rng_core.bounded(3);
};

void Klee::Update()
{
    if(current_sheet == "klee_walk" && direction == "left")
    {
        if(pos_x > 0)
            pos_x -= 2;
        else
        {
            decision = 1;
            Decision();
            //QTextStream(stdout) << "hit wall";
        }
    }
    else if(current_sheet == "klee_walk" && direction == "right")
    {
        if(pos_x < (screen_width-64))
            pos_x += 2;
        else
        {
            decision = 2;
            Decision();
            //QTextStream(stdout) << "hit wall";
        }
    }
    else if(draggable) //&& current_sheet == "klee_throw"
    {
        direction_vector[0] = static_cast<int>((cursor().pos().x() - 20 - pos_x - 20)/5);
        direction_vector[1] = static_cast<int>((cursor().pos().y() - 32 - pos_y - 32)/5);
        pos_x += direction_vector[0];
        pos_y += direction_vector[1];
    }
    else if(!draggable && sqrt(direction_vector[0]*direction_vector[0]+direction_vector[1]*direction_vector[1])>1)
    {
        pos_x += direction_vector[0]/2;
        pos_y += direction_vector[1]/2;
        if(pos_x > screen_width)
            direction_vector[0] *= -1;
        else if(pos_x < 0)
            direction_vector[0] *= -1;
        if(pos_y > (screen_height - 86-37))
            direction_vector[1] *= -0.5;
        direction_vector[1] += 9.81/2;
        direction_vector[0] /= 1.01;
        //QTextStream(stdout) << pos_x << " " << pos_y << "\n";
    }
    else if(!draggable && sqrt(direction_vector[0]*direction_vector[0]+direction_vector[1]*direction_vector[1])<1
            && pos_y<(screen_height-84) && pos_y > (screen_height - 170)
            && current_sheet == "klee_throw")
    {
        current_sheet = "klee_idle";
        timer_decision->start(2300);
        Decision();
    }

    this->update(boundingRect());
};

void Klee::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        draggable = true;
        current_sheet = "klee_throw";
        timer_decision->stop();
        nextFrame();
        QTextStream(stdout) << "mouse click!\n";
    }
};

void Klee::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        draggable = false;
        QTextStream(stdout) << "mouse release!\n";
    }
};
