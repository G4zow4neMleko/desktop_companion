#include "klee.h"

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


    QDir directory(":/sprites/klee/");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);

    foreach(QString filename, images) {
        QVector<QPixmap> *frames = new QVector<QPixmap>;
        QPixmap QPixmap(":/sprites/klee/"+filename);

        for(int i=0; i< (QPixmap.size().width()/64); ++i)
            (*frames).append(QPixmap.copy(i*64,0,64,86));

        filename.chop(4);
        animation_map.insert(filename, *frames);
        //QTextStream(stdout) << filename+"\n";
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

//    timer_debug = new QTimer();
//    connect(timer_debug, &QTimer::timeout, this, &Klee::DebugT);
//    timer_debug->start(200);




//    hd = GetDesktopWindow();
//    hd = FindWindowA("Progman",NULL);
//    hd = FindWindowEx(hd, 0, L"SHELLDLL_DefView", NULL);
//    hd = FindWindowEx(hd, 0, L"SysListView32", NULL);

//    GetWindowThreadProcessId(hd, &Pi);
//    he = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false,Pi);

//    QTextStream(stdout) << "ilosc " << ListView_GetItemCount(hd) << "\n";

//    POINT *pC =  (POINT*) VirtualAllocEx(he,NULL,sizeof(POINT),MEM_COMMIT,PAGE_READWRITE);
//    WriteProcessMemory(he, pC, &pC, sizeof(POINT), NULL);

//    POINT pt;
//    ListView_GetItemPosition(hd,20,pC);
//    ReadProcessMemory(hd, pC, &pt, sizeof(POINT), NULL);
//    QTextStream(stdout) << pt.x << "  " << pt.y << "\n";


//    HWND tp;
//    tp = GetNextWindow(GetTopWindow(GetParent(FindWindowA("Progman",NULL))),2);
//    RECT rect;
//    GetWindowRect(tp,&rect);

//    QTextStream(stdout) << rect.right  << " " << rect.bottom << "\n";

    //for(int i=0; i<1000; ++i)
    //ListView_SetItemPosition(hd,0,200,200);

    //ReadProcessMemory(hd,pC,&pt,sizeof (POINT),NULL);
    //QTextStream(stdout) << pt.x << "  " << pt.y << "\n";

    //VirtualFreeEx(he,pC,0,MEM_RELEASE);
};


QRectF Klee::boundingRect() const
{
    return QRectF(0,0,65,86);
};

void Klee::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(direction == "right")
        painter->drawPixmap(0,0, animation_map[current_sheet][frame_current].transformed(QTransform().scale(-1,1)));
    else
        painter->drawPixmap(0,0, animation_map[current_sheet][frame_current]);

    Q_UNUSED(option);
    Q_UNUSED(widget);
};

void Klee::nextFrame()
{
    //HWND tp;
    //LPSTR lpString = nullptr;
    //tp = GetNextWindow(GetTopWindow(FindWindowA("Progman",NULL)),2);
//    tp = GetActiveWindow();
//    RECT rect;
//    GetWindowRect(tp,&rect);
    //HWND tp;
    //LPSTR lpString = nullptr;
    //tp = GetTopWindow(FindWindowA("Progman",NULL));
    //tp = GetActiveWindow();
    //RECT rect;
    //GetWindowRect(tp,&rect);

//    GetWindowTextA(tp,lpString,20);
//    QTextStream(stdout) << lpString << "\n";

//    WM_GETTEXT;
//    QTextStream(stdout) << lpString << "\n";

//    POINT pt;
//    ClientToScreen(tp,&pt);

    //QTextStream(stdout) << rect.right  << " " << rect.bottom << "\n";
    //QTextStream(stdout) << pt.x  << " " << pt.y << "\n";

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
   case 3:
        current_sheet = "klee_catch_walk";
        if(direction == "front")
            direction = "left";
        timer_frame->stop();
        nextFrame();
        frame_delay = 100;
        timer_frame->start(frame_delay);
        break;
    }
    decision = rng_core.bounded(4);
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
    else if(draggable)
    {
        direction_vector[0] = (cursor().pos().x() - 20 - pos_x - 20)/4;
        direction_vector[1] = (cursor().pos().y() - 22 - pos_y)/4;

        if(direction_vector[0] > 0)
            direction = "right";
        else if(direction_vector[0] < 0)
            direction = "left";

        pos_x += direction_vector[0];
        pos_y += direction_vector[1];
    }
    else if(!draggable && current_sheet == "klee_throw" )
    {
        pos_x += direction_vector[0]/2;
        pos_y += direction_vector[1]/2;\

        if(pos_x > (screen_width-64) )
        {
            direction_vector[0] *= -1;
            pos_x = screen_width-64;
        }

        else if(pos_x < 0)
        {
            direction_vector[0] *= -1;
            pos_x = 0;
        }

        if(direction_vector[0]>0)
            direction = "right";
        else
            direction = "left";

        if(pos_y > (screen_height - 86-37) && direction_vector[1]>0)
        {
            pos_y = screen_height - 86-37;
            direction_vector[1] *= -0.6;
            direction_vector[0] *= 0.93;
        }

        if(static_cast<int>(sqrt(direction_vector[0]*direction_vector[0] + direction_vector[1]*direction_vector[1])) <= 4
                && pos_y <= (screen_height-86-36) && pos_y >= (screen_height-86-38) )
        {
            direction_vector[0] = 0;
            direction_vector[1] = 0;
            pos_y = screen_height-86-37;
            timer_decision->start(2300);
            Decision();
        }

        direction_vector[1] += 9;
        direction_vector[0] /= 1.04;
    }
    else if(current_sheet == "klee_catch_walk")
    {
        if(cursor().pos().x() < (pos_x+32+100) && cursor().pos().x() > (pos_x+32-100)
                && cursor().pos().y() < (pos_y+43+100) && cursor().pos().y() > (pos_y+43-100))
        {
            nextFrame();
            if(direction == "left")
            {
                pos_x -= 5;
                cursor().setPos(pos_x+25,pos_y+43);
                if(pos_x<0)
                {
                    direction = "right";
                    pos_x = 0;
                    cursor().setPos(pos_x+32,pos_y+43);
                }
            }
            else
            {
                pos_x += 5;
                cursor().setPos(pos_x+32,pos_y+43);
                if( pos_x > (screen_width-64) )
                {
                    direction = "left";
                    pos_x = screen_width-64;
                    cursor().setPos(pos_x+25,pos_y+43);
                }
            }
        }
        else
        {
            Decision();
        };
    }

    this->setPos(pos_x,pos_y);
    this->update(boundingRect());
    this->scene()->update(this->scene()->sceneRect());
};

void Klee::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //auto it = scene()->itemAt(event->pos(), QTransform());
    //QTextStream(stdout) << "press: " << typeid(it).name() << "\n" << event->pos().x() << " " << event->pos().y() << "\n";
    if(event->button() == Qt::LeftButton)
    {
        draggable = true;
        current_sheet = "klee_throw";
        timer_decision->stop();
        nextFrame();
    }
};

void Klee::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        draggable = false;
    }
};

void Klee::DebugT()
{
    QTextStream(stdout) << "postac:  " << pos_x << " " << pos_y << "\n";
}
