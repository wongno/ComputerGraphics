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
    };

    struct VertexData
    {
        float x, y, z;    // x,y,z positions
        float xn, yn, zn; // x,y,z normals
        float s, t;       // s,t texture coordinates

        VertexData() {};

        VertexData(float _x, float _y, float _z, float _xn, float _yn, float _zn, float _s, float _t) : x(_x), y(_y), z(_z), xn(_xn), yn(_yn), zn(_zn), s(_s), t(_t) {}

        // Tests if two VertexData are equal
        bool operator==(const VertexData& rhs)
        {
            if ((x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (xn == rhs.xn) && (yn == rhs.yn) && (zn == rhs.zn) && (s == rhs.s) && (t == rhs.t))
            {
                return true;
            }
            return false;
        }
    };

    std::vector<float> getVerticesAndTextures();
    std::vector<unsigned int> getFaces();
    std::string getMtlFilepath();

    // NOTE:    You may add any helper functions you like in the
    //          private section.
private:
    // filepath info
    std::string objFilePath;

    // filepath to .mtl file associated with .obj file
    std::string mtlFilePath;

    std::vector<VertexData> vertexDataOut;

    // vertices of .obj
    std::vector<Vector3> vertices;
    // normal values of .obj
    std::vector<Vector3> normal;
    // texture values of .obj
    std::vector<Vector2> textures;

    // vertex indices of face values of .obj
    std::vector<unsigned int> vertexIndices;

    std::map<std::string, int> vectorVals;

    // sets the material info, normal file and texture
    void getMtlInfo(std::string line, std::string filename);

    // use string to create a vector 3
    ObjReader::Vector3 setVector3(std::string line);

    // use string to create a vector 2
    ObjReader::Vector2 setVector2(std::string line);

    // use string to create a vertex data object
    void setFace(std::string currString);

    //splits a string based on regex passed into function
    std::vector<std::string> split(std::string givenString, std::string regexMatch);
};

#endif