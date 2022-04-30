#include "Object.h"

object::object(_path path, double x0, double y0) {
    texture.loadFromFile(path.path);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(path.x0, path.y0, path.weight_, path.hight_));
    sprite.setPosition(x0, y0);
}
sf::Sprite& object::getSprite() {
    return sprite;
}
object::~object() {}
void object::setScale(sf::Vector2f vec) {
    this->sprite.setScale(vec);
}
void object::setSpeed(sf::Vector2f speed) { ; }
void object::setStick(bool val) {}
bool object::isStick() const { return false; }
sf::Vector2f object::getSpeed() const {
    return { 0,0 };
}
void object::setShow(bool a) {
    draw = a;
}
bool object::isShow() const {
    return draw;
}
bool object::isPlatform() const {
    return false;
}
bool object::isfloor() const {
    return false;
}
void object::setfloor(bool floor) { ; }
bool object::isBall() const {
    return false;
}
