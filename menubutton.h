#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QObject>
#include <QGraphicsEllipseItem>

class MenuButton : public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit MenuButton();


private slots:
    void Update();


private:
    //void paint2(QPainter *painter2, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QGraphicsEllipseItem *circle;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MENUBUTTON_H
