#ifndef KLEE_H
#define KLEE_H

#include <QMap>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QScreen>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <windows.h>
#include <commctrl.h>
#include <QPoint>
#include <QGraphicsScene>
#include <QDir>
#include "food.h"
#include "hand.h"
#include "curtain.h"

class Klee : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Klee(QScreen *screen);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

private slots:
    void nextFrame();
    void Blink();
    void Decision();
    void Update();
    void DebugT();
    void DespawnFood();
    void DespawnHand();
    void DespawnCurtain();

public slots:
    void OptionClicked(QString text);

private:
    int width;
    int height;
    int frame_current;
    int pos_x;
    int pos_y;
    int blink;
    int decision;
    int frame_delay;
    int screen_width;
    int screen_height;
    int skin_iterator;
    int skin_num;
    float direction_vector[2] = {0.0,0.0};
    bool draggable;
    bool in_action;
    QScreen *main_screen;
    QRandomGenerator rng_core;

    HWND hd;
    HANDLE he;
    DWORD Pi;

    QTimer *timer_frame;
    QTimer *timer_blink;
    QTimer *timer_decision;
    QTimer *timer_update;
    QTimer *timer_debug;
    QTimer *timer_food;
    QTimer *timer_pet;
    QTimer *timer_curtain;
    Food *food = nullptr;
    Hand *hand = nullptr;
    Curtain *curtain = nullptr;
    QMap<QString,QVector<QPixmap>> animation_map;
    QString current_sheet;
    QString direction;
    QRectF boundingRect() const;
    void Feed();
    void Pet();
    void SkinChange();
    void LoadSkins();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // KLEE_H
