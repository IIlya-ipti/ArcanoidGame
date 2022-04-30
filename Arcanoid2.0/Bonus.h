#pragma once

#include "GameObjects.h"



class Bonus : public object {
protected:
    sf::Vector2f norm = { 0,1 };
    Ball* ball;
    Platform* platform;
public:
    Bonus(_path path, double x0, double y0);
    virtual ~Bonus() {};
    void setBall(Ball* ball);
    void setPlatform(Platform* platform);
    void run(float t);
    virtual void applyBonus() = 0;
    // in ManyFold
    bool intersect(ManyFold* collis);
};

class BonusSize : public Bonus {
    void applyBonus();
public:
    BonusSize(_path path, double x0, double y0);
};

class BonusSpeed : public Bonus {
    void applyBonus();
public:
    BonusSpeed(_path path, double x0, double y0);
};

class BonusTrajectory : public Bonus {
    void applyBonus();
public:
    BonusTrajectory(_path path, double x0, double y0);
};

class BonusSticking : public Bonus {
    void applyBonus();
public:
    BonusSticking(_path path, double x0, double y0);
};

class BonusHealth : public Bonus {
    void applyBonus();
public:
    BonusHealth(_path path, double x0, double y0);
};