#include "Loger.h"
#include <iostream>
#include <cmath>

using namespace std;

int Loger::maxFps = 0;
int Loger::minFps = 1000000;

void Loger::report()
{
    cout << "Max FPS: " << maxFps << "\n";
    cout << "Min FPS: " << minFps << "\n";
}

void Loger::updateFpsRep(int _fps)
{
    maxFps = max(maxFps, _fps);
    minFps = min(minFps, _fps);
}
