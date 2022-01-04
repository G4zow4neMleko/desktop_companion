#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTextStream>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

};

#endif // SCENE_H
