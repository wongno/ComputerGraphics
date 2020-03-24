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
        if (line.substr(0, 6) == "mtllib") {
            std::vector<std::string> splitLine = ObjReader::split(line, "\\s+");
            std::string mtlFile = splitLine[1];

            std::vector<std::string> filePath = ObjReader::split(filename, "\/");

            std::string ans = "";

            for (int i = 0; i < filePath.size() - 1; i++) {
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
                    try {
                        int value = vectorVals.at(combo);
                        vertexIndices.push_back(value);


                    }
                    catch (const std::out_of_range&) {
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

    return vertexAndTextures;
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