#pragma once
#include "SFML/Graphics.hpp"

class ManyFold;

typedef struct PathObject {
    const char* path;
    int x0;
    int y0;
    int weight_;
    int hight_;
} _path;




class object {
protected:
    bool draw = true;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    object(_path path, double x0, double y0);
    sf::Sprite& getSprite();
    virtual ~object();
    void setScale(sf::Vector2f vec);
    virtual void run(float t) = 0;
    virtual bool intersect(ManyFold* collis) = 0;
    virtual void setSpeed(sf::Vector2f speed);
    virtual void setStick(bool val);
    virtual bool isStick() const;
    virtual sf::Vector2f getSpeed() const;
    void setShow(bool a);
    bool isShow() const;
    virtual bool isPlatform() const;
    virtual bool isfloor() const;
    virtual void setfloor(bool floor);
    virtual bool isBall() const;
};
