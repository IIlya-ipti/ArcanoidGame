
#include "Bonus.h"
bool Bonus::intersect(ManyFold* collis) {
    if (collis->ApplyImpulseBonus()) {
        this->setShow(false);
        applyBonus();
        return true;
    }
    return false;
}
Bonus::Bonus(_path path, double x0, double y0) : object(path, x0, y0) {
}
void Bonus::setBall(std::shared_ptr<Ball> &ball) {
    this->ball = ball;
}
void Bonus::setPlatform(std::shared_ptr<Platform>& platform) {
    this->platform = platform;
}

void Bonus::run(float t) {
    if (isShow()) {
        sf::Vector2f vec2 = this->sprite.getPosition();
        vec2.x = vec2.x + norm.x * t;
        vec2.y = vec2.y + norm.y * t;
        this->sprite.setPosition(vec2);
    }
}

void BonusSize::applyBonus() {
    platform->setScale({ 0.5,0.5 });
}

BonusSize::BonusSize(_path path, double x0, double y0) : Bonus(path, x0, y0) {}

void BonusSpeed::applyBonus() {
    sf::Vector2f vec = ball->getSpeed();
    vec.x *= 1.2;
    vec.y *= 1.2;
    ball->setSpeed(vec);
}

BonusSpeed::BonusSpeed(_path path, double x0, double y0) : Bonus(path, x0, y0) {}

void BonusTrajectory::applyBonus() {
    ball->invX();
    ball->invY();
}

BonusTrajectory::BonusTrajectory(_path path, double x0, double y0) : Bonus(path, x0, y0) {}

void BonusSticking::applyBonus() {
    ball->setStick(true);
}

BonusSticking::BonusSticking(_path path, double x0, double y0) : Bonus(path, x0, y0) {}

void BonusHealth::applyBonus() {
    ball->setfloor(true);
}

BonusHealth::BonusHealth(_path path, double x0, double y0) : Bonus(path, x0, y0) {}
