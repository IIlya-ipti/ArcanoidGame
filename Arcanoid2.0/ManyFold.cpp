#include "ManyFold.h"

double ManyFold::WindowX;
double ManyFold::WindowY;
int ManyFold::PlayerScores = 0;
bool ManyFold::ApplyImpulseBlock() {
    if (!obj2->isShow()) {
        return false;
    }
    bool x, y, flag = false;
    sf::Vector2f vec = obj1->getSpeed();
    x = AxIntersect({ vec.x,0 });
    y = AxIntersect({ 0,vec.y });
    obj1->run(-time);
    if (x) {
        obj1->setSpeed({ -vec.x,vec.y });
    }
    if (y) {
        obj1->setSpeed({ vec.x, -vec.y });
    }
    if (!(x || y)) {
        obj1->setSpeed(vec);
    }
    else {
        if (obj2->isPlatform() && obj1->isStick()) {
            obj1->setSpeed({ 0,0 });
            obj1->setStick(false);
        }
        flag = true;
    }
    obj1->run(time);
    return flag;
}
bool ManyFold::AxIntersectWindow(sf::Vector2f vec) {
    obj1->run(-time);
    obj1->setSpeed(vec);
    obj1->run(time);
    sf::Vector2f pos = obj1->getSprite().getPosition();
    double width = obj1->getSprite().getGlobalBounds().width;
    double height = obj1->getSprite().getGlobalBounds().height;

    // release bonus if ball outside the scene
    if ((pos.y + height >= WindowY)) {
        if (obj1->isfloor()) {

            return true;
        }
        obj1->getSprite().setPosition(sf::Vector2f(WindowX / 2, WindowY / 2 + 100));
        PlayerScores -= 1;
    }
    return  (pos.x + width >= WindowX) || (pos.y <= 0) || (pos.x <= 0);
}
void ManyFold::PosCorrectionBall() {
    if (!obj2->isShow()) {
        return;
    }
    bool x, y;
    sf::Vector2f vec = obj1->getSpeed();
    x = AxIntersectWindow({ vec.x,0 });
    y = AxIntersectWindow({ 0,vec.y });
    obj1->run(-time);
    if (x) {
        obj1->setSpeed({ -vec.x,vec.y });
    }
    if (y) {
        obj1->setSpeed({ vec.x, -vec.y });
    }
    if (!(x || y)) {
        obj1->setSpeed(vec);
    }
    else {
        obj1->setfloor(false);
    }
    obj1->run(time);
}
bool ManyFold::AxIntersect(sf::Vector2f vec) {
    obj1->run(-time);
    obj1->setSpeed(vec);
    obj1->run(time);
    return intersects(obj1, obj2);
}
void ManyFold::setWindowAxis(double weight, double height) {
    WindowX = weight;
    WindowY = height;
}
int ManyFold::getPlayerPoints() {
    return PlayerScores;
}
ManyFold::ManyFold(std::shared_ptr <object> obj1, std::shared_ptr <object> obj2) {
    this->obj1 = std::move(obj1);
    this->obj2 = std::move(obj2);
}
void ManyFold::setTime(double t) {
    this->time = t;
}
void ManyFold::apply() {
    bool in1 = obj1->intersect(this);
    bool in2 = obj2->intersect(this);
    if ((in1 || in2) && !obj2->isPlatform() && obj1->isBall()) {
        if (!obj2->isPlatform() && obj1->isBall()) {
            PlayerScores += 1;
        }
    }
}
bool ManyFold::ApplyImpulseBonus() {
    if (obj2->isShow()) {
        if (obj1->getSprite().getGlobalBounds().intersects(obj2->getSprite().getGlobalBounds())) {
            return true;
        }
    }
    return false;
}
bool intersects(std::shared_ptr<object> ob1, std::shared_ptr<object> ob2)
{
    if (ob1->getSprite().getGlobalBounds().intersects(ob2->getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}

