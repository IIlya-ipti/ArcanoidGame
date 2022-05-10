#pragma once
#include "Object.h"


bool intersects(std::shared_ptr <object> ob1, std::shared_ptr <object> ob2);


/* preprocessing collision between balland blocks */
class ManyFold {
private:
    static int PlayerScores;
    static double WindowY;
    static double WindowX;
    std::shared_ptr<object> obj1;
    std::shared_ptr<object> obj2;
    float time;

    bool AxIntersectWindow(sf::Vector2f vec);
    bool AxIntersect(sf::Vector2f vec);
public:
    static void setWindowAxis(double weight, double height);
    static int getPlayerPoints();
    ManyFold(std::shared_ptr<object> obj1, std::shared_ptr<object> obj2);
    void setTime(double t);
    bool ApplyImpulseBlock();
    bool ApplyImpulseBonus();
    void PosCorrectionBall();
    void apply();
};
