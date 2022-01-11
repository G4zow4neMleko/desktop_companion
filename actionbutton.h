#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QScreen>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QTimer>
#include "optionscontainer.h"
#include <QGraphicsScene>

class ActionButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ActionButton(QScreen *screen);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


signals:


private slots:
    void Update();
    void DebugT();
    void SetDragTrue();

private:
    int pos_x;
    int pos_y;
    int brush_thickness = 1;
    int screen_width;
    int screen_height;
    bool draggable = false;
    int width;
    int height;

    optionsContainer* option_container = nullptr;
    QTimer* timer_update;
    QTimer* timer_drag;
    QTimer* timer_debug;

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ACTIONBUTTON_H