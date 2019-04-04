//
// Created by kannie on 04/04/19.
//
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include "Obstracles.h"


#include <iostream>


Obstracle::Obstracle(float xPos, float zPos, float r) {
    this->xPos = xPos;
    this->zPos = zPos;
    this->radious = r;
}

void Obstracle::draw() {
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);

    // Movement.
    glTranslatef(xPos, 0.0, zPos);

    glTranslatef(0.0, radious, 0.0);
    glutSolidSphere(radious, 100, 100);
    glPopMatrix();
    glPopAttrib();
}

void Obstracle::updatePos(float animateDiff, float numGroundBox) {
    this->zPos = this->zPos + animateDiff * numGroundBox / 3.0;
}

bool Obstracle::isHit(float pPosX, float pPosY, float r) {
    double distance = hypot(hypot(pPosX-this->xPos,pPosY-0.0),0.0-this->zPos);
    float closeRange = r + this->radious;
    return distance < closeRange;
}

Obstracles::Obstracles(int numObs) {
    this->numObs = numObs;
}

void Obstracles::draw() {
    for (auto obstracle : obstracles) { obstracle.draw(); }
}

void Obstracles::update(float animationRatio, float animateDiff, float numGroundBox) {
    float ratioAdd = numGroundBox / numObs;
    bool isTime = fmodf(animationRatio, ratioAdd) <= 0.1;
    for (auto& obstracle : obstracles) {
        obstracle.updatePos(animateDiff, numGroundBox);
    }
    if (obstracles.size() >= numObs && isTime) {
        obstracles.pop_back();
    }
    if (isTime) {
        int radious = rand() % 5 + 5;
        int xPos = rand() % (100 - 2 * radious) - (50 - radious);
        obstracles.push_front(Obstracle(xPos, -300.0, radious));
    }
}

bool Obstracles::isHit(float pPosX, float pPosY, float r) {
    for (auto obstracle : obstracles) {
        if (obstracle.isHit(pPosX, pPosY, r)) return true;
    }
    return false;
}