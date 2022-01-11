#ifndef OPTION_H
#define OPTION_H

#include <QObject>
#include <QGraphicsItem>
#include "optionscontainer.h"
#include <QString>
#include <QPainter>
#include <QFont>
#include <QMouseEvent>
#include <QWidget>

class option : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit option(QGraphicsItem *parent = nullptr, QString t = "");
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

private:
    int width;
    int height;
    QString text;
    QColor color;
    QRgb text_color;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // OPTION_H
