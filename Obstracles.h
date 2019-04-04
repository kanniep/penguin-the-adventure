//
// Created by kannie on 04/04/19.
//
#include <list>

#ifndef PENQUINTHEADVENTURE_OBSTRACLES_H
#define PENQUINTHEADVENTURE_OBSTRACLES_H

class Obstracle {
public:
    Obstracle(float xPos, float zPos, float r);
    void draw();
    void updatePos(float animateDiff, float numGroundBox);
    bool isHit(float pPosX, float pPosY, float r);
    float zPos;
private:
    float xPos, radious;
};

class Obstracles {
public:
    Obstracles(int numObs);
    void draw();
    void update(float animationRatio, float animateDiff, float numGroundBox);
    bool isHit(float pPosX, float pPosY, float r);
private:
    int numObs;
    std::list<Obstracle> obstracles;
};


#endif //PENQUINTHEADVENTURE_OBSTRACLES_H
