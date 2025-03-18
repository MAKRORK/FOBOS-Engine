#include "BVH.h"
#include "../../../Global.h"
#include "../../../Interfaces/World.h"
#include "Collider.h"
#include "SFML/Graphics.hpp"
#include "fstream"
// #include "time.h"
// #include "windows.h"

// int n = 300;

std::ofstream file("../logs/log.txt");

int BVH::createBVH(std::vector<Collider *> &vec, SMath::Geometry::RectGeometry rect)
{
    // n--;
    // if (n <= 0)
    //     return -1;
    if (vec.size() == 0)
    {
        return -1;
    }
    World::addObject(new Object());
    Object *obj = World::getObjectByIndex(World::getObjectCount() - 1);

    if (vec.size() == 1)
    {
        int id;
        rect.tl = vec[0]->getTopLeft();
        rect.br = vec[0]->getButtomRigth();
        obj->addChildren(new LineShape(SMath::side(rect.tl, SMath::vec2f(rect.br.x, rect.tl.y)), fv::Color::red));
        obj->addChildren(new LineShape(SMath::side(rect.br, SMath::vec2f(rect.br.x, rect.tl.y)), fv::Color::blue));
        obj->addChildren(new LineShape(SMath::side(rect.tl, SMath::vec2f(rect.tl.x, rect.br.y)), fv::Color::green));
        obj->addChildren(new LineShape(SMath::side(rect.br, SMath::vec2f(rect.tl.x, rect.br.y)), fv::Color::yellow));
        branches.push_back(BVHbranch());
        id = branches.size() - 1;
        branches[id].rect = rect;
        branches[id].collider = vec[0];
        return id;
    }

    rect.tl = vec[0]->getTopLeft();
    rect.br = vec[0]->getButtomRigth();

    for (Collider *c : vec)
    {
        rect.tl.x = min(rect.tl.x, c->getTopLeft().x);
        rect.tl.y = min(rect.tl.y, c->getTopLeft().y);
        rect.br.x = max(rect.br.x, c->getButtomRigth().x);
        rect.br.y = max(rect.br.y, c->getButtomRigth().y);
    }
    obj->addChildren(new LineShape(SMath::side(rect.tl, SMath::vec2f(rect.br.x, rect.tl.y)), fv::Color::red));
    obj->addChildren(new LineShape(SMath::side(rect.br, SMath::vec2f(rect.br.x, rect.tl.y)), fv::Color::blue));
    obj->addChildren(new LineShape(SMath::side(rect.tl, SMath::vec2f(rect.tl.x, rect.br.y)), fv::Color::green));
    obj->addChildren(new LineShape(SMath::side(rect.br, SMath::vec2f(rect.tl.x, rect.br.y)), fv::Color::yellow));
    // file << vec.size() << "\n";
    //  for (int i = 0; i < vec.size(); i++)
    //  {
    //      file << "{" << vec[i]->getTopLeft() << ", " << vec[i]->getButtomRigth() << "}\n";
    //      // file << "{" << vec[1]->getTopLeft() << ", " << vec[1]->getButtomRigth() << "}\n";
    //  }
    float vl = (rect.tl.x + rect.br.x) / 2.f;
    // std::vector<Collider *> colls = checkLineV(vl, vec);
    float r = vl, l = vl;
    // std::file << vec.size() << "\n";
    // for (int i = 0; i < branches.size(); i++)
    // {
    //     file << "id: " << i << " [" << branches[i].childs[0] << ", " << branches[i].childs[1] << "]\n";
    //     file << "{" << branches[i].rect.tl << ", " << branches[i].rect.br << "}\n";
    // }
    std::vector<Collider *> lc;
    std::vector<Collider *> rc;

    for (Collider *c : vec)
    {
        // if (c->getButtomRigth().x < rect.tl.x)
        if (vl > c->getTopLeft().x && vl < c->getButtomRigth().x)
        {
            if (vl - c->getTopLeft().x < c->getButtomRigth().x - vl)
            {
                if (c->getTopLeft().x <= l)
                {
                    l = c->getTopLeft().x;
                }
                rc.push_back(c);
            }
            else
            {
                if (r <= c->getButtomRigth().x)
                {
                    r = c->getButtomRigth().x;
                }
                lc.push_back(c);
            }
        }
        else if (c->getButtomRigth().x <= vl)
        {

            lc.push_back(c);
        }
        else
        {
            rc.push_back(c);
        }
    }
    float hl = (rect.tl.y + rect.br.y) / 2.f;
    float t = hl, b = hl;

    std::vector<Collider *> tc;
    std::vector<Collider *> bc;

    for (Collider *c : vec)
    {
        if (hl > c->getTopLeft().y && hl < c->getButtomRigth().y)
        {
            if (hl - c->getTopLeft().y <= c->getButtomRigth().y - hl)
            {
                if (c->getTopLeft().y <= t)
                {
                    t = c->getTopLeft().y;
                }
                bc.push_back(c);
            }
            else
            {
                if (b <= c->getButtomRigth().y)
                {
                    b = c->getButtomRigth().y;
                }
                tc.push_back(c);
            }
        }
        else if (c->getButtomRigth().y <= hl)
        {
            tc.push_back(c);
        }
        else
        {
            bc.push_back(c);
        }
    }
    float sv = (r - l) * (rect.br.y - rect.tl.y);
    float sh = (b - t) * (rect.br.x - rect.tl.x);
    int id;
    branches.push_back(BVHbranch());
    id = branches.size() - 1;
    branches[id].rect = rect;
    // file << "l: " << l << " r: " << r << " S = " << sv << "\n";
    // file << "t: " << t << " b: " << b << " S = " << sh << "\n";

    if (sv < sh)
    {
        // obj->addChildren(new LineShape(SMath::side(SMath::vec2f(l, rect.tl.y), SMath::vec2f(l, rect.br.y)), fv::Color::red));
        // obj->addChildren(new LineShape(SMath::side(SMath::vec2f(r, rect.tl.y), SMath::vec2f(r, rect.br.y)), fv::Color::blue));
        SMath::Geometry::RectGeometry lr;
        lr.tl = rect.tl;
        lr.br = SMath::vec2f(r, rect.br.y);
        branches[id].childs[0] = createBVH(lc, lr);
        SMath::Geometry::RectGeometry rr;
        rr.tl = SMath::vec2f(l, rect.tl.y);
        rr.br = rect.br;
        branches[id].childs[1] = createBVH(rc, rr);
    }
    else
    {
        // obj->addChildren(new LineShape(SMath::side(SMath::vec2f(rect.tl.x, t), SMath::vec2f(rect.br.x, t)), fv::Color::red));
        // obj->addChildren(new LineShape(SMath::side(SMath::vec2f(rect.tl.x, b), SMath::vec2f(rect.br.x, b)), fv::Color::blue));
        SMath::Geometry::RectGeometry tr;
        tr.tl = rect.tl;
        tr.br = SMath::vec2f(rect.br.x, b);
        branches[id].childs[0] = createBVH(tc, tr);
        SMath::Geometry::RectGeometry br;
        br.tl = SMath::vec2f(rect.tl.x, t);
        br.br = rect.br;
        branches[id].childs[1] = createBVH(bc, br);
    }

    // Sleep(100);
    // sf::sleep(sf::milliseconds(100));
    return id;
}

void BVH::createNewBVH(std::vector<Collider *> &vec)
{
    SMath::Geometry::RectGeometry r;
    r.tl = vec[0]->getTopLeft();
    r.br = vec[0]->getButtomRigth();

    for (Collider *c : vec)
    {
        r.tl.x = min(r.tl.x, c->getTopLeft().x);
        r.tl.y = min(r.tl.y, c->getTopLeft().y);
        r.br.x = max(r.br.x, c->getButtomRigth().x);
        r.br.y = max(r.br.y, c->getButtomRigth().y);
        // std::cout << c->getTopLeft() << " | " << c->getButtomRigth() << "\n";
    }
    // std::cout << r.tl << "    " << r.br << "\n";
    //  branches.push_back(bvh);
    createBVH(vec, r);
    // for (int i = 0; i < branches.size(); i++)
    // {
    //     cout << "id: " << i << " [" << branches[i].childs[0] << ", " << branches[i].childs[1] << "]\n";
    //     cout << "{" << branches[i].rect.tl << ", " << branches[i].rect.br << "}\n";
    // }
    file.close();
}
