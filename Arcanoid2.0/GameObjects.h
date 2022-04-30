#pragma once

#include "Object.h"
#include "ManyFold.h"


class Platform : public object {
public:
    Platform(_path path, double x0, double y0);
    void run(float t);;
    bool intersect(ManyFold* collis);
    bool isPlatform() const;
};
class Ball :public object {
    bool stick = false;
    bool floor = false;
    sf::Vector2f norm = { 1,-1 };
public:
    Ball(_path path, double x0, double y0);
    void run(float t);
    void invX();
    void invY();
    sf::Vector2f getSpeed() const;
    void setStick(bool val);
    bool isStick() const;

    bool isfloor() const;
    bool isBall() const;
    void setfloor(bool floor);
    void setSpeed(sf::Vector2f speed);
    bool intersect(ManyFold* collis);
};



