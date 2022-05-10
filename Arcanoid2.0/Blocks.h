#pragma once

#include "Bonus.h"
#include "ManyFold.h"

class Block : public object {
protected:
    int health = 1;
public:
    Block(_path path, double x0, double y0) : object(path, x0, y0) {};
    virtual ~Block() {};
    void run(float t) {};
    virtual bool intersect(ManyFold* collis);
};
class BlockBonus : public Block {
    std::shared_ptr<Bonus> bonus = NULL;
public:
    BlockBonus(_path path, double x0, double y0, std::shared_ptr<Bonus>& bonus);
    ~BlockBonus() {};
    void setBonus(std::shared_ptr<Bonus>& bonus);
    bool intersect(ManyFold* collis);
};
class invulnerableBlock : public Block {
public:
    invulnerableBlock(_path path, double x0, double y0) : Block(path, x0, y0) {};
    ~invulnerableBlock() {};
    bool intersect(ManyFold* collis);

};
class SpeedBlock :public Block {
    std::shared_ptr <Ball> ball;
public:
    SpeedBlock(_path path, double x0, double y0, std::shared_ptr <Ball>& ball);
    ~SpeedBlock() {};
    bool intersect(ManyFold* collis);
};

