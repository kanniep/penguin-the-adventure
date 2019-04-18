//
// Created by kannie on 04/04/19.
//

#ifndef PENQUINTHEADVENTURE_PENQUIN_H
#define PENQUINTHEADVENTURE_PENQUIN_H


class Penquin {
public:
    Penquin();
    void draw();
    void jump();
    void updateJump();
    void moveLeft();
    void moveRight();
    void upForm();
    bool downForm();
    float xPos = 0, yPos = 0, r=5.0;
    int formNum=0;
private:
    float gravity = -0.9;
    float yJumpVelocity = 25.0, yVelocity = 0.0;
    int maxFormNum = 2;
    bool invisible=false;
    int maxInvis=120, currentInvis;
    int numFrame=-1;
};


#endif //PENQUINTHEADVENTURE_PENQUIN_H
