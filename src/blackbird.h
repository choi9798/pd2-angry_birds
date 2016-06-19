#ifndef BLACKBIRD_H
#define BLACKBIRD_H

#include <bird.h>

class Blackbird : public Bird
{
public:
    Blackbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void ability();
};

#endif // BLACKBIRD_H
