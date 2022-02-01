#ifndef HAND_H
#define HAND_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDir>
#include <QTimer>
#include <QVector>

class Hand : public QObject , public QGraphicsItem
{
public:
    explicit Hand(QGraphicsItem *parent = nullptr);

private slots:
    void nextFrame();


private:
    int width;
    int height;
    int frame_current;
    int pos_x;
    int pos_y;
    QVector<QPixmap> frames;
    QRectF boundingRect() const;
    QTimer *timer_frame;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // HAND_H
