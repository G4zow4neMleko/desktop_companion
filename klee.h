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

    void move(QString direction);

signals:

private slots:
    void nextFrame();
    void Blink();
    void Decision();
    //void Pos_update();
    void Update();

private:

    int frame_current;
    int pos_x;
    int pos_y;
    int blink;
    int decision;
    int frame_delay;
    QRandomGenerator rng_core;

    QTimer *timer_frame;
    QTimer *timer_blink;
    QTimer *timer_decision;
    //QTimer *timer_pos;
    QTimer *timer_update;
    QMap<QString,QVector<QPixmap>> animation_map;
    QString current_sheet;
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // KLEE_H
