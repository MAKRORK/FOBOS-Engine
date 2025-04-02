#include "Sprite.h"

vector<Sprite *> Sprite::sprites;

vector<SpriteToRender> Sprite::getSpritesToRender(SMath::vec2f pos, float dist, float fov, float angle)
{
    float dd = dist * dist;
    float f = fov / 2.f;
    SMath::vec2f fvt = SMath::getVectorFromAngle(angle);
    SMath::vec2f fvmn = SMath::getVectorFromAngle(angle - f);
    SMath::vec2f fvmx = SMath::getVectorFromAngle(angle + f);
    float scb = SMath::scalar(normalize(fvt), normalize(SMath::getVectorFromAngle(angle + SMath::pi / 2)));
    vector<SpriteToRender> vec;
    float sn = SMath::fast_sin(-angle);
    float cs = SMath::fast_cos(-angle);
    for (Sprite *s : sprites)
    {
        SMath::vec2f sp = s->getPos();
        float sc = SMath::scalar(fvt, SMath::normalize(sp - pos));
        float sqd = SMath::sqrLength(sp, pos);

        if (sqd < dd && sc > scb)
        {
            float d = SMath::fastSqrt(sqd);
            float dc = d * sc;
            SpriteToRender sr;
            sr.dist = dc;
            sr.h = (s->heigth) / dc;
            sr.w = (s->radius * 2) / dc;
            float dx1 = sp.x - pos.x;
            float dy1 = sp.y - pos.y;

            // float xx1 = dx1 * cs - dy1 * sn;
            float yy1 = dx1 * sn + dy1 * cs;
            // cout << SMath::vec2f(yy1, dc) << "   " << sc << "\n";
            sr.x = (1.f + (2 * yy1 / dc));
            sr.sprite = s;
            vec.push_back(sr);
            // cout << sr.w << "   " << sr.h << "\n";
        }
    }
    return vec;
}
