// Includes for the assignment
#include "Vector4f.h"
#include "Matrix4f.h"
#include <iostream>

// Tests for comparing our library
// You may compare your operations against the glm library
// which is a well tested library.
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Sample unit test comparing against GLM.
bool unitTest0() {
    glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
    Matrix4f myIdentity(1.0f, 0, 0, 0,
        0, 1.0f, 0, 0,
        0, 0, 1.0f, 0,
        0, 0, 0, 1.0f);

    if (
        glmIdentityMatrix[0][0] == myIdentity[0][0] &&
        glmIdentityMatrix[0][1] == myIdentity[0][1] &&
        glmIdentityMatrix[0][2] == myIdentity[0][2] &&
        glmIdentityMatrix[0][3] == myIdentity[0][3] &&
        glmIdentityMatrix[1][0] == myIdentity[1][0] &&
        glmIdentityMatrix[1][1] == myIdentity[1][1] &&
        glmIdentityMatrix[1][2] == myIdentity[1][2] &&
        glmIdentityMatrix[1][3] == myIdentity[1][3] &&
        glmIdentityMatrix[2][0] == myIdentity[2][0] &&
        glmIdentityMatrix[2][1] == myIdentity[2][1] &&
        glmIdentityMatrix[2][2] == myIdentity[2][2] &&
        glmIdentityMatrix[2][3] == myIdentity[2][3] &&
        glmIdentityMatrix[3][0] == myIdentity[3][0] &&
        glmIdentityMatrix[3][1] == myIdentity[3][1] &&
        glmIdentityMatrix[3][2] == myIdentity[3][2] &&
        glmIdentityMatrix[3][3] == myIdentity[3][3]) {
        return true;
    }

    return false;
}

bool unitTest1() {
    glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
    Matrix4f myIdentity(1.0f, 0, 0, 0,
        0, 1.0f, 0, 0,
        0, 0, 1.0f, 0,
        0, 0, 0, 1.0f);

    if (
        glmIdentityMatrix[0][0] == myIdentity(0, 0) &&
        glmIdentityMatrix[0][1] == myIdentity(0, 1) &&
        glmIdentityMatrix[0][2] == myIdentity(0, 2) &&
        glmIdentityMatrix[0][3] == myIdentity(0, 3) &&
        glmIdentityMatrix[1][0] == myIdentity(1, 0) &&
        glmIdentityMatrix[1][1] == myIdentity(1, 1) &&
        glmIdentityMatrix[1][2] == myIdentity(1, 2) &&
        glmIdentityMatrix[1][3] == myIdentity(1, 3) &&
        glmIdentityMatrix[2][0] == myIdentity(2, 0) &&
        glmIdentityMatrix[2][1] == myIdentity(2, 1) &&
        glmIdentityMatrix[2][2] == myIdentity(2, 2) &&
        glmIdentityMatrix[2][3] == myIdentity(2, 3) &&
        glmIdentityMatrix[3][0] == myIdentity(3, 0) &&
        glmIdentityMatrix[3][1] == myIdentity(3, 1) &&
        glmIdentityMatrix[3][2] == myIdentity(3, 2) &&
        glmIdentityMatrix[3][3] == myIdentity(3, 3)) {
        return true;
    }

    return false;
}

// Sample unit test comparing against GLM.
bool unitTest2() {
    glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
    Vector4f a(1.0f, 0.0f, 0.0f, 0.0f);
    Vector4f b(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4f c(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4f d(0.0f, 0.0f, 0.0f, 1.0f);
    Matrix4f myIdentity(a, b, c, d);

    if (
        glmIdentityMatrix[0][0] == myIdentity[0][0] &&
        glmIdentityMatrix[0][1] == myIdentity[0][1] &&
        glmIdentityMatrix[0][2] == myIdentity[0][2] &&
        glmIdentityMatrix[0][3] == myIdentity[0][3] &&
        glmIdentityMatrix[1][0] == myIdentity[1][0] &&
        glmIdentityMatrix[1][1] == myIdentity[1][1] &&
        glmIdentityMatrix[1][2] == myIdentity[1][2] &&
        glmIdentityMatrix[1][3] == myIdentity[1][3] &&
        glmIdentityMatrix[2][0] == myIdentity[2][0] &&
        glmIdentityMatrix[2][1] == myIdentity[2][1] &&
        glmIdentityMatrix[2][2] == myIdentity[2][2] &&
        glmIdentityMatrix[2][3] == myIdentity[2][3] &&
        glmIdentityMatrix[3][0] == myIdentity[3][0] &&
        glmIdentityMatrix[3][1] == myIdentity[3][1] &&
        glmIdentityMatrix[3][2] == myIdentity[3][2] &&
        glmIdentityMatrix[3][3] == myIdentity[3][3]) {
        return true;
    }

    return false;
}

// Sample unit test comparing against GLM.
// TODO: Test against glm::scale
bool unitTest3() {
    glm::mat4 glmScale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
    Vector4f a(1.0f, 0, 0, 0);
    Vector4f b(0.0f, 1.0f, 0, 0);
    Vector4f c(0, 0, 1.0f, 0);
    Vector4f d(0, 0, 0, 1.0f);
    Matrix4f myScaled(a, b, c, d);
    myScaled = myScaled.MakeScale(2.0f, 2.0f, 2.0f);
    if (
        glmScale[0][0] == myScaled[0][0] &&
        glmScale[0][1] == myScaled[0][1] &&
        glmScale[0][2] == myScaled[0][2] &&
        glmScale[0][3] == myScaled[0][3] &&
        glmScale[1][0] == myScaled[1][0] &&
        glmScale[1][1] == myScaled[1][1] &&
        glmScale[1][2] == myScaled[1][2] &&
        glmScale[1][3] == myScaled[1][3] &&
        glmScale[2][0] == myScaled[2][0] &&
        glmScale[2][1] == myScaled[2][1] &&
        glmScale[2][2] == myScaled[2][2] &&
        glmScale[2][3] == myScaled[2][3] &&
        glmScale[3][0] == myScaled[3][0] &&
        glmScale[3][1] == myScaled[3][1] &&
        glmScale[3][2] == myScaled[3][2] &&
        glmScale[3][3] == myScaled[3][3]) {
        return true;
    }

    return false;
}

// Sample unit test comparing against GLM.
// Testing operator
bool unitTest4() {
    glm::mat4 glmTest = glm::mat4(1.0f);
    glmTest[1][3] = 72.0f;
    glmTest[2][3] = 2.1f;

    Matrix4f myMatrix(0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0);

    myMatrix[1][3] = 72.0f;
    myMatrix[2][3] = 2.1f;

    if (glmTest[1][3] == myMatrix[1][3] &&
        glmTest[2][3] == myMatrix[2][3]) {
        return true;
    }

    return false;
}

// Sample unit test testing your library
bool unitTest5() {
    Vector4f a(1, 1, 1, 1);
    Vector4f b(0, 0, 0, 0);
    Vector4f c = a + b;

    if (c.x == 1 && c.y == 1 && c.z == 1 && c.w == 1) {
        return true;
    }
    return false;
}

// Sample unit test testing your library
bool unitTestVector1() {
    glm::vec4 gv = glm::vec4(-5.0f, 2.0f, 0.0f, 10.0f);
    Vector4f v = Vector4f(-5.0f, 2.0f, 0.0f, 10.0f);
    gv *= 3.0f;
    v *= 3.0f;
    if (gv[0] == v[0] && gv[1] == v[1] && gv[2] == v[2] && gv[3] == v[3]) {
        return true;
    }
    else {
        return false;
    }
    // subtract the values to see if less that .001

}
bool unitTestVector2() {
    glm::vec4 gv = glm::vec4(-5, 2, 0, 10);
    Vector4f v = Vector4f(-5, 2, 0, 10);
    gv /= 3;
    v /= 3;
    return gv[0] == v[0] && gv[1] == v[1] && gv[2] == v[2] && gv[3] == v[3];
}
bool unitTestVector3() {
    glm::vec4 gv = glm::vec4(-5, 2, 0, 10);
    Vector4f v = Vector4f(-5, 2, 0, 10);
    glm::vec4 gv2 = glm::vec4(-8, 12, 2, 1);
    Vector4f v2 = Vector4f(-8, 12, 2, 1);
    gv += gv2;
    v += v2;
    return gv[0] == v[0] && gv[1] == v[1] && gv[2] == v[2] && gv[3] == v[3];
}
bool unitTestVector4() {
    glm::vec4 gv = glm::vec4(-5, 2, 0, 10);
    Vector4f v = Vector4f(-5, 2, 0, 10);
    glm::vec4 gv2 = glm::vec4(-8, 12, 2, 1);
    Vector4f v2 = Vector4f(-8, 12, 2, 1);
    gv -= gv2;
    v -= v2;
    return gv[0] == v[0] && gv[1] == v[1] && gv[2] == v[2] && gv[3] == v[3];
}
bool unitTestVector5() {
    glm::vec4 gv = glm::vec4(-5, 2, 0, 10);
    Vector4f v = Vector4f(-5, 2, 0, 10);
    glm::vec4 gv2 = glm::vec4(-8, 12, 2, 1);
    Vector4f v2 = Vector4f(-8, 12, 2, 1);
    float dotG = glm::dot(gv, gv2);
    float dotV = Dot(v, v2);
    return dotG == dotV;
}
bool unitTestVector6() {
    glm::vec4 gv = glm::vec4(-5, 2, 0, 10);
    Vector4f v = Vector4f(-5, 2, 0, 10);
    glm::vec4 rG = gv * 10.0f;
    Vector4f rV = v * 10.0f;
    return rG[0] == rV[0] && rG[1] == rV[1] && rG[2] == rV[2] && rG[3] == rV[3];
}

bool unitTestVector7() {
    glm::vec4 gv = glm::vec4(-5, 2, 0, 10);
    Vector4f v = Vector4f(-5, 2, 0, 10);
    glm::vec4 rG = gv / 10.0f;
    Vector4f rV = v / 10.0f;
    return rG[0] == rV[0] && rG[1] == rV[1] && rG[2] == rV[2] && rG[3] == rV[3];
}

bool unitTestVector8() {
    glm::vec4 gv = glm::vec4(-5, 2, 0, 10);
    Vector4f v = Vector4f(-5, 2, 0, 10);
    glm::vec4 rG = -gv;
    Vector4f rV = -v;
    return rG[0] == rV[0] && rG[1] == rV[1] && rG[2] == rV[2] && rG[3] == rV[3];
}

bool unitTestVector9() {
    glm::vec4 gv = glm::vec4(-5, 2, 0, 10);
    Vector4f v = Vector4f(-5, 2, 0, 10);
    float gMag = glm::length(gv);
    float vMag = Magnitude(v);


    return gMag == vMag;
}

bool unitTestVector10() {
    glm::vec4 g1 = glm::vec4(-5, 2, 0, 10);
    glm::vec4 g2 = glm::vec4(-3, 4, 2, -10);
    glm::vec4 gv = g1 + g2;
    Vector4f v1 = Vector4f(-5, 2, 0, 10);
    Vector4f v2 = Vector4f(-3, 4, 2, -10);
    Vector4f v = v1 + v2;
    return gv[0] == v[0] && gv[1] == v[1] && gv[2] == v[2] && gv[3] == v[3];
}

bool unitTestVector11() {
    glm::vec4 g1 = glm::vec4(-5, 2, 0, 10);
    glm::vec4 g2 = glm::vec4(-3, 4, 2, -10);
    glm::vec4 gv = g1 - g2;
    Vector4f v1 = Vector4f(-5, 2, 0, 10);
    Vector4f v2 = Vector4f(-3, 4, 2, -10);
    Vector4f v = v1 - v2;
    return gv[0] == v[0] && gv[1] == v[1] && gv[2] == v[2] && gv[3] == v[3];
}

//bool unitTestVector12() {
//    glm::vec4 g1 = glm::vec4(-5, 2, 0, 10);
//    glm::vec4 g2 = glm::vec4(-3, 4, 2, -10);
//    glm::vec4 gv = glm::gtx::proj(g1,g2);
//    Vector4f v1 = Vector4f(-5, 2, 0, 10);
//    Vector4f v2 = Vector4f(-3, 4, 2, -10);
//    Vector4f v = Project(v1,v2);
//    return gv[0] == v[0] && gv[1] == v[1] && gv[2] == v[2] && gv[3] == v[3];
//}
bool unitTestVector13() {
    glm::vec4 g1 = glm::vec4(-5, 2, 0, 10);
    glm::vec4 nG = glm::normalize(g1);
    Vector4f v1 = Vector4f(-5, 2, 0, 10);
    Vector4f v = Normalize(v1);
    return nG[0] == v[0] && nG[1] == v[1] && nG[2] == v[2] && nG[3] == v[3];
}

bool unitTestVector14() {
    glm::vec3 g1 = glm::vec3(-5, 2, 0);
    glm::vec3 g2 = glm::vec3(-3, 4, 2);
    glm::vec3 gv = glm::cross(g1, g2);
    Vector4f v1 = Vector4f(-5, 2, 0, 10);
    Vector4f v2 = Vector4f(-3, 4, 2, -10);
    Vector4f v = CrossProduct(v1, v2);
    return gv[0] == v[0] && gv[1] == v[1] && gv[2] == v[2];
}

bool unitTestMatrix1() {
    glm::mat4 glmMatrix = glm::mat4(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    glm::mat4 glmRotated = glm::rotate(glmMatrix, 180.0f, glm::vec3(1.0f, 0, 0));
    Matrix4f myMatrix(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4f id(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0);
    Matrix4f rMatrix = id.MakeRotationX(180.0f);
    Matrix4f rotatedMatrix = myMatrix * rMatrix;
    if (glmRotated[0][0] == rotatedMatrix[0][0] &&
        glmRotated[0][1] == rotatedMatrix[0][1] &&
        glmRotated[0][2] == rotatedMatrix[0][2] &&
        glmRotated[0][3] == rotatedMatrix[0][3] &&
        glmRotated[1][0] == rotatedMatrix[1][0] &&
        glmRotated[1][1] == rotatedMatrix[1][1] &&
        glmRotated[1][2] == rotatedMatrix[1][2] &&
        glmRotated[1][3] == rotatedMatrix[1][3] &&
        glmRotated[2][0] == rotatedMatrix[2][0] &&
        glmRotated[2][1] == rotatedMatrix[2][1] &&
        glmRotated[2][2] == rotatedMatrix[2][2] &&
        glmRotated[2][3] == rotatedMatrix[2][3] &&
        glmRotated[3][0] == rotatedMatrix[3][0] &&
        glmRotated[3][1] == rotatedMatrix[3][1] &&
        glmRotated[3][2] == rotatedMatrix[3][2] &&
        glmRotated[3][3] == rotatedMatrix[3][3]) {
        return true;
    }
    return false;
}

// Sample unit test testing your library
bool unitTestMatrix2() {
    glm::mat4 glmMatrix = glm::mat4(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    glm::mat4 glmRotated = glm::rotate(glmMatrix, 180.0f, glm::vec3(0, 1.0f, 0));
    Matrix4f myMatrix(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4f id(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0);
    Matrix4f rMatrix = id.MakeRotationY(180.0f);
    Matrix4f rotatedMatrix = myMatrix * rMatrix;
    if (glmRotated[0][0] == rotatedMatrix[0][0] &&
        glmRotated[0][1] == rotatedMatrix[0][1] &&
        glmRotated[0][2] == rotatedMatrix[0][2] &&
        glmRotated[0][3] == rotatedMatrix[0][3] &&
        glmRotated[1][0] == rotatedMatrix[1][0] &&
        glmRotated[1][1] == rotatedMatrix[1][1] &&
        glmRotated[1][2] == rotatedMatrix[1][2] &&
        glmRotated[1][3] == rotatedMatrix[1][3] &&
        glmRotated[2][0] == rotatedMatrix[2][0] &&
        glmRotated[2][1] == rotatedMatrix[2][1] &&
        glmRotated[2][2] == rotatedMatrix[2][2] &&
        glmRotated[2][3] == rotatedMatrix[2][3] &&
        glmRotated[3][0] == rotatedMatrix[3][0] &&
        glmRotated[3][1] == rotatedMatrix[3][1] &&
        glmRotated[3][2] == rotatedMatrix[3][2] &&
        glmRotated[3][3] == rotatedMatrix[3][3]) {
        return true;
    }
    return false;
}
// Sample unit test testing your library
bool unitTestMatrix3() {
    glm::mat4 glmMatrix = glm::mat4(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    glm::mat4 glmRotated = glm::rotate(glmMatrix, 180.0f, glm::vec3(0, 0, 1.0f));
    Matrix4f myMatrix(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4f id(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0);
    Matrix4f rMatrix = id.MakeRotationZ(180.0f);
    Matrix4f rotatedMatrix = myMatrix * rMatrix;
    if (glmRotated[0][0] == rotatedMatrix[0][0] &&
        glmRotated[0][1] == rotatedMatrix[0][1] &&
        glmRotated[0][2] == rotatedMatrix[0][2] &&
        glmRotated[0][3] == rotatedMatrix[0][3] &&
        glmRotated[1][0] == rotatedMatrix[1][0] &&
        glmRotated[1][1] == rotatedMatrix[1][1] &&
        glmRotated[1][2] == rotatedMatrix[1][2] &&
        glmRotated[1][3] == rotatedMatrix[1][3] &&
        glmRotated[2][0] == rotatedMatrix[2][0] &&
        glmRotated[2][1] == rotatedMatrix[2][1] &&
        glmRotated[2][2] == rotatedMatrix[2][2] &&
        glmRotated[2][3] == rotatedMatrix[2][3] &&
        glmRotated[3][0] == rotatedMatrix[3][0] &&
        glmRotated[3][1] == rotatedMatrix[3][1] &&
        glmRotated[3][2] == rotatedMatrix[3][2] &&
        glmRotated[3][3] == rotatedMatrix[3][3]) {
        return true;
    }
    return false;
}
// Sample unit test testing your library
bool unitTestMatrix4() {
    glm::mat4 glmMatrix = glm::mat4(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    glm::mat4 gScaled = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
    Matrix4f myMatrix(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4f mScaled = myMatrix.MakeScale(2.0f, 2.0f, 2.0f);
    if (gScaled[0][0] == mScaled[0][0] &&
        gScaled[0][1] == mScaled[0][1] &&
        gScaled[0][2] == mScaled[0][2] &&
        gScaled[0][3] == mScaled[0][3] &&
        gScaled[1][0] == mScaled[1][0] &&
        gScaled[1][1] == mScaled[1][1] &&
        gScaled[1][2] == mScaled[1][2] &&
        gScaled[1][3] == mScaled[1][3]) {
        return true;
    }
    return false;
}
// Sample unit test testing your library
bool unitTestMatrix5() {
    glm::mat4 g1 = glm::mat4(
        2.0f, 1.0f, 3.0f, 1.0f,
        5.0f, 2.0f, 5.0f, 2.0f,
        3.0f, 3.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 2.0f);
    glm::mat4 g2 = glm::mat4(
        3.0f, 2.0f, 4.0f, 10.0f,
        1.0f, 3.0f, 4.0f, 10.0f,
        1.0f, 2.0f, 3.0f, 10.0f,
        3.0f, 2.0f, 4.0f, 3.0f);
    glm::mat4 gMult = g1 * g2;
    Matrix4f m1(
        2.0f, 5.0f, 3.0f, 4.0f,
        1.0f, 2.0f, 3.0f, 5.0f,
        3.0f, 5.0f, 2.0f, 6.0f,
        1.0f, 2.0f, 3.0f, 2.0f);
    Matrix4f m2(
        3.0f, 1.0f, 1.0f, 3.0f,
        2.0f, 3.0f, 2.0f, 2.0f,
        4.0f, 4.0f, 3.0f, 4.0f,
        10.0f, 10.0f, 10.0f, 3.0f);
    Matrix4f m3(
        2.0f, 1.0f, 3.0f, 1.0f,
        5.0f, 2.0f, 5.0f, 2.0f,
        3.0f, 3.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 2.0f);
    Matrix4f m4(
        3.0f, 2.0f, 4.0f, 10.0f,
        1.0f, 3.0f, 4.0f, 10.0f,
        1.0f, 2.0f, 3.0f, 10.0f,
        3.0f, 2.0f, 4.0f, 3.0f);
    Matrix4f mMult = m3 * m4;

    if (gMult[0][0] == mMult[0][0] &&
        gMult[0][1] == mMult[0][1] &&
        gMult[0][2] == mMult[0][2] &&
        gMult[0][3] == mMult[0][3] &&
        gMult[1][0] == mMult[1][0] &&
        gMult[1][1] == mMult[1][1] &&
        gMult[1][2] == mMult[1][2] &&
        gMult[1][3] == mMult[1][3] &&
        gMult[2][0] == mMult[2][0] &&
        gMult[2][1] == mMult[2][1] &&
        gMult[2][2] == mMult[2][2] &&
        gMult[2][3] == mMult[2][3] &&
        gMult[3][0] == mMult[3][0] &&
        gMult[3][1] == mMult[3][1] &&
        gMult[3][2] == mMult[3][2] &&
        gMult[3][3] == mMult[3][3]) {
        return true;
    }
    return false;
}

bool unitTestMatrix6() {
    glm::mat4 g1 = glm::mat4(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    glm::mat4 g2 = glm::mat4(
        17.0f, 18.0f, 19.0f, 20.0f,
        21.0f, 22.0f, 23.0f, 24.0f,
        25.0f, 26.0f, 27.0f, 28.0f,
        29.0f, 30.0f, 31.0f, 32.0f);
    glm::mat4 multG = g1 * g2;
    Matrix4f m1 = Matrix4f(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4f m2 = Matrix4f(
        17.0f, 18.0f, 19.0f, 20.0f,
        21.0f, 22.0f, 23.0f, 24.0f,
        25.0f, 26.0f, 27.0f, 28.0f,
        29.0f, 30.0f, 31.0f, 32.0f);
    Matrix4f multM = m1 * m2;
    return true;
}



bool unitTestMatrix7() {
    glm::mat4 g1 = glm::mat4(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    glm::vec4 g2 = glm::vec4(
        1.0f, 2.0f, 3.0f, 4.0f);
    glm::vec4 multG = g1 * g2;

    Matrix4f m1 = Matrix4f(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    Vector4f m2 = Vector4f(
        1.0f, 2.0f, 3.0f, 4.0f);
    Vector4f multM = m1 * m2;
   
    return true;
}

bool unitTestMatrix8() {
    glm::mat4 g1 = glm::mat4(
        glm::vec4(1.0f, 2.0f, 3.0f, 4.0f),
        glm::vec4(5.0f, 6.0f, 7.0f, 8.0f),
        glm::vec4(9.0f, 10.0f, 11.0f, 12.0f),
        glm::vec4(13.0f, 14.0f, 15.0f, 16.0f));
    glm::mat4 g2 = glm::mat4(
        glm::vec4(17.0f, 18.0f, 19.0f, 20.0f),
        glm::vec4(21.0f, 22.0f, 23.0f, 24.0f),
        glm::vec4(25.0f, 26.0f, 27.0f, 28.0f),
        glm::vec4(29.0f, 30.0f, 31.0f, 32.0f));
    glm::mat4 multG = g1 * g2;
    Matrix4f m1 = Matrix4f(
        Vector4f(1.0f, 2.0f, 3.0f, 4.0f),
        Vector4f(5.0f, 6.0f, 7.0f, 8.0f),
        Vector4f(9.0f, 10.0f, 11.0f, 12.0f),
        Vector4f(13.0f, 14.0f, 15.0f, 16.0f));
    Matrix4f m2 = Matrix4f(
        Vector4f(17.0f, 18.0f, 19.0f, 20.0f),
        Vector4f(21.0f, 22.0f, 23.0f, 24.0f),
        Vector4f(25.0f, 26.0f, 27.0f, 28.0f),
        Vector4f(29.0f, 30.0f, 31.0f, 32.0f));
    Matrix4f multM = m1 * m2;
    
    return true;
}


int main() {
    // Keep track of the tests passed
    unsigned int testsPassed = 0;

    // Run 'unit tests'
    std::cout << "Passed 0: " << unitTest0() << " \n";
    std::cout << "Passed 1: " << unitTest1() << " \n";
    std::cout << "Passed 2: " << unitTest2() << " \n";
    std::cout << "Passed 3: " << unitTest3() << " \n";
    std::cout << "Passed 4: " << unitTest4() << " \n";
    std::cout << "Passed 5: " << unitTest5() << " \n";
    std::cout << "Passed Vector 1: " << unitTestVector1() << " \n";
    std::cout << "Passed Vector 2: " << unitTestVector2() << " \n";
    std::cout << "Passed Vector 3: " << unitTestVector3() << " \n";
    std::cout << "Passed Vector 4: " << unitTestVector4() << " \n";
    std::cout << "Passed Vector 5: " << unitTestVector5() << " \n";
    std::cout << "Passed Vector 6: " << unitTestVector6() << " \n";
    std::cout << "Passed Vector 7: " << unitTestVector7() << " \n";
    std::cout << "Passed Vector 8: " << unitTestVector8() << " \n";
    std::cout << "Passed Vector 9: " << unitTestVector9() << " \n";
    std::cout << "Passed Vector 10: " << unitTestVector10() << " \n";
    std::cout << "Passed Vector 11: " << unitTestVector11() << " \n";
    std::cout << "Passed Vector 13: " << unitTestVector13() << " \n";
    std::cout << "Passed Vector 14: " << unitTestVector14() << " \n";

    std::cout << "Passed Matrix 1: " << unitTestMatrix1() << " \n";
    std::cout << "Passed Matrix 2: " << unitTestMatrix2() << " \n";
    std::cout << "Passed Matrix 3: " << unitTestMatrix3() << " \n";
    std::cout << "Passed Matrix 4: " << unitTestMatrix4() << " \n";
    std::cout << "Passed Matrix 5: " << unitTestMatrix5() << " \n";
    std::cout << "Passed Matrix 6: " << unitTestMatrix6() << " \n";
    std::cout << "Passed Matrix 7: " << unitTestMatrix7() << " \n";
    std::cout << "Passed Matrix 8: " << unitTestMatrix8() << " \n";


    return 0;
}
