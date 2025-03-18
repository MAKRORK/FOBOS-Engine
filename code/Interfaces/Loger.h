#pragma once

class Loger
{
private:
    static int minFps;
    static int maxFps;

public:
    static void report();
    static void updateFpsRep(int _fps);
};
