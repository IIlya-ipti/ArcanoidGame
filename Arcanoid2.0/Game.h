#pragma once
#ifndef MY_GAME_H // include guard
#define MY_GAME_H
#include "GameObjects.h"
#include <vector>


using namespace std;


class Game {
    const double XWindow = 800;
    const double YWindow = 600;
    const int xNumBlocks = 10;
    const int yNumBlocks = 10;
    const float time_coeff = 3.4;// multiply time 
    vector<object*> objects;     // run objects
    vector<ManyFold*> manyfolds; // solve collisions
public:
    void SetObjects();
    void RUN();
};
#endif /* GAME_H */