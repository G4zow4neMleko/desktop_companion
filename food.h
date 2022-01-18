#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QRandomGenerator>
#include <QVector>
#include <QPixmap>
#include "klee.h"

class food : public QObject , public QGraphicsItem
{

    Q_OBJECT
public:
    explicit food(QGraphicsItem *parent = nullptr, QRandomGenerator *Core = nullptr);


private:
    int pos_x;
    int pos_y;
    int food_num;
    QVector<QPixmap> food_type;
    QRandomGenerator *core;
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // FOOD_H
