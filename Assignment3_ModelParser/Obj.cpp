#include "Obj.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

Obj::Obj(std::string fileName) {
    std::ifstream file(fileName);
    std::string line;
    if (!file) {
        std::cout << "no file" << std::endl;
    }
    while (std::getline(file, line)) {
        if (!isComment(line)) {
            std::vector<std::string> s = split("\\s+", line);
            if (s[0] == "v") {
                Vertex v;
                v.x = std::stof(s[1]);
                v.y = std::stof(s[2]);
                v.z = std::stof(s[3]);
                temp_vertices.push_back(v);
            }
            if (s[0] == "vn") {
                Vertex v;
                v.x = std::stof(s[1]);
                v.y = std::stof(s[2]);
                v.z = std::stof(s[3]);
                temp_normals.push_back(v);
            }
            if (s[0] == "f") {
                for (int i = 1; i <s.size(); i++) {
                    std::vector<std::string> f = split("\/\/", s[i]);
                    vertexIndices.push_back(std::stoi(f[0]));
                }
                             
            }
        }
    }
    
}


// returns true whether a line is a comment and contains '#'
bool Obj::isComment(std::string line) {
    std::string::size_type found = line.find_first_not_of(" ");
    char foundChar = line[found];
    return foundChar == '#';
}

// splits a string by white spaces and places them into a vector of strings
std::vector<std::string> Obj::split(std::string r, std::string s) {
    std::regex regex(r);
    std::vector<std::string> out(
        std::sregex_token_iterator(s.begin(), s.end(), regex, -1),
        std::sregex_token_iterator());
    return out;
}

std::vector<float> Obj::getVertices() 
{
    std::vector<float> result;
    for (int i = 0; i < temp_vertices.size(); i++) {
        Vertex v = temp_vertices[i];
        result.push_back(v.x);
        result.push_back(v.y);
        result.push_back(v.z);
    }
    return result;
}

std::vector<float> Obj::getNormals() {
    std::vector<float> result;
    for (int i = 0; i < temp_normals.size(); i++) {
        Vertex v = temp_normals[i];
        result.push_back(v.x);
        result.push_back(v.y);
        result.push_back(v.z);
    }
    return result;
}

std::vector<unsigned int> Obj::getFaces()
{
    std::vector<unsigned int> ans;
    for (int i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i];
        ans.push_back(vertexIndex - 1);
    }

    return ans;
}
std::vector<unsigned int> Obj::getLineFaces()
{

    std::vector<unsigned int> ans;
    for (int i = 0; i < vertexIndices.size(); i += 3)
    {

        unsigned int first = vertexIndices[i];
        unsigned int second = vertexIndices[i + 1];
        unsigned int third = vertexIndices[i + 2];
        ans.push_back(first - 1);
        ans.push_back(second - 1);
        ans.push_back(second - 1);
        ans.push_back(third - 1);
        ans.push_back(first - 1);
        ans.push_back(third - 1);
    }

    return ans;
}