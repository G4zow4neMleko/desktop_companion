#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{

}

//void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    auto it = this->itemAt(event->scenePos(), QTransform());
//    if(it != mouseGrabberItem())
//        it->grabMouse();
//    this->sendEvent(it, event);
//    //QTextStream(stdout) << event->scenePos().x() << " " << event->scenePos().y() << " " << it->pos().x() << " " << it->pos().y() <<"\n";
//}

//void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    this->sendEvent(mouseGrabberItem(), event);
//    mouseGrabberItem()->ungrabMouse();
//}
