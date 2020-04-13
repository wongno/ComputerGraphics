#ifndef OBJREADER_H
#define OBJREADER_H

#include <string>
#include <vector>
#include <map>
#include "MtlFileReader.h"
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

class ObjReader
{
public:
    // Constructor loads a filename with the .ppm extension
    ObjReader(std::string fileName);
    // Destructor clears any memory that has been allocated
    ~ObjReader() {};

    // Struct to represent the x, y, z values of a Vector
    struct Vector3
    {
        float x, y, z;
    };

    // Struct to represent the s,t values of a Vector Texture
    struct Vector2
    {
        float s, t;

        // override the < operator so we can use Vector2 as a key in a map
        bool operator<(const Vector2& ob) const
        {
            return s < ob.s || (s == ob.s && t < ob.t);
        }
    };

    std::vector<float> getVertices();
    std::vector<float> getNormals();
    std::vector<float> getVerticesAndTextures();
    std::vector<float> getVerticesTexturesNormalsTangents();
    std::vector<unsigned int> getFaces();
    std::string getMtlFilepath();

    void getCalculatedTangents();

    // NOTE:    You may add any helper functions you like in the
    //          private section.
private:
    // filepath info
    std::string objFilePath;

    // filepath to .mtl file associated with .obj file
    std::string mtlFilePath;

    // vertices of .obj
    std::vector<Vector3> vertices;
    // normal values of .obj
    std::vector<Vector3> normal;
    // texture values of .obj
    std::vector<Vector2> textures;
    // face values of .obj
    std::vector<Vector2> faces;
    // vertex indices of face values of .obj
    std::vector<unsigned int> vertexIndices;

    // vertex and texture data for buffer
    std::vector<float> vertexAndTextures;

    // tangent values of .obj
    std::vector<QVector3D> tangents;

    // bitangents values of .obj
    std::vector<QVector3D> bitangents;

    std::map<ObjReader::Vector2, int> vectorVals;

    std::vector<QVector3D> getCalculatedTangent(unsigned int position, unsigned int texture);

    //splits a string based on regex passed into function
    std::vector<std::string> split(std::string givenString, std::string regexMatch);
};

#endif