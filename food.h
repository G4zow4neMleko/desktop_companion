#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QRandomGenerator>
#include <QVector>
#include <QPixmap>
#include <QGraphicsItem>
#include <QDir>
#include <QPainter>

class Food : public QObject , public QGraphicsItem
{

    Q_OBJECT

public:
    explicit Food(QGraphicsItem *parent = nullptr, QRandomGenerator *core = nullptr);
    void changeFood();

private:
    int pos_x;
    int pos_y;
    int food_num;
    int width;
    int height;
    QVector<QPixmap> food_type;
    QRandomGenerator *rng_core;
    QRectF boundingRect() const;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // FOOD_H
