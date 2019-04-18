//
// Created by kannie on 11/04/19.
//
#include <list>
#ifndef PENQUINTHEADVENTURE_FOOD_H
#define PENQUINTHEADVENTURE_FOOD_H

class Food {
public:
    Food(float xPos, float zPos);
    void draw();
    void updatePos(float animateDiff, float numGroundBox);
    bool isHit(float pPosX, float pPosY, float r);
    float zPos;
private:
    float xPos, radious = 5.0;
};

class Foods {
public:
    Foods(int numObs);
    void draw();
    void update(float animationRatio, float animateDiff, float numGroundBox);
    bool isHit(float pPosX, float pPosY, float r);
private:
    int numObs;
    std::list<Food> foods;
};

#endif //PENQUINTHEADVENTURE_FOOD_H
