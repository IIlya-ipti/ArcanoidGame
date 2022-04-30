#pragma once
#include <vector>
#include "Object.h"
#include "Blocks.h"
#include "ManyFold.h"
#include "Bonus.h"
#include "GameObjects.h"


enum {
    SIZE,
    SPEED,
    STICKING,
    HEALTH,
    TRAJECTORY,
    INVULNERABLE,
    SPEEDBLOCK
};


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



class Game {
    const double XWindow = 800;
    const double YWindow = 600;
    const int xNumBlocks = 10;
    const int yNumBlocks = 10;
    const float time_coeff = 3.4; // multiply time 
    std::vector<object*> objects;     // run objects
    std::vector<ManyFold*> manyfolds; // solve collisions
public:
    void SetObjects();
    void RUN();
};
