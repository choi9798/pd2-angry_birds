#ifndef OB_H
#define OB_H


#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BLOCK_DENSITY 15.0f
#define BLOCK_FRICTION 0.8f
#define BLOCK_RESTITUTION 0.3f

class Ob : public GameItem
{
    public:
        Ob(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // OB_H
