//
// Created by kannie on 04/04/19.
//

#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "getBMP.h"
#include "scene.h"

static unsigned int texture[2]; // Array of texture indices.

// Load external textures.
void loadTextures()
{
    // Create texture ids.
    glGenTextures(2, texture);

    // Local storage for bmp image data.
    imageFile *image[2];

    // Load the images.
    image[0] = getBMP("/home/kannie/AIT/CG/Project/PenquinTheAdventure/images/texture-snow.bmp");
    image[1] = getBMP("/home/kannie/AIT/CG/Project/PenquinTheAdventure/images/posx.bmp");

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

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);
}

Scener::Scener() {}

// Function to draw a point.
void Scener::draw(float distance, float numGroundBox)
{
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, distance); glVertex3f(-50.0, 0.0, 100.0);
    glTexCoord2f(8.0, distance); glVertex3f(50.0, 0.0, 100.0);
    glTexCoord2f(8.0, numGroundBox + distance); glVertex3f(50.0, 0.0, -300.0);
    glTexCoord2f(0.0, numGroundBox + distance); glVertex3f(-50.0, 0.0, -300.0);
    glEnd();
}