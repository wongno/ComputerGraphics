#include "PPM.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>



// Constructor loads a filename with the .ppm extension
PPM::PPM(std::string fileName){
    // TODO:    Load and parse a ppm to get its pixel
    //          data stored properly. 
    std::ifstream file(fileName);
    std::string line;
    if (!file) {
        std::cout << "no file" << std::endl;
    }
    int count = 0;
    std::string max = "";
    std::string compiled = "";
    m_PixelData = new unsigned char[m_width * m_height * 3];
    while (std::getline(file, line)) {
        if (!isComment(line)) {
            if (count == 0) { //1st line
                if (line != "P3") {
                    std::cout << "wrong file type" << std::endl;
                    break;
                }
            }
            if (count == 1) { //width and height
                std::istringstream iss(line);
                std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                    std::istream_iterator<std::string>());
                for (int i = 0; i < results.size(); i++) {
                    if (m_width == 0) {
                        m_width = std::stoi(results[i]);
                    }
                    else {
                        m_height = std::stoi(results[i]);
                    }
                }              
            }
            if (count == 2) { // max rgb
                std::vector<std::string> max = split(line);
                m_maxRGB = std::stoi(max[0]);
            }
            count += 1;
            compiled += line;
            compiled += " ";
        }                
    }
    m_PixelData = new unsigned char [m_width * m_height * 3];
    std::vector<std::string> comp = split(compiled);
    
    // doesn't include the first 3 lines of data (header, width & height, max rgb)
    for (int i = 4; i < comp.size(); i++) {
        m_PixelData[i-4]= std::stoi(comp[i]);
    }
}

// Destructor clears any memory that has been allocated
PPM::~PPM(){
    delete[] m_PixelData;
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName){
    std::ofstream output(outputFileName);
    output << "P3" << std::endl;
    output << m_width << " " << m_height << std::endl;
    output << m_maxRGB << std::endl;
    for (int i = 0; i < m_width * m_height * 3; i++) {
        output << (int)m_PixelData[i] << std::endl;
    }
    output.close();
}

// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken(){
    m_maxRGB = std::max(m_maxRGB - 50, 0);

    for (int i = 0; i < m_width * m_height * 3; i++) {
        unsigned char pixel = m_PixelData[i];
        m_PixelData[i] = std::max(pixel - 50,0);
    }
}

// Sets a pixel to a specific R,G,B value 
void PPM::setPixel(int x, int y, int R, int G, int B){
    int index = (y * m_width * 3) + x * 3;
    m_PixelData[index + 0] = R;
    m_PixelData[index + 1] = G;
    m_PixelData[index + 2] = B;
}

// returns true whether a line is a comment and contains '#'
bool PPM::isComment(std::string line) {
    std::string::size_type found = line.find_first_not_of(" ");
    char foundChar = line[found];
    return foundChar == '#';
}

// splits a string by white spaces and places them into a vector of strings
std::vector<std::string> PPM::split(std::string s) {
    std::regex regex("\\s+");
    std::vector<std::string> out(
        std::sregex_token_iterator(s.begin(), s.end(), regex, -1),
        std::sregex_token_iterator());
    return out;
}
