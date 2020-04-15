// user libraries
#include "ObjReader.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <typeinfo>
#include <string>

ObjReader::ObjReader(std::string filename)
{
    std::ifstream file(filename);

    std::cout << "filename: " << filename << "\n";

    // if file isn't there, print out warning
    if (!file)
    {
        std::cout << "unable to open file";
        exit(1);
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.substr(0, 6) == "mtllib")
        {
            // set material file information
            ObjReader::getMtlInfo(line, filename);
        }
        if (line.substr(0, 2) == "v ")
        {
            // add vertex
            Vector3 vertex = ObjReader::setVector3(line);
            vertices.push_back(vertex);
        }
        else if (line.substr(0, 3) == "vn ")
        {
            // add normal vertex
            Vector3 vertex = ObjReader::setVector3(line);

            normal.push_back(vertex);
        }
        else if (line.substr(0, 3) == "vt ")
        {
            // add texture coord
            Vector2 vertexTexture = ObjReader::setVector2(line);

            textures.push_back(vertexTexture);
        }
        else if (line.substr(0, 2) == "f ")
        {
            std::vector<std::string> something = ObjReader::split(line, "\\s+");

            for (int i = 1; i < something.size(); i++)
            {
                std::string currString = something[i];
                if (currString.find("\/\/") != std::string::npos)
                {
                    std::vector<std::string> grabbedVertices = ObjReader::split(currString, "\/\/");
                    vertexIndices.push_back(std::stoi(grabbedVertices[0]));
                }
                else
                {
                    // add face
                    ObjReader::setFace(currString);
                }
            }
        }
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
    }
}

void ObjReader::getCalculatedTangents()
{
    for (unsigned int i = 0; i < vertexDataOut.size(); i += 3)
    {

        VertexData v0 = vertexDataOut[i];
        VertexData v1 = vertexDataOut[i + 1];
        VertexData v2 = vertexDataOut[i + 2];

        QVector3D v0GLM(v0.x, v0.y, v0.z);
        QVector3D v1GLM(v1.x, v1.y, v1.z);
        QVector3D v2GLM(v2.x, v2.y, v2.z);

        QVector3D Edge1 = v1GLM - v0GLM;
        QVector3D Edge2 = v2GLM - v0GLM;

        QVector2D t0GLM = QVector2D(v0.s, v0.t);
        QVector2D t1GLM = QVector2D(v1.s, v1.t);
        QVector2D t2GLM = QVector2D(v2.s, v2.t);

        float DeltaU1 = t1GLM.x() - t0GLM.x();
        float DeltaV1 = t1GLM.y() - t0GLM.y();
        float DeltaU2 = t2GLM.x() - t0GLM.x();
        float DeltaV2 = t2GLM.y() - t0GLM.y();

        float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

        QVector3D Tangent, Bitangent;

        Tangent.setX(f * (DeltaV2 * Edge1.x() - DeltaV1 * Edge2.x()));
        Tangent.setY(f * (DeltaV2 * Edge1.y() - DeltaV1 * Edge2.y()));
        Tangent.setZ(f * (DeltaV2 * Edge1.z() - DeltaV1 * Edge2.z()));

        Bitangent.setX(f * (-DeltaU2 * Edge1.x() - DeltaU1 * Edge2.x()));
        Bitangent.setY(f * (-DeltaU2 * Edge1.y() - DeltaU1 * Edge2.y()));
        Bitangent.setZ(f * (-DeltaU2 * Edge1.z() - DeltaU1 * Edge2.z()));

        Tangent.normalize();
        Bitangent.normalize();

        tangents.push_back(Tangent);
        tangents.push_back(Tangent);
        tangents.push_back(Tangent);

        bitangents.push_back(Bitangent);
        bitangents.push_back(Bitangent);
        bitangents.push_back(Bitangent);
    }
}

std::vector<unsigned int> ObjReader::getFaces()
{
    std::vector<unsigned int> ans;
    for (int i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i];
        ans.push_back(vertexIndex);
    }

    return ans;
}

std::vector<float> ObjReader::getVerticesTexturesNormalsTangents()
{
    // set values for tangent/bitangent

    std::vector<float> ans;
    ObjReader::getCalculatedTangents();

    for (int i = 0; i < vertexDataOut.size(); i++)
    {

        VertexData curr = vertexDataOut[i];
        QVector3D tangent = tangents[i];
        QVector3D bitangent = bitangents[i];

        ans.push_back(curr.x);
        ans.push_back(curr.y);
        ans.push_back(curr.z);

        ans.push_back(curr.s);
        ans.push_back(curr.t);

        ans.push_back(curr.xn);
        ans.push_back(curr.yn);
        ans.push_back(curr.zn);

        ans.push_back(tangent.x());
        ans.push_back(tangent.y());
        ans.push_back(tangent.z());

        ans.push_back(bitangent.x());
        ans.push_back(bitangent.y());
        ans.push_back(bitangent.z());
    }

    return ans;
}

std::string ObjReader::getTextureMtlFilepath()
{

    return mtlTexture;
}

std::string ObjReader::getNormalMtlFilePath()
{

    return mtlNormal;
}

// Private functions
void ObjReader::getMtlInfo(std::string line, std::string filename)
{
    std::vector<std::string> splitLine = ObjReader::split(line, "\\s+");
    std::string mtlFile = splitLine[1];

    std::vector<std::string> filePath = ObjReader::split(filename, "\/");

    std::string ans = "";

    for (int i = 0; i < filePath.size() - 1; i++)
    {
        ans += filePath[i] + "/";
    }

    objFilePath = ans;

    MtlFileReader mtlReader = MtlFileReader(objFilePath + mtlFile);
    mtlTexture = objFilePath + mtlReader.getTextureFile();
    mtlNormal = objFilePath + mtlReader.getNormalFile();
}

ObjReader::Vector3 ObjReader::setVector3(std::string line)
{
    std::vector<std::string> something = ObjReader::split(line, "\\s+");
    Vector3 vector;
    vector.x = std::stof(something[1]);
    vector.y = std::stof(something[2]);
    vector.z = std::stof(something[3]);

    return vector;
}

ObjReader::Vector2 ObjReader::setVector2(std::string line)
{
    std::vector<std::string> something = ObjReader::split(line, "\\s+");
    Vector2 vector;
    vector.s = std::stof(something[1]);
    vector.t = std::stof(something[2]);

    return vector;
}

void ObjReader::setFace(std::string currString)
{
    std::vector<std::string> grabbedVertices = ObjReader::split(currString, "\/");

    // get vertex, texture and normal value at this position
    Vector3 vertex = vertices.at(std::stoi(grabbedVertices[0]) - 1);
    Vector2 vertexTexture = textures.at(std::stoi(grabbedVertices[1]) - 1);
    Vector3 vertexNormal = normal.at(std::stoi(grabbedVertices[2]) - 1);

    std::string combo = currString;

    try
    {
        // if face already exists, add index to indices
        int value = vectorVals.at(combo);
        vertexIndices.push_back(value);
    }
    catch (const std::out_of_range&)
    {
        // else, create a new vertex data and to vertices list
        int size = vectorVals.size();
        vectorVals.insert(std::pair<std::string, int>(combo, size));
        vertexIndices.push_back(size);

        VertexData newVertex;
        newVertex.x = vertex.x;
        newVertex.y = vertex.y;
        newVertex.z = vertex.z;
        newVertex.s = vertexTexture.s;
        newVertex.t = vertexTexture.t;
        newVertex.xn = vertexNormal.x;
        newVertex.yn = vertexNormal.y;
        newVertex.zn = vertexNormal.z;

        vertexDataOut.push_back(newVertex);
    }
}

std::vector<std::string> ObjReader::split(std::string s, std::string regexMatch)
{
    std::regex regex(regexMatch);

    std::vector<std::string> out(
        std::sregex_token_iterator(s.begin(), s.end(), regex, -1),
        std::sregex_token_iterator());
    return out;
}