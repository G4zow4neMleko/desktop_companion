#ifndef OPTIONSCONTAINER_H
#define OPTIONSCONTAINER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QVector>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QTimer>
#include <QScreen>
#include <QDialog>
#include "option.h"

class optionsContainer : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit optionsContainer(QGraphicsItem *parent = nullptr, QScreen *Screen = nullptr);


private slots:
    void Update();
    void OptionClickedEmit(QString text);


signals:
    void OptionClicked(QString text);

private:
    int width;
    int height;
    int screen_width;
    int screen_height;

    QVector<option*> options;
    QTimer* timer_update;


    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // OPTIONSCONTAINER_H
