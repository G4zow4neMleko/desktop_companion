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

public slots:
    void Feed();

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
    float direction_vector[2] = {0.0,0.0};
    bool draggable;
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
    QMap<QString,QVector<QPixmap>> animation_map;
    QString current_sheet;
    QString direction;
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // KLEE_H
