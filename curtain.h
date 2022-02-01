#ifndef CURTAIN_H
#define CURTAIN_H

#include <QObject>
#include <QRandomGenerator>
#include <QVector>
#include <QPixmap>
#include <QGraphicsItem>
#include <QDir>
#include <QPainter>

class Curtain : public QObject , public QGraphicsItem
{

    Q_OBJECT

public:
    explicit Curtain(QGraphicsItem *parent = nullptr);

private:
    int pos_x;
    int pos_y;
    int width;
    int height;
    QPixmap curatin_pixmap;
    QRectF boundingRect() const;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CURTAIN_H
