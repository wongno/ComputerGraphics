/** @file MtlFileReader.h
 *  @brief Class for getting the texture file out of a material file
 *
 *  @author Anika
 *  @bug No known bugs.
 */
#ifndef MTLFILEREADER_H
#define MTLFILEREADER_H

#include <string>
#include <vector>

class MtlFileReader
{
public:
    // Constructor loads a filename with the .ppm extension
    MtlFileReader(std::string fileName);
    // Destructor clears any memory that has been allocated
    ~MtlFileReader() {};

    std::string getPath();


private:
    // path to texture file
    std::string textureFile;
    std::vector<std::string> split(std::string givenString, std::string regexMatch);
};

#endif