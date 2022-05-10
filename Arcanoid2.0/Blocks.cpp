#include "Blocks.h"

bool Block::intersect(ManyFold* collis) {
    if (collis->ApplyImpulseBlock()) {
        health--;
        if (health == 0) {
            this->setShow(false);
        }
        return true;
    }
    return false;
}
BlockBonus::BlockBonus(_path path, double x0, double y0, std::shared_ptr<Bonus>& bonus) :Block(path, x0, y0) {
    this->bonus = bonus;
    this->bonus->setShow(false);
}
void BlockBonus::setBonus(std::shared_ptr<Bonus>& bonus) {
    this->bonus = std::move(bonus);
    bonus->setShow(false);

}
bool BlockBonus::intersect(ManyFold* collis) {
    if (collis->ApplyImpulseBlock()) {
        health--;
        if (health == 0) {
            this->setShow(false);
            if (bonus != NULL) {
                bonus->setShow(true);
            }
        }
        return true;
    }
    return false;
}
SpeedBlock::SpeedBlock(_path path, double x0, double y0, std::shared_ptr <Ball>& ball) : Block(path, x0, y0) {
    this->ball = ball;
}
bool SpeedBlock::intersect(ManyFold* collis) {
    if (collis->ApplyImpulseBlock()) {
        sf::Vector2f vec2 = ball->getSpeed();
        vec2.x *= 1.1;
        vec2.y *= 1.1;
        ball->setSpeed(vec2);

        health--;
        if (health == 0) {
            this->setShow(false);
        }
        return true;
    }
    return false;
}

bool invulnerableBlock::intersect(ManyFold* collis) {
    if (collis->ApplyImpulseBlock()) {
        ;
    }
    return false;
}
