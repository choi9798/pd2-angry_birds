#include <yellowbird.h>

Yellowbird::Yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{

}
void Yellowbird::ability()
{
   b2Vec2 a=g_body->GetLinearVelocity();
   g_body->SetLinearVelocity(b2Vec2(a.x*5,a.y*5));
}
