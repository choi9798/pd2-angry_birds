#include <bluebird.h>

Bluebird::Bluebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{

}
void Bluebird::ability()
{
   b2Vec2 a=g_body->GetLinearVelocity();
   g_body->SetLinearVelocity(b2Vec2(0,a.y*(-15)));
}
