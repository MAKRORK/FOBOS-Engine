#include "ColliderCircle.h"
#include "../../../Interfaces/World.h"
#include "../Entity.h"
#include "ColliderRect.h"
#include "ColliderPolygon.h"
#include "ColliderLine.h"

void ColliderCircle::updateCircle()
{
    setCircleRad(getRadius());
    setCircleCenter(SMath::vec2f(0.f));
    setRect(-getRadius(), getRadius());
}

void ColliderCircle::collision()
{

    Entity *p = dynamic_cast<Entity *>(getParent());
    if (!p)
        return;
    SMath::Geometry::RectGeometry rect;
    rect.tl = getTopLeft() + p->getVel();
    rect.br = getButtomRigth() + p->getVel();
    vector<Collider *> colls = getBVHObjects(rect);
    for (int i = 0; i < colls.size(); i++)
    {

        Object *obj = colls[i]->getParent();
        if (obj == getParent() && obj)
            continue;

        Collider *col;

        col = colls[i];

        if (col)
        {
            if (col->getType() == COLLIDER_TYPE_LINE)
            {
                ColliderLine *l = dynamic_cast<ColliderLine *>(col);

                p->addImpulse(Collider::getMTVPolyCircle(l->getLine(), p->getWorldPos() + p->getVel(), getRadius()));
            }

            else if (col->getType() == COLLIDER_TYPE_RECT)
            {
                ColliderRect *rect = dynamic_cast<ColliderRect *>(col);

                p->addImpulse(Collider::getMTVPolyCircle(rect->getSides(), p->getWorldPos() + p->getVel(), getRadius()));
            }

            else if (col->getType() == COLLIDER_TYPE_CIRCLE)
            {
                ColliderCircle *c = dynamic_cast<ColliderCircle *>(col);
                SMath::vec2f h = (p->getWorldPos() + p->getVel()) - c->getWorldPos();
                if (SMath::length(h) < getRadius() + c->getRadius())
                {
                    SMath::vec2f mtv = SMath::normalize(h) * ((getRadius() + c->getRadius()) - SMath::length(h));

                    p->addImpulse(mtv);
                }
            }
            else if (col->getType() == COLLIDER_TYPE_POLY)
            {
                ColliderPolygon *pol = dynamic_cast<ColliderPolygon *>(col);

                p->addImpulse(Collider::getMTVPolyCircle(pol->getSides(), p->getWorldPos() + p->getVel(), getRadius()));
            }
        }
    }
}

void ColliderCircle::setRadius(float _radius)
{

    Circle::setRadius(_radius);
    updateCircle();
}
