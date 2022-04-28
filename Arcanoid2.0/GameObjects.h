#pragma once

#ifndef MY_GM_H // include guard
#define MY_GM_H
#include "SFML/Graphics.hpp"


/*
    abstract class of all objects (block, ball , blocksbonus, ...)
*/
class object;

/* 

    preprocessing collision between ball and blocks 

*/
class ManyFold;

/*
    class of ball
*/
class Ball;

/*
    class of bonus
*/
class Bonus;

/*
    class of platform
*/
class Platform;

/*
    class of block 
*/
class Block;

/*
    class of block bonus (bonus is inner of block)
*/
class BlockBonus;

class invulnerableBlock;

class SpeedBlock;

bool intersects(object* ob1, object* ob2);

enum {
    SIZE,
    SPEED,
    STICKING,
    HEALTH,
    TRAJECTORY,
    INVULNERABLE,
    SPEEDBLOCK
};


typedef struct PathObject {
    const char* path;
    int x0;
    int y0;
    int weight_;
    int hight_;
} _path;



const _path path_ball = {
    "./res/ball_out.png",
    37,32,33,33
};

const _path path_block = {
    "./res/sh_2.png",
    10,70,60,25
};

const _path path_platform = {
    "./res/sh_2.png",
    20,220,150,2
};

const _path path_bonus1 = {
    "./res/sh_2.png",
    0,110,80,80
};

const _path path_bonus2 = {
    "./res/sh_2.png",
    239, 110, 80, 80
};

const _path path_bonus3 = {
    "./res/sh_2.png",
    239, 110, 80, 80
};

const _path path_bonus4 = {
    "./res/sh_2.png",
    5, 0, 110, 33
};



/* preprocessing collision between ball and blocks */
class ManyFold {
private:
    static int PlayerScores;
    static double WindowY;
    static double WindowX;
    object* obj1;
    object* obj2;
    float time;

    bool AxIntersectWindow(sf::Vector2f vec);
    bool AxIntersect(sf::Vector2f vec);
public:
    static void setWindowAxis(double weight, double height) {
        WindowX = weight;
        WindowY = height;
    }
    static int getPlayerPoints() {
        return PlayerScores;
    }
    ManyFold(object*& obj1, object*& obj2) {
        this->obj1 = obj1;
        this->obj2 = obj2;
    }
    void setTime(double t) {
        this->time = t;
    }
    bool ApplyImpulseBlock();
    bool ApplyImpulseBonus();
    void PosCorrectionBall();
    void apply();
};




class object {
protected:
    bool draw = true;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    object(_path path, double x0, double y0);
    sf::Sprite& getSprite() {
        return sprite;
    }
    void setScale(sf::Vector2f vec) {
        sprite.setScale(vec);
    }
    virtual void run(float t) = 0;
    virtual bool intersect(ManyFold* collis) = 0;
    void setShow(bool a) {
        draw = a;
    }
    bool isShow() const {
        return draw;
    }
    virtual bool isPlatform() const {
        return false;
    }
    virtual bool isBall() const  {
        return false;
    }
};
class Platform : public object {
public:
    Platform(_path path, double x0, double y0) : object(path, x0, y0) {};
    void run(float t) {};
    bool intersect(ManyFold* collis) {
        if (collis->ApplyImpulseBlock()) {
            return true;
        };
        return false;
    }
    bool isPlatform() const {
        return true;
    }
};
class Ball :public object {
    bool stick = false;
    bool floor = false;
    sf::Vector2f norm = { 1,-1 };
public:
    Ball(_path path, double x0, double y0) :object(path, x0, y0) {};
    void run(float t) {
        sf::Vector2f vec2 = this->sprite.getPosition();
        vec2.x = vec2.x + norm.x * t;
        vec2.y = vec2.y + norm.y * t;
        this->sprite.setPosition(vec2);
    }
    void invX() {
        norm.x = norm.x * -1;
    }
    void invY() {
        norm.y = norm.y * -1;
    }
    sf::Vector2f getSpeed() const {
        return norm;
    }
    void setStick(bool val) {
        this->stick = val;
    }
    bool isStick() const {
        return stick;
    }
    bool isfloor() const {
        return floor;
    }
    bool isBall() const {
        return true;
    }
    void setfloor(bool floor) {
        this->floor = floor;
    }
    void setSpeed(sf::Vector2f speed) {
        this->norm = speed;
    }
    bool intersect(ManyFold* collis) {
        collis->PosCorrectionBall();
        return false;
    }
};
class Bonus : public object {
    sf::Vector2f norm = { 0,1 };
    Ball* ball;
    Platform* platform;
    int nbonus;
public:
    Bonus(_path path, int Bonus, double x0, double y0) : object(path, x0, y0) {
        this->nbonus = Bonus;
    };
    void setBall(Ball* ball) {
        this->ball = ball;
    }
    void setPlatform(Platform* platform) {
        this->platform = platform;
    }
    void run(float t) {
        if (isShow()) {
            sf::Vector2f vec2 = this->sprite.getPosition();
            vec2.x = vec2.x + norm.x * t;
            vec2.y = vec2.y + norm.y * t;
            this->sprite.setPosition(vec2);
        }
    }
    // in ManyFold
    bool intersect(ManyFold* collis);
};
class Block : public object {
protected:
    int health = 2;
public:
    Block(_path path, double x0, double y0) : object(path, x0, y0) {};
    void run(float t) {};
    virtual bool intersect(ManyFold* collis);
};
class BlockBonus : public Block {
    Bonus* bonus = NULL;
public:
    BlockBonus(_path path, double x0, double y0) :Block(path, x0, y0) {
        this->bonus = bonus;
    };
    void setBonus(Bonus*& bonus) {
        this->bonus = bonus;
        bonus->setShow(false);

    }
    bool intersect(ManyFold* collis);
};
class invulnerableBlock : public Block {
public:
    invulnerableBlock(_path path, double x0, double y0) : Block(path, x0, y0) {};
    bool intersect(ManyFold* collis) {
        if (collis->ApplyImpulseBlock()) {
            ;
        }
        return false;
    }

};
class SpeedBlock :public Block {
    Ball* ball;
public:
    SpeedBlock(_path path, double x0, double y0) : Block(path, x0, y0) {};
    void setBall(Ball* ball) {
        this->ball = ball;
    }
    bool intersect(ManyFold* collis);
};

#endif /* GM_H */