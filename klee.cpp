#include "klee.h"
#include <QDir>

Klee::Klee(QScreen *screen):QObject(), QGraphicsItem()
{
    blink = 1;
    frame_current = 0;
    frame_delay = 200;
    current_sheet = "klee_idle";
    pos_x = 1800;
    pos_y = screen->geometry().height()-86-37;
    rng_core = QRandomGenerator();


    QDir directory(":/sprites");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);

    foreach(QString filename, images) {
        QVector<QPixmap> *frames = new QVector<QPixmap>;
        QPixmap QPixmap(":/sprites/"+filename);

        for(int i=0; i< (QPixmap.size().width()/64); ++i)
            (*frames).append(QPixmap.copy(i*64,0,64,86));

        filename.chop(4);
        //QTextStream(stdout) << filename+"\n";
        animation_map.insert(filename, *frames);
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

//    timer_pos = new QTimer();
//    connect(timer_pos, &QTimer::timeout, this, &Klee::Pos_update);
//    timer_pos->start(2300);

};

QRectF Klee::boundingRect() const
{
    return QRectF(0,0,1920,1080);
};

void Klee::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QTextStream(stdout) << frame_current <<"\n";
    painter->drawPixmap(pos_x,pos_y, animation_map[current_sheet][frame_current]);
    QTextStream(stdout) << "n2\n";
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
    if(current_sheet == "klee_catch_walk" || current_sheet == "klee_walk" || current_sheet == "klee_idle")
        blink = 0;
};

void Klee::Decision()
{
    decision = QRandomGenerator::global()->bounded(3);
    switch(decision)
    {
    case 0:
        current_sheet = "klee_idle";
        timer_frame->stop();
        nextFrame();
        frame_delay = 200;
        timer_frame->start(frame_delay);
        break;
    case 1:
        current_sheet = "klee_walk";
        timer_frame->stop();
        nextFrame();
        frame_delay = 60;
        timer_frame->start(frame_delay);
        break;
    case 2:
        current_sheet = "klee_walk";
        timer_frame->stop();
        nextFrame();
        frame_delay = 60;
        timer_frame->start(frame_delay);
        break;
    }

    //QTextStream(stdout) << decision << "\n";
};

void Klee::Update()
{
    //QTextStream(stdout) << "update\n" << decision << "\n";
    if(current_sheet == "klee_walk")
        pos_x -= 2;
    this->update(boundingRect());
};
