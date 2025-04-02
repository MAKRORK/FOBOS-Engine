#include "CameraR3D.h"
#include "../Entity/Colliders/Collider.h"
#include "../../Global.h"
#include "../../Interfaces/RenderR3D.h"
#include "../R3DObjects/Wall.h"
#include <cmath>
#include <thread>
#include "../R3DObjects/Sprite.h"

// void CameraR3D::render()
// {
//     float f = SMath::deg2rad(fov);
//     /// float s = getWorldRot() - f / 2.f;
//     // std::cout << resolution.x << " " << resolution.y;
//     SMath::vec2f med = (getWorldPos() + (getWorldPos() + getForwardVector() * distance)) / 2;
//     SMath::Geometry::RectGeometry rect;
//     rect.tl = med - distance / 2.f;
//     rect.br = med + distance / 2.f;
//     vector<Collider *> colls = Collider::getCollidersInBVH(rect, getParent());
// #pragma omp parallel for schedule(dynamic, 820)
//     for (int i = 0; i < resolution.x; i++)
//     {
//         float s = getWorldRot() - f / 2.f + (f / resolution.x) * i;
//         SMath::vec2f end = getWorldPos() + SMath::getVectorFromAngle(s) * distance;
//         // raycastResult res = Collider::raycast(getWorldPos(), end, getParent(), false, Global::miniMapCam);
//         //  s += f / resolution.x;
//         raycastResult res = Collider::raycastForThread(getWorldPos(), end, colls);
//         if (res.isColliding)
//         {
//             float md = distance * distance;

//             SMath::vec2f m = end;
//             int id = 0;
//             int side_id = 0;
//             for (int i = 0; i < res.collidedObjects.size(); i++)
//             {
//                 // /cout << res.collidedObjects[i].obj << " : ";
//                 for (int j = 0; j < res.collidedObjects[i].points.size(); j++)
//                 {
//                     // cout << res.collidedObjects[i].points[j] << "\n";
//                     float d = SMath::sqrLength(res.collidedObjects[i].points[j] - getWorldPos());
//                     if (d <= md)
//                     {
//                         md = d;
//                         m = res.collidedObjects[i].points[j];
//                         id = i;
//                         side_id = res.collidedObjects[i].sides[j];
//                     }
//                 }
//             }

//             float dist = SMath::fastSqrt(md) * SMath::fast_cos(abs(s - getWorldRot()));
//             float h = (50.f * getSize().y) / dist;
//             Wall *w = dynamic_cast<Wall *>(res.collidedObjects[id].obj);
//             SMath::side s = w->getSide(side_id);
//             float aspect = SMath::length(s.p2, m) / SMath::length(s);

//             // RenderR3D::renderRayLine(i, h, getRenderContext(), getContext(), resolution, getSize(), dist, aspect, w->getTextureIndex(side_id));
//         }
//     }
// }
bool comp(lineToRender a, lineToRender b)
{
    return a.dist > b.dist;
}
bool compSpr(SpriteToRender a, SpriteToRender b)
{
    return a.dist > b.dist;
}
vector<lineToRender> CameraR3D::lines;

void CameraR3D::render()
{
    float f = SMath::deg2rad(fov);
    lines.clear();
    lines.resize(resolution.x);
    SMath::vec2f wp = getWorldPos();
    float wr = getWorldRot();
    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(numThreads);
    SMath::vec2f med = (wp + (wp + getForwardVector() * distance)) / 2;
    SMath::Geometry::RectGeometry rect;
    rect.tl = med - distance / 2.f;
    rect.br = med + distance / 2.f;

    vector<Collider *> colls = Collider::getCollidersInBVH(rect, getParent());

    float start_ang = wr - f / 2.f;
    float step = (f / resolution.x);
    auto renderChunk = [&](int start, int end)
    {
        for (int i = start; i < end; i++)
        {
            float s = start_ang + step * i;
            SMath::vec2f end = wp + SMath::getVectorFromAngle(s) * distance;
            raycastResult res = Collider::raycastForThread(wp, end, colls);

            if (res.isColliding)
            {
                float md = distance * distance;
                SMath::vec2f m = end;
                int id = 0, side_id = 0;

                for (size_t j = 0; j < res.collidedObjects.size(); j++)
                {
                    for (size_t k = 0; k < res.collidedObjects[j].points.size(); k++)
                    {
                        float d = SMath::sqrLength(res.collidedObjects[j].points[k] - wp);
                        if (d <= md)
                        {
                            md = d;
                            m = res.collidedObjects[j].points[k];
                            id = j;
                            side_id = res.collidedObjects[j].sides[k];
                        }
                    }
                }

                float dist = SMath::fastSqrt(md) * SMath::fast_cos(s - wr);
                float h = (50.f * getSize().y) / dist;
                Wall *w = dynamic_cast<Wall *>(res.collidedObjects[id].obj);
                SMath::side s = w->getSide(side_id);
                float aspect = SMath::length(s.p2, m) / SMath::length(s);
                lines[i].x = i;
                lines[i].h = h;
                lines[i].dist = dist;
                lines[i].aspect = aspect;
                lines[i].tex_id = w->getTextureIndex(side_id);
            }
        }
    };

    int chunkSize = resolution.x / numThreads;
    for (int i = 0; i < numThreads; i++)
    {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? resolution.x : start + chunkSize;
        threads[i] = std::thread(renderChunk, start, end);
    }

    for (auto &t : threads)
    {
        t.join();
    }
    sort(lines.begin(), lines.end(), comp);
    float screenAsp = (float)getSize().x / getSize().y;
    vector<SpriteToRender> str = Sprite::getSpritesToRender(wp, distance, f, wr);
    int n = 0;
    // cout << screenAsp << "\n";
    RenderR3D::renderSky(getWorldRot(), 2, getRenderContext(), getContext(), getSize());
    RenderR3D::renderFloor(getRenderContext(), getContext(), getSize());
    for (lineToRender l : lines)
    {
        if (n < str.size() && str[n].dist > l.dist)
        {
            // cout << (str[n].w * screenAsp) * getSize().x << "\n";
            RenderR3D::renderSprite(SMath::vec2(str[n].x * getSize().x / 2 - (str[n].w / 2) * getSize().x, getSize().y / 2 - (str[n].h / 2) * getSize().y), str[n].sprite->getTextureIndex(), getRenderContext(), getContext(), SMath::vec2f(str[n].w * screenAsp, str[n].h), getSize());
            n++;
        }

        RenderR3D::renderRayLine(l.x, l.h, getRenderContext(), getContext(), resolution, getSize(), l.dist, l.aspect, l.tex_id);
    }

    while (n < str.size())
    {
        // /cout << SMath::vec2(str[n].x * getSize().x / 2 - (str[n].w / 2) * getSize().x, getSize().y / 2 - (str[n].h / 2) * getSize().y) << " " << SMath::vec2f(str[n].w * screenAsp, str[n].h) * getSize().y << " " << str[0].dist << "\n";
        RenderR3D::renderSprite(SMath::vec2(str[n].x * getSize().x / 2 - (str[n].w / 2) * getSize().x, getSize().y / 2 - (str[n].h / 2) * getSize().y), str[n].sprite->getTextureIndex(), getRenderContext(), getContext(), SMath::vec2f(str[n].w * screenAsp, str[n].h), getSize());
        n++;
    }
}