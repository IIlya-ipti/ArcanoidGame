#include "GameObjects.h"

Platform::Platform(_path path, double x0, double y0) : object(path, x0, y0) {}

void Platform::run(float t) {}

bool Platform::intersect(ManyFold* collis) {
    if (collis->ApplyImpulseBlock()) {
        return true;
    };
    return false;
}

bool Platform::isPlatform() const {
    return true;
}

Ball::Ball(_path path, double x0, double y0) :object(path, x0, y0) {}

void Ball::run(float t) {
    sf::Vector2f vec2 = this->sprite.getPosition();
    vec2.x = vec2.x + norm.x * t;
    vec2.y = vec2.y + norm.y * t;
    this->sprite.setPosition(vec2);
}

void Ball::invX() {
    norm.x = norm.x * -1;
}

void Ball::invY() {
    norm.y = norm.y * -1;
}

sf::Vector2f Ball::getSpeed() const {
    return norm;
}

void Ball::setStick(bool val) {
    this->stick = val;
}

bool Ball::isStick() const {
    return stick;
}

bool Ball::isfloor() const {
    return floor;
}

bool Ball::isBall() const {
    return true;
}

void Ball::setfloor(bool floor) {
    this->floor = floor;
}

void Ball::setSpeed(sf::Vector2f speed) {
    this->norm = speed;
}

bool Ball::intersect(ManyFold* collis) {
    collis->PosCorrectionBall();
    return false;
}
