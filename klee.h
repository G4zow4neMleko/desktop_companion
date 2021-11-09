#ifndef KLEE_H
#define KLEE_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

class Klee : public QObject , public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Klee();

signals:

};

#endif // KLEE_H
