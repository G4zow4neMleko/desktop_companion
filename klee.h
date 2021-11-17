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

class Klee : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Klee(QScreen *screen);

signals:

private slots:
    void nextFrame();
    void Blink();
    void Decision();
    void Update();

private:

    int frame_current;
    int pos_x;
    int pos_y;
    int blink;
    int decision;
    int frame_delay;
    int screen_width;
    int screen_height;
    QRandomGenerator rng_core;

    QTimer *timer_frame;
    QTimer *timer_blink;
    QTimer *timer_decision;
    QTimer *timer_update;
    QMap<QString,QVector<QPixmap>> animation_map;
    QString current_sheet;
    QString direction;
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // KLEE_H
