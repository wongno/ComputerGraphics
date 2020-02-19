/** @file Obj.h
 *  @brief Class for working with Obj files
 *
 *  Class for working with P3 PPM images specifically.
 *
 *  @author your_name_here
 *  @bug No known bugs.
 */
#ifndef OBJ_H
#define OBJ_H

#include <string>
#include <vector>


class Obj {
public:
    // Constructor loads a filename with the .ppm extension
    Obj(std::string fileName);
    // Destructor clears any memory that has been allocated
    ~Obj() {};
    
    std::vector<float> getVertices();
    std::vector<float> getNormals();
    std::vector<unsigned int> getLineFaces();
    std::vector<unsigned int> getFaces();

    struct Vertex {
        float x, y, z;

    };
    

private:
    // returns True if a string is a comment with '#'
    bool isComment(std::string line);

    // returns vector list of string, removing spaces
    std::vector<std::string> split(std::string r, std::string s);

    std::vector<Vertex> temp_vertices;
    std::vector<Vertex> temp_normals;   
    std::vector< unsigned int > vertexIndices;




};


#endif
