//
// Created by kannie on 04/04/19.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include "Penquin.h"
#include <iostream>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define FRATE = 60;

std::vector<float> verticesVectorP; // Vector to read in vertex x, y and z values fromt the OBJ file.
std::vector<float> normalsVectorP; // Vector to read in vertex x, y and z values fromt the OBJ file.
std::vector<int> facesVectorP; // Vector to read in face vertex indices from the OBJ file.

float *verticesP[60];  // Vertex array of the object x, y, z values.
int *facesP[60];// Face (triangle) vertex indices.
float *normalsP[60];  // Vertex array of the object x, y, z values.
int numIndicesP[60]; // Number of face vertex indices.

void loadOBJPenquin(std::string fileName)
{
    verticesVectorP.clear();
    normalsVectorP.clear();
    facesVectorP.clear();
    std::string line;
    int count, vertexIndex1, vertexIndex2, vertexIndex3;
    float coordinateValue;
    char currentCharacter, previousCharacter;

    // Open the OBJ file.
    std::ifstream inFile(fileName.c_str(), std::ifstream::in);

    // Read successive lines.
    while (getline(inFile, line))
    {
        // Line has vertex data.
        if (line.substr(0, 2) == "v ")
        {
            // Initialize a string from the character after "v " to the end.
            std::istringstream currentString(line.substr(2));

            // Read x, y and z values. The (optional) w value is not read.
            for (count = 1; count <= 3; count++)
            {
                currentString >> coordinateValue;
                verticesVectorP.push_back(coordinateValue);
            }
        }

            // Line has vertex data.
        else if (line.substr(0, 3) == "vn ")
        {
            // Initialize a string from the character after "vn " to the end.
            std::istringstream currentString(line.substr(3));

            // Read x, y and z values. The (optional) w value is not read.
            for (count = 1; count <= 3; count++)
            {
                currentString >> coordinateValue;
                normalsVectorP.push_back(coordinateValue);
            }
        }

            // Line has face data.
        else if (line.substr(0, 2) == "f ")
        {
            // Initialize a string from the character after "f " to the end.
            std::istringstream currentString(line.substr(2));

            // Strategy in the following to detect a vertex index within a face line is based on the
            // fact that vertex indices are exactly those that follow a white space. Texture and
            // normal indices are ignored.
            // Moreover, from the third vertex of a face on output one triangle per vertex, that
            // being the next triangle in a fan triangulation of the face about the first vertex.
            previousCharacter = ' ';
            count = 0;
            while (currentString.get(currentCharacter))
            {
                // Stop processing line at comment.
                if ((previousCharacter == '#') || (currentCharacter == '#')) break;

                // Current character is the start of a vertex index.
                if ((previousCharacter == ' ') && (currentCharacter != ' '))
                {
                    // Move the string cursor back to just before the vertex index.
                    currentString.unget();

                    // Read the first vertex index, decrement it so that the index range is from 0, increment vertex counter.
                    if (count == 0)
                    {
                        currentString >> vertexIndex1;
                        vertexIndex1--;
                        count++;
                    }

                        // Read the second vertex index, decrement it, increment vertex counter.
                    else if (count == 1)
                    {
                        currentString >> vertexIndex2;
                        vertexIndex2--;
                        count++;
                    }

                        // Read the third vertex index, decrement it, increment vertex counter AND output the first triangle.
                    else if (count == 2)
                    {
                        currentString >> vertexIndex3;
                        vertexIndex3--;
                        count++;
                        facesVectorP.push_back(vertexIndex1);
                        facesVectorP.push_back(vertexIndex2);
                        facesVectorP.push_back(vertexIndex3);
                    }

                        // From the fourth vertex and on output the next triangle of the fan.
                    else
                    {
                        vertexIndex2 = vertexIndex3;
                        currentString >> vertexIndex3;
                        vertexIndex3--;
                        facesVectorP.push_back(vertexIndex1);
                        facesVectorP.push_back(vertexIndex2);
                        facesVectorP.push_back(vertexIndex3);
                    }

                    // Begin the process of detecting the next vertex index just after the vertex index just read.
                    currentString.get(previousCharacter);
                }

                    // Current character is not the start of a vertex index. Move ahead one character.
                else previousCharacter = currentCharacter;
            }
        }

            // Nothing other than vertex and face data is processed.
        else
        {
        }
    }

    // Close the OBJ file.
    inFile.close();
}

Penquin::Penquin() {
    for (int numFrame=0; numFrame<60; numFrame++) {
        // Read the external OBJ file into the internal vertex and face vectors.

        if (numFrame < 10)
            loadOBJPenquin("/home/kannie/AIT/CG/Project/PenquinTheAdventure/images/animated_penquin/penquin_00000" + std::to_string(numFrame + 1) + ".obj");
        else
            loadOBJPenquin("/home/kannie/AIT/CG/Project/PenquinTheAdventure/images/animated_penquin/penquin_0000" + std::to_string(numFrame + 1) + ".obj");
        // Size the vertex array and copy into it x, y, z values from the vertex vector.

        verticesP[numFrame] = new float[verticesVectorP.size()];
        for (int i = 0; i < verticesVectorP.size(); i++) verticesP[numFrame][i] = verticesVectorP[i];
        normalsP[numFrame] = new float[normalsVectorP.size()];
        for (int i = 0; i < normalsVectorP.size(); i++) normalsP[numFrame][i] = normalsVectorP[i];
        // Size the faces array and copy into it face index values from the face vector.
        facesP[numFrame] = new int[facesVectorP.size()];
        for (int i = 0; i < facesVectorP.size(); i++) facesP[numFrame][i] = facesVectorP[i];
        numIndicesP[numFrame] = facesVectorP.size();
    }
}

void Penquin::draw() {
    numFrame++;
    if (numFrame == 60) numFrame = 0;
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verticesP[numFrame]);
    glNormalPointer(GL_FLOAT, 0, normalsP[numFrame]);
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();

    // Calculate invisible
    float invisBlended = 1.0;
    if (invisible) {
        currentInvis--;
        invisBlended = 0.5;
    }
    if (currentInvis == 0) invisible = false;
    switch(formNum) {
        case 0: this->r = 5; break;
        case 1: this->r = 6; break;
        case 2: this->r = 7; break;
    }

    // Movement.
    glTranslatef(xPos, yPos, 0.0);

    glTranslatef(0.0, r, 0.0);
    glScalef(r, r, r);
    glDrawElements(GL_TRIANGLES, numIndicesP[numFrame], GL_UNSIGNED_INT, facesP[numFrame]);
//    glutSolidSphere(r, 100, 100);
    glPopMatrix();
    glPopAttrib();

    glEnable(GL_NORMALIZE);
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
    if (xPos > -50.0+r) xPos -= 1;
}

void Penquin::moveRight() {
    if (xPos < 50.0-r) xPos += 1;
}

void Penquin::upForm() {
    if (formNum != maxFormNum) formNum++;
}

bool Penquin::downForm() {
    if (!invisible) {
        if (formNum == 0) return false;
        else {
            formNum--;
            invisible = true;
            currentInvis = maxInvis;
            return true;
        }
    } else return true;
}