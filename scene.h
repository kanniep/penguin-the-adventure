//
// Created by kannie on 04/04/19.
//

#ifndef PENQUINTHEADVENTURE_SCENE_H
#define PENQUINTHEADVENTURE_SCENE_H
class Scener {
public:
Scener();
void draw(float distance, float numGroundBox); // Function to draw a point.
void writeScore(int score, float pPosX, float pPosY);
void writeGameOver(int score);
private:
};

void loadTextures();
#endif //PENQUINTHEADVENTURE_SCENE_H
