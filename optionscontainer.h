#ifndef OPTIONSCONTAINER_H
#define OPTIONSCONTAINER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QVector>
#include <QGraphicsScene>
#include "option.h"
#include <QGraphicsSceneEvent>

class optionsContainer : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit optionsContainer(QGraphicsItem *parent = nullptr);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:

private:
    int width;
    int height;
    QVector<QGraphicsItem*> options;

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // OPTIONSCONTAINER_H
