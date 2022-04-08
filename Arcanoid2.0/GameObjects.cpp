#include "GameObjects.h"



double ManyFold::WindowX;
double ManyFold::WindowY;
int ManyFold::PlayerScores = 0;
object::object(_path path, double x0, double y0) {
    texture.loadFromFile(path.path);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(path.x0, path.y0, path.weight_, path.hight_));
    sprite.setPosition(x0, y0);
}
bool Bonus::intersect(ManyFold* collis) {
    if (collis->ApplyImpulseBonus()) {
        this->setShow(false);
        sf::Vector2f vec = ball->getSpeed();
        switch (nbonus)
        {
        case SIZE:
            platform->setScale({ 0.5,0.5 });
            break;
        case SPEED:
            vec.x *= 1.2;
            vec.y *= 1.2;
            ball->setSpeed(vec);
            break;
        case TRAJECTORY:
            ball->invX();
            ball->invY();
            break;
        case STICKING:
            ball->setStick(true);
            break;
        case HEALTH:
            ball->setfloor(true);
            break;
        default:
            break;
        }
        return true;
    }
    return false;
}
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
bool intersects(object* ob1, object* ob2) {
    if (ob1->getSprite().getGlobalBounds().intersects(ob2->getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}
bool ManyFold::ApplyImpulseBlock() {
    if (!obj2->isShow()) {
        return false;
    }
    Ball* ball = (Ball*)obj1;
    bool x, y, flag = false;
    sf::Vector2f vec = ball->getSpeed();
    x = AxIntersect({ vec.x,0 });
    y = AxIntersect({ 0,vec.y });
    ball->run(-time);
    if (x) {
        ball->setSpeed({ -vec.x,vec.y });
    }
    if (y) {
        ball->setSpeed({ vec.x, -vec.y });
    }
    if (!(x || y)) {
        ball->setSpeed(vec);
    }
    else {
        if (obj2->isPlatform() && ball->isStick()) {
            ball->setSpeed({ 0,0 });
            ball->setStick(false);
        }
        flag = true;
    }
    ball->run(time);
    return flag;
}
bool ManyFold::AxIntersectWindow(sf::Vector2f vec) {
    Ball* ball = (Ball*)obj1;
    ball->run(-time);
    ball->setSpeed(vec);
    ball->run(time);
    sf::Vector2f pos = ball->getSprite().getPosition();
    double width = ball->getSprite().getGlobalBounds().width;
    double height = ball->getSprite().getGlobalBounds().height;

    // release bonus if ball outside the scene
    if ((pos.y + height >= WindowY)) {
        if (ball->isfloor()) {
            
            return true;
        }
        ball->getSprite().setPosition(sf::Vector2f(WindowX / 2, WindowY / 2 + 100));
        PlayerScores -= 1;
    }
    return  (pos.x + width >= WindowX) || (pos.y <= 0) || (pos.x <= 0);
}
void ManyFold::PosCorrectionBall() {
    Ball* ball = (Ball*)obj1;
    if (!obj2->isShow()) {
        return;
    }
    bool x, y;
    sf::Vector2f vec = ball->getSpeed();
    x = AxIntersectWindow({ vec.x,0 });
    y = AxIntersectWindow({ 0,vec.y });
    ball->run(-time);
    if (x) {
        ball->setSpeed({ -vec.x,vec.y });
    }
    if (y) {
        ball->setSpeed({ vec.x, -vec.y });
    }
    if (!(x || y)) {
        ball->setSpeed(vec);
    }
    else {
        ball->setfloor(false);
    }
    ball->run(time);
}
bool ManyFold::AxIntersect(sf::Vector2f vec) {
    Ball* ball = (Ball*)obj1;
    ball->run(-time);
    ball->setSpeed(vec);
    ball->run(time);
    return intersects(obj1, obj2);
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
            Bonus* bonus = (Bonus*)obj2;
            return true;
        }
    }
    return false;
}