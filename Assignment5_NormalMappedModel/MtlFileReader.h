
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

    // get texture file
    std::string getTextureFile();

    // get normal file
    std::string getNormalFile();

private:
    // path to texture file
    std::string textureFile;
    // normal file name
    std::string normalFile;
    // split string based on regex match
    std::vector<std::string> split(std::string givenString, std::string regexMatch);
};

#endif