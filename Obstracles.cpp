//
// Created by kannie on 04/04/19.
//
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include "Obstracles.h"

#include <iostream>

static std::vector<float> verticesVector; // Vector to read in vertex x, y and z values fromt the OBJ file.
static std::vector<float> normalsVector; // Vector to read in vertex x, y and z values fromt the OBJ file.
static std::vector<int> facesVector; // Vector to read in face vertex indices from the OBJ file.
static float *vertices = NULL;  // Vertex array of the object x, y, z values.
static int *faces = NULL; // Face (triangle) vertex indices.
static float *normals = NULL;  // Vertex array of the object x, y, z values.
static int numIndices; // Number of face vertex indices.
static int rangeR = 10;
static int baseR = 12;

void loadOBJ(std::string fileName)
{
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
                verticesVector.push_back(coordinateValue);
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
                normalsVector.push_back(coordinateValue);
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
                        facesVector.push_back(vertexIndex1);
                        facesVector.push_back(vertexIndex2);
                        facesVector.push_back(vertexIndex3);
                    }

                        // From the fourth vertex and on output the next triangle of the fan.
                    else
                    {
                        vertexIndex2 = vertexIndex3;
                        currentString >> vertexIndex3;
                        vertexIndex3--;
                        facesVector.push_back(vertexIndex1);
                        facesVector.push_back(vertexIndex2);
                        facesVector.push_back(vertexIndex3);
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


Obstracle::Obstracle(float xPos, float zPos, float r) {
    this->xPos = xPos;
    this->zPos = zPos;
    this->radious = r;
}

void Obstracle::draw() {
    float currentAngle = (radious - baseR) / (float) rangeR * 360.0;
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    glPushMatrix();

    // Movement.
    glTranslatef(xPos, 0.0, zPos);

    glTranslatef(0.0, radious / 2.0, 0.0);
    glScalef(radious, radious, radious);
    glRotatef(currentAngle, 0.0, 1.0, 0.0);
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(0.0, 0.0, -17.0);
    glColor4f(0.44, 0.48, 0.62, 0.9);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, faces);
    glPopMatrix();

    glEnable(GL_NORMALIZE);
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

    // Read the external OBJ file into the internal vertex and face vectors.
    loadOBJ("/home/kannie/AIT/CG/Project/PenquinTheAdventure/images/stone.obj");
    // Size the vertex array and copy into it x, y, z values from the vertex vector.
    vertices = new float[verticesVector.size()];
    for (int i = 0; i < verticesVector.size(); i++) vertices[i] = verticesVector[i];
    normals = new float[normalsVector.size()];
    for (int i = 0; i < normalsVector.size(); i++) normals[i] = normalsVector[i];
    // Size the faces array and copy into it face index values from the face vector.
    faces = new int[facesVector.size()];
    for (int i = 0; i < facesVector.size(); i++) faces[i] = facesVector[i];
    numIndices = facesVector.size();
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
        int radious = rand() % rangeR + baseR;
        int xPos = rand() % (100 - 2 * radious) - (50 - radious);
        obstracles.push_front(Obstracle(xPos, -300.0, radious));
    }
}

bool Obstracles::isHit(float pPosX, float pPosY, float r) {
    if (obstracles.size() == 0) return false;
    else return obstracles.back().isHit(pPosX, pPosY, r);
}