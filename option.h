#ifndef OPTION_H
#define OPTION_H

#include <QObject>
#include <QGraphicsItem>
#include "optionscontainer.h"
#include <QString>
#include <QPainter>
#include <QFont>
#include <QGraphicsSceneEvent>
#include <QMouseEvent>

class option : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit option(QGraphicsItem *parent = nullptr, QString t = "");
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseReleaseEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneHoverEvent *event);

signals:

private:
    int width;
    int height;
    QString text;
    enum Qt::GlobalColor color;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // OPTION_H
