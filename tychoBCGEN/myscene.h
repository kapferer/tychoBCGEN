#ifndef MYSCENE_H
#define MYSCENE_H

#include <QEvent>
#include <QGraphicsScene>

class myscene : public QGraphicsScene
{


public:

protected:
     void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // MYSCENE_H
