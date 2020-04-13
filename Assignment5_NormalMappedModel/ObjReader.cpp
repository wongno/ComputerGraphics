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
            std::vector<std::string> splitLine = ObjReader::split(line, "\\s+");
            std::string mtlFile = splitLine[1];

            std::vector<std::string> filePath = ObjReader::split(filename, "\/");

            std::string ans = "";

            for (int i = 0; i < filePath.size() - 1; i++)
            {
                std::cout << "dkfjl: " << filePath[i] << "\n";
                ans += filePath[i] + "/";
            }

            objFilePath = ans;

            std::cout << "here::: " << ans << "\n";

            MtlFileReader mtlReader = MtlFileReader(objFilePath + mtlFile);
            mtlFilePath = objFilePath + mtlReader.getPath();
        }
        if (line.substr(0, 2) == "v ")
        {

            std::vector<std::string> something = ObjReader::split(line, "\\s+");
            Vector3 vertex;
            vertex.x = std::stof(something[1]);
            vertex.y = std::stof(something[2]);
            vertex.z = std::stof(something[3]);

            // std::cout << "\n vertex: " << something[1] << "\n";

            vertices.push_back(vertex);
        }
        else if (line.substr(0, 3) == "vn ")
        {
            std::vector<std::string> something = ObjReader::split(line, "\\s+");
            Vector3 vertex;
            vertex.x = std::stof(something[1]);
            vertex.y = std::stof(something[2]);
            vertex.z = std::stof(something[3]);

            normal.push_back(vertex);
        }
        else if (line.substr(0, 3) == "vt ")
        {
            std::vector<std::string> something = ObjReader::split(line, "\\s+");
            Vector2 vertexTexture;
            vertexTexture.s = std::stof(something[1]);
            vertexTexture.t = std::stof(something[2]);

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
                    std::cout << "\n vertex face: " << grabbedVertices[0] << "\n";
                    vertexIndices.push_back(std::stoi(grabbedVertices[0]));
                }
                else
                {
                    std::vector<std::string> grabbedVertices = ObjReader::split(currString, "\/");

                    Vector3 vertex = vertices.at(std::stoi(grabbedVertices[0]) - 1);
                    Vector2 vertexTexture = textures.at(std::stoi(grabbedVertices[1]) - 1);

                    Vector2 combo;
                    combo.s = std::stoi(grabbedVertices[0]) - 1;
                    combo.t = std::stoi(grabbedVertices[1]) - 1;

                    faces.push_back(combo);

                    // try
                    // {
                    //     int value = vectorVals.at(combo);
                    //     vertexIndices.push_back(value);
                    // }
                    // catch (const std::out_of_range &)
                    // {
                    //     int size = vectorVals.size();
                    //     vectorVals.insert(std::pair<ObjReader::Vector2, int>(combo, size));
                    //     vertexIndices.push_back(size);

                    //     vertexAndTextures.push_back(vertex.x);
                    //     vertexAndTextures.push_back(vertex.y);
                    //     vertexAndTextures.push_back(vertex.z);
                    //     vertexAndTextures.push_back(vertexTexture.s);
                    //     vertexAndTextures.push_back(vertexTexture.t);
                    // }
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
    for (unsigned int i = 0; i < vertices.size(); i += 3)
    {
        ObjReader::Vector3 v0 = vertices[i];
        ObjReader::Vector3 v1 = vertices[i + 1];
        ObjReader::Vector3 v2 = vertices[i + 2];

        QVector3D v0GLM(v0.x, v0.y, v0.z);
        QVector3D v1GLM(v1.x, v1.y, v1.z);
        QVector3D v2GLM(v2.x, v2.y, v2.z);

        QVector3D Edge1 = v1GLM - v0GLM;
        QVector3D Edge2 = v2GLM - v0GLM;

        ObjReader::Vector2 t0 = textures[i];
        ObjReader::Vector2 t1 = textures[i + 1];
        ObjReader::Vector2 t2 = textures[i + 2];

        QVector2D t0GLM = QVector2D(t0.s, t0.t);
        QVector2D t1GLM = QVector2D(t1.s, t1.t);
        QVector2D t2GLM = QVector2D(t2.s, t2.t);

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

        // Same thing for bitangents
        bitangents.push_back(Bitangent);
        bitangents.push_back(Bitangent);
        bitangents.push_back(Bitangent);
    }
}

std::vector<float> ObjReader::getVertices()
{

    std::vector<float> ans;
    for (int i = 0; i < vertices.size(); i++)
    {

        ObjReader::Vector3 v = vertices[i];
        ans.push_back(v.x);
        ans.push_back(v.y);
        ans.push_back(v.z);
    }

    return ans;
}

std::vector<float> ObjReader::getNormals()
{

    std::vector<float> ans;
    for (int i = 0; i < normal.size(); i++)
    {

        ObjReader::Vector3 v = normal[i];
        ans.push_back(v.x);
        ans.push_back(v.y);
        ans.push_back(v.z);
    }

    return ans;
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

std::vector<float> ObjReader::getVerticesAndTextures()
{

    for (int i = 0; i < faces.size(); i++)
    {
        Vector2 combo = faces[i];
        Vector2 vertexTexture = textures[combo.t];
        Vector3 vertex = vertices[combo.s];
        QVector3D tangent = tangents[combo.t];

        try
        {
            int value = vectorVals.at(combo);
            vertexIndices.push_back(value);
        }
        catch (const std::out_of_range&)
        {
            int size = vectorVals.size();
            vectorVals.insert(std::pair<ObjReader::Vector2, int>(combo, size));
            vertexIndices.push_back(size);

            vertexAndTextures.push_back(vertex.x);
            vertexAndTextures.push_back(vertex.y);
            vertexAndTextures.push_back(vertex.z);
            vertexAndTextures.push_back(vertexTexture.s);
            vertexAndTextures.push_back(vertexTexture.t);
        }
    }

    return vertexAndTextures;
}

std::vector<QVector3D> ObjReader::getCalculatedTangent(unsigned int position, unsigned int texture)
{
    ObjReader::Vector3 v0 = vertices[position];
    ObjReader::Vector3 v1 = vertices[position + 1];
    ObjReader::Vector3 v2 = vertices[position + 2];

    QVector3D v0GLM(v0.x, v0.y, v0.z);
    QVector3D v1GLM(v1.x, v1.y, v1.z);
    QVector3D v2GLM(v2.x, v2.y, v2.z);

    QVector3D Edge1 = v1GLM - v0GLM;
    QVector3D Edge2 = v2GLM - v0GLM;

    ObjReader::Vector2 t0 = textures[texture];
    ObjReader::Vector2 t1 = textures[texture + 1];
    ObjReader::Vector2 t2 = textures[texture + 2];

    QVector2D t0GLM = QVector2D(t0.s, t0.t);
    QVector2D t1GLM = QVector2D(t1.s, t1.t);
    QVector2D t2GLM = QVector2D(t2.s, t2.t);

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

    std::vector<QVector3D> ans;
    ans.push_back(Tangent);
    ans.push_back(Bitangent);
    return ans;
}

std::vector<float> ObjReader::getVerticesTexturesNormalsTangents()
{
    // set values for tangent/bitangent

    std::vector<float> ans;

    for (int i = 0; i < faces.size(); i++)
    {
        Vector2 combo = faces[i];
        Vector2 vertexTexture = textures[combo.t];
        Vector3 vertex = vertices[combo.s];
        Vector3 normalVal = normal[combo.s];
        std::vector<QVector3D> tb = ObjReader::getCalculatedTangent(combo.s, combo.t);
        QVector3D tangent = tb[0];
        QVector3D bitangent = tb[1];
        try
        {
            int value = vectorVals.at(combo);
            vertexIndices.push_back(value);
        }
        catch (const std::out_of_range&)
        {
            int size = vectorVals.size();
            vectorVals.insert(std::pair<ObjReader::Vector2, int>(combo, size));
            vertexIndices.push_back(size);

            ans.push_back(vertex.x);
            ans.push_back(vertex.y);
            ans.push_back(vertex.z);
            ans.push_back(vertexTexture.s);
            ans.push_back(vertexTexture.t);

            ans.push_back(normalVal.x);
            ans.push_back(normalVal.y);
            ans.push_back(normalVal.z);

            ans.push_back(tangent.x());
            ans.push_back(tangent.y());
            ans.push_back(tangent.z());

            ans.push_back(bitangent.x());
            ans.push_back(bitangent.y());
            ans.push_back(bitangent.z());
        }
    }

    return ans;
}

std::string ObjReader::getMtlFilepath()
{

    return mtlFilePath;
}

std::vector<std::string> ObjReader::split(std::string s, std::string regexMatch)
{
    std::regex regex(regexMatch);

    std::vector<std::string> out(
        std::sregex_token_iterator(s.begin(), s.end(), regex, -1),
        std::sregex_token_iterator());
    return out;
}