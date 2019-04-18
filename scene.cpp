//
// Created by kannie on 04/04/19.
//

#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "getBMP.h"
#include "scene.h"

static unsigned int texture[3]; // Array of texture indices.
static float wallHight = 30.0;
static float roadWidth = 50.0;
static float wallWidth = 30.0;
static float skyWidth = 500.0;
static float skyDepth = -350.0;

// Routine to draw a stroke character string.
void writeStrokeString(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

// Routine to onvert floating point to char string.
void floatToString(char * destStr, int val)
{
    sprintf(destStr, "%d", val);
}

// Load external textures.
void loadTextures()
{
    // Create texture ids.
    glGenTextures(3, texture);

    // Local storage for bmp image data.
    imageFile *image[3];

    // Load the images.
    image[0] = getBMP("/home/kannie/AIT/CG/Project/PenquinTheAdventure/images/texture-snow.bmp");
    image[1] = getBMP("/home/kannie/AIT/CG/Project/PenquinTheAdventure/images/ice-wall.bmp");
    image[2] = getBMP("/home/kannie/AIT/CG/Project/PenquinTheAdventure/images/sky.bmp");

    // Bind grass image to texture object texture[0].
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind sky image to texture object texture[1]
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->width, image[1]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind sky image to texture object texture[2]
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->width, image[2]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);
}

Scener::Scener() {}

void Scener::writeScore(int score, float pPosX, float pPosY) {
    glDisable(GL_LIGHTING);
    char theStringBuffer[10]; // String buffer.
    floatToString(theStringBuffer, score);

    // Score
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-5.0 + pPosX, 40.0 + pPosY, -60.0);
    glScalef(0.05, 0.05, 0.05);
    writeStrokeString(GLUT_STROKE_ROMAN, theStringBuffer);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Scener::writeGameOver(int score) {
    glDisable(GL_LIGHTING);
    char theStringBuffer[10]; // String buffer.
    floatToString(theStringBuffer, score);

    // Score
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-5.0, 40.0, -60.0);
    glScalef(0.05, 0.05, 0.05);
    writeStrokeString(GLUT_STROKE_ROMAN, theStringBuffer);
    glPopMatrix();

    // Instruction.
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-35.0, 30.0, -60.0);
    glScalef(0.05, 0.05, 0.05);
    writeStrokeString(GLUT_STROKE_ROMAN, "Press spacebar to play");
    glPopMatrix();
    glEnable(GL_LIGHTING);
}
// Function to draw a point.
void Scener::draw(float distance, float numGroundBox)
{
    // Floor.
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glColor3f(0.85, 1.0, 1.0);
    glTexCoord2f(0.0, distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f(-roadWidth, 0.0, 100.0);
    glTexCoord2f(6.0, distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f(roadWidth, 0.0, 100.0);
    glTexCoord2f(6.0, numGroundBox + distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f(roadWidth, 0.0, -300.0);
    glTexCoord2f(0.0, numGroundBox + distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f(-roadWidth, 0.0, -300.0);
    glEnd();
    // End floor.

    // Left wall
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glColor3f(0.85, 1.0, 1.0);
    glTexCoord2f(0.0, distance); glNormal3f(sqrt(3.0)/2.0, 0.5, 0.0); glVertex3f(-(roadWidth + wallHight/2.0), wallHight, 100.0);
    glTexCoord2f(2.4, distance); glNormal3f(sqrt(3.0)/2.0, 0.5, 0.0); glVertex3f(-roadWidth, 0.0, 100.0);
    glTexCoord2f(2.4, numGroundBox + distance); glNormal3f(sqrt(3.0)/2.0, 0.5, 0.0); glVertex3f(-roadWidth, 0.0, -300.0);
    glTexCoord2f(0.0, numGroundBox + distance); glNormal3f(sqrt(3.0)/2.0, 0.5, 0.0); glVertex3f(-(roadWidth + wallHight/2.0), wallHight, -300.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glColor3f(0.85, 1.0, 1.0);
    glTexCoord2f(0.0, distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f(-(roadWidth + wallHight/2.0 + wallWidth), wallHight, 100.0);
    glTexCoord2f(8.0, distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f(-(roadWidth + wallHight/2.0), wallHight, 100.0);
    glTexCoord2f(8.0, numGroundBox + distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f(-(roadWidth + wallHight/2.0), wallHight, -300.0);
    glTexCoord2f(0.0, numGroundBox + distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f(-(roadWidth + wallHight/2.0 + wallWidth), wallHight, -300.0);
    glEnd();
    // End left wall.

    // Right wall
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glColor3f(0.85, 1.0, 1.0);
    glTexCoord2f(0.0, distance); glNormal3f(-sqrt(3.0)/2.0, 0.5, 0.0); glVertex3f(50.0, 0.0, 100.0);
    glTexCoord2f(2.4, distance); glNormal3f(-sqrt(3.0)/2.0, 0.5, 0.0); glVertex3f((roadWidth + wallHight/2.0), wallHight, 100.0);
    glTexCoord2f(2.4, numGroundBox + distance); glNormal3f(-sqrt(3.0)/2.0, 0.5, 0.0); glVertex3f((roadWidth + wallHight/2.0), wallHight, -300.0);
    glTexCoord2f(0.0, numGroundBox + distance); glNormal3f(-sqrt(3.0)/2.0, 0.5, 0.0); glVertex3f(50.0, 0.0, -300.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glColor3f(0.85, 1.0, 1.0);
    glTexCoord2f(0.0, distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f((roadWidth + wallHight/2.0), wallHight, 100.0);
    glTexCoord2f(8.0, distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f((roadWidth + wallHight/2.0 + wallWidth), wallHight, 100.0);
    glTexCoord2f(8.0, numGroundBox + distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f((roadWidth + wallHight/2.0 + wallWidth), wallHight, -300.0);
    glTexCoord2f(0.0, numGroundBox + distance); glNormal3f(0.0, 1.0, 0.0); glVertex3f((roadWidth + wallHight/2.0), wallHight, -300.0);
    glEnd();
    // End right wall.

    // sky.
//    glDisable(GL_LIGHTING);
//    glBindTexture(GL_TEXTURE_2D, texture[2]);
//    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
//    glTexCoord2f(0.0, 0.0); glNormal3f(0.0, 0.0, 1.0); glVertex3f(-skyWidth, -100.0, skyDepth);
//    glTexCoord2f(1.0, 0.0); glNormal3f(0.0, 0.0, 1.0); glVertex3f(skyWidth, -100.0, skyDepth);
//    glTexCoord2f(1.0, 1.0); glNormal3f(0.0, 0.0, 1.0); glVertex3f(skyWidth, skyWidth, skyDepth);
//    glTexCoord2f(0.0, 1.0); glNormal3f(0.0, 0.0, 1.0); glVertex3f(-skyWidth, skyWidth, skyDepth);
//    glEnd();
//    glEnable(GL_LIGHTING);
    // End floor.
}