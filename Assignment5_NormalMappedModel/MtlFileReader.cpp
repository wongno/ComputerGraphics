// user libraries
#include "MtlFileReader.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <typeinfo>
#include <string>

MtlFileReader::MtlFileReader(std::string filename)
{
    std::ifstream file(filename);

    // if file isn't there, print out warning
    if (!file)
    {
        std::cout << "unable to open file";
        exit(1);
    }

    std::string line;

    while (std::getline(file, line))
    {

        if (line.substr(0, 10).find("map_Bump") != std::string::npos)
        {
            std::vector<std::string> lineSplit = MtlFileReader::split(line, "\\s+");
            normalFile = lineSplit[1];
        }

        if (line.substr(0, 6) == "map_Kd")
        {

            std::vector<std::string> lineSplit = MtlFileReader::split(line, "\\s+");
            textureFile = lineSplit[1];
        }
    }
}

std::string MtlFileReader::getTextureFile()
{
    return textureFile;
}

std::string MtlFileReader::getNormalFile()
{
    return normalFile;
}

std::vector<std::string> MtlFileReader::split(std::string s, std::string regexMatch)
{
    std::regex regex(regexMatch);

    std::vector<std::string> out(
        std::sregex_token_iterator(s.begin(), s.end(), regex, -1),
        std::sregex_token_iterator());
    return out;
}