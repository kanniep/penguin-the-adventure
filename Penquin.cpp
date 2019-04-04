//
// Created by kannie on 04/04/19.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Penquin.h"

Penquin::Penquin() {}

void Penquin::draw() {
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);

    // Movement.
    glTranslatef(xPos, yPos, 0.0);

    glTranslatef(0.0, r, 0.0);
    glutSolidSphere(r, 100, 100);
    glPopMatrix();
    glPopAttrib();
}

void Penquin::updateJump() {
    if (yVelocity != 0.0) {
        if (yPos < 0.0) {
            yPos = 0.0;
            yVelocity = 0.0;
        } else {
            yPos += yVelocity*0.06;
            yVelocity += gravity;
        }
    }
}

void Penquin::jump() {
    if (yPos == 0.0) yVelocity = yJumpVelocity;
}

void Penquin::moveLeft() {
    if (xPos > -50.0) xPos -= 1;
}

void Penquin::moveRight() {
    if (xPos < 50.0) xPos += 1;
}
