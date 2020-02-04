// High level design note
// Our matrix should match the behavior of the glm library.
#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <cmath>

// We need to Vector4f header in order to multiply a matrix
// by a vector.
#include "Vector4f.h"

// Matrix 4f represents 4x4 matrices in Math
struct Matrix4f {
private:
    float n[4][4];  // Store each value of the matrix

public:
    Matrix4f() = default;

    // TODO: Row or column major order you decide!
    // Matrix constructor with 9 scalar values.
    Matrix4f(float n00, float n01, float n02, float n03,
        float n10, float n11, float n12, float n13,
        float n20, float n21, float n22, float n23,
        float n30, float n31, float n32, float n33) {

        /* n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = n30;
         n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = n31;
         n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = n32;
         n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = n33;*/
        n[0][0] = n00; n[0][1] = n01; n[0][2] = n02; n[0][3] = n03;
        n[1][0] = n10; n[1][1] = n11; n[1][2] = n12; n[1][3] = n13;
        n[2][0] = n20; n[2][1] = n21; n[2][2] = n22; n[2][3] = n23;
        n[3][0] = n30; n[3][1] = n31; n[3][2] = n32; n[3][3] = n33;
    }

    // Matrix constructor from four vectors.
    // Note: 'd' will almost always be 0,0,0,1
    Matrix4f(const Vector4f& a, const Vector4f& b, const Vector4f& c, const Vector4f& d) {
        /*   n[0][0] = a.x; n[0][1] = b.x; n[0][2] = c.x; n[0][3] = d.x;
           n[1][0] = a.y; n[1][1] = b.y; n[1][2] = c.y; n[1][3] = d.y;
           n[2][0] = a.z; n[2][1] = b.z; n[2][2] = c.z; n[2][3] = d.z;
           n[3][0] = a.w; n[3][1] = b.w; n[3][2] = c.w; n[3][3] = d.w;*/
        n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; n[0][3] = a.w;
        n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; n[1][3] = b.w;
        n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; n[2][3] = c.w;
        n[3][0] = d.x; n[3][1] = d.y; n[3][2] = d.z; n[3][3] = d.w;
    }

    // Makes the matrix an identity matrix
    void identity() {
        // TODO:
        n[0][0] = 1.0f; n[0][1] = 0; n[0][2] = 0; n[0][3] = 0;
        n[1][0] = 0; n[1][1] = 1.0f; n[1][2] = 0; n[1][3] = 0;
        n[2][0] = 0; n[2][1] = 0; n[2][2] = 1.0f; n[2][3] = 0;
        n[3][0] = 0; n[3][1] = 0; n[3][2] = 0; n[3][3] = 1.0f;

    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    float& operator ()(int i, int j) {
        return (n[j][i]);
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    const float& operator ()(int i, int j) const {
        return (n[j][i]);
    }

    // Return a single  vector from the matrix (row or columnn major? hmm).
    Vector4f& operator [](int j) {
        return (*reinterpret_cast<Vector4f*>(n[j]));
    }

    // Return a single  vector from the matrix (row or columnn major? hmm).
    const Vector4f& operator [](int j) const {
        return (*reinterpret_cast<const Vector4f*>(n[j]));
    }

    // Make a matrix rotate about various axis
    Matrix4f MakeRotationX(float t) {
        // TODO:
        Matrix4f n;

        n[0][0] = 1; n[0][1] = 0; n[0][2] = 0; n[0][3] = 0;
        n[1][0] = 0; n[1][1] = cos(t); n[2][1] = -sin(t); n[1][3] = 0;
        n[2][0] = 0; n[1][2] = sin(t); n[2][2] = cos(t); n[2][3] = 0;
        n[3][0] = 0; n[3][1] = 0; n[3][2] = 0; n[3][3] = 1;

        /*n[0][0] = 1; n[1][0] = 0; n[2][0] = 0; n[3][0] = 0;
        n[0][1] = 0; n[1][1] = cos(t); n[2][1] = -sin(t); n[3][1] = 0;
        n[0][2] = 0; n[1][2] = sin(t); n[2][2] = cos(t); n[3][2] = 0;
        n[0][3] = 0; n[1][3] = 0; n[2][3] = 0; n[3][3] = 1;*/
        return(n); // You will need to modify this.
                            // When you test, test against glm_gtx_transform
    }
    Matrix4f MakeRotationY(float t) {
        // TODO:
        Matrix4f n;
        n[0][0] = cos(t); n[1][0] = 0; n[2][0] = sin(t); n[3][0] = 0;
        n[0][1] = 0;      n[1][1] = 1; n[2][1] = 0;      n[3][1] = 0;
        n[0][2] = -sin(t); n[1][2] = 0; n[2][2] = cos(t); n[3][2] = 0;
        n[0][3] = 0;       n[1][3] = 0; n[2][3] = 0;       n[3][3] = 1;
        return(n); // You will need to modify this.
                            // When you test, test against glm_gtx_transform
    }
    Matrix4f MakeRotationZ(float t) {
        // TODO:
        Matrix4f n;
        n[0][0] = cos(t); n[1][0] = -sin(t); n[2][0] = 0; n[3][0] = 0;
        n[0][1] = sin(t);      n[1][1] = cos(t); n[2][1] = 0;      n[3][1] = 0;
        n[0][2] = 0; n[1][2] = 0; n[2][2] = 1; n[3][2] = 0;
        n[0][3] = 0;       n[1][3] = 0; n[2][3] = 0;       n[3][3] = 1;
        return(n); // You will need to modify this.
                            // When you test, test against glm_gtx_transform
    }
    Matrix4f MakeScale(float sx, float sy, float sz) {
        // TODO:
        Matrix4f n;
        n[0][0] = sx; n[1][0] = 0; n[2][0] = 0; n[3][0] = 0;
        n[0][1] = 0;      n[1][1] = sy; n[2][1] = 0;      n[3][1] = 0;
        n[0][2] = 0; n[1][2] = 0; n[2][2] = sz; n[3][2] = 0;
        n[0][3] = 0;       n[1][3] = 0; n[2][3] = 0;       n[3][3] = 1;
        return(n); // You will need to modify this.
                            // When you test, test against glm_gtx_transform
    }
};

// Matrix Multiplication
Matrix4f operator *(const Matrix4f& A, const Matrix4f& B) {
    // TODO:
    Matrix4f n;
    n[0][0] = A[0][0] * B[0][0] + A[1][0] * B[0][1] + A[2][0] * B[0][2] + A[3][0] * B[0][3];
    n[0][1] = A[0][1] * B[0][0] + A[1][1] * B[0][1] + A[2][1] * B[0][2] + A[3][1] * B[0][3];
    n[0][2] = A[0][2] * B[0][0] + A[1][2] * B[0][1] + A[2][2] * B[0][2] + A[3][2] * B[0][3];
    n[0][3] = A[0][3] * B[0][0] + A[1][3] * B[0][1] + A[2][3] * B[0][2] + A[3][3] * B[0][3];

    n[1][0] = A[0][0] * B[1][0] + A[1][0] * B[1][1] + A[2][0] * B[1][2] + A[3][0] * B[1][3];
    n[1][1] = A[0][1] * B[1][0] + A[1][1] * B[1][1] + A[2][1] * B[1][2] + A[3][1] * B[1][3];
    n[1][2] = A[0][2] * B[1][0] + A[1][2] * B[1][1] + A[2][2] * B[1][2] + A[3][2] * B[1][3];
    n[1][3] = A[0][3] * B[1][0] + A[1][3] * B[1][1] + A[2][3] * B[1][2] + A[3][3] * B[1][3];

    n[2][0] = A[0][0] * B[2][0] + A[1][0] * B[2][1] + A[2][0] * B[2][2] + A[3][0] * B[2][3];
    n[2][1] = A[0][1] * B[2][0] + A[1][1] * B[2][1] + A[2][1] * B[2][2] + A[3][1] * B[2][3];
    n[2][2] = A[0][2] * B[2][0] + A[1][2] * B[2][1] + A[2][2] * B[2][2] + A[3][2] * B[2][3];
    n[2][3] = A[0][3] * B[2][0] + A[1][3] * B[2][1] + A[2][3] * B[2][2] + A[3][3] * B[2][3];

    n[3][0] = A[0][0] * B[3][0] + A[1][0] * B[3][1] + A[2][0] * B[3][2] + A[3][0] * B[3][3];
    n[3][1] = A[0][1] * B[3][0] + A[1][1] * B[3][1] + A[2][1] * B[3][2] + A[3][1] * B[3][3];
    n[3][2] = A[0][2] * B[3][0] + A[1][2] * B[3][1] + A[2][2] * B[3][2] + A[3][2] * B[3][3];
    n[3][3] = A[0][3] * B[3][0] + A[1][3] * B[3][1] + A[2][3] * B[3][2] + A[3][3] * B[3][3];
    /*n[0][0] = A[0][0] * B[0][0] + A[1][0] * B[0][1] + A[2][0] * B[0][2] + A[3][0] * B[0][3];
    n[1][0] = A[0][0] * B[1][0] + A[1][0] * B[1][1] + A[2][0] * B[1][2] + A[3][0] * B[1][3];
    n[2][0] = A[0][0] * B[2][0] + A[1][0] * B[2][1] + A[2][0] * B[2][2] + A[3][0] * B[2][3];
    n[3][0] = A[0][0] * B[3][0] + A[1][0] * B[3][1] + A[2][0] * B[3][2] + A[3][0] * B[3][3];

    n[0][1] = A[0][1] * B[0][0] + A[1][1] * B[0][1] + A[2][1] * B[0][2] + A[3][1] * B[0][3];
    n[1][1] = A[0][1] * B[1][0] + A[1][1] * B[1][1] + A[2][1] * B[1][2] + A[3][1] * B[1][3];
    n[2][1] = A[0][1] * B[2][0] + A[1][1] * B[2][1] + A[2][1] * B[2][2] + A[3][1] * B[2][3];
    n[3][1] = A[0][1] * B[3][0] + A[1][1] * B[3][1] + A[2][1] * B[3][2] + A[3][1] * B[3][3];

    n[0][2] = A[0][2] * B[0][0] + A[1][2] * B[0][1] + A[2][2] * B[0][2] + A[3][2] * B[0][3];
    n[1][2] = A[0][2] * B[1][0] + A[1][2] * B[1][1] + A[2][2] * B[1][2] + A[3][2] * B[1][3];
    n[2][2] = A[0][2] * B[2][0] + A[1][2] * B[2][1] + A[2][2] * B[2][2] + A[3][2] * B[2][3];
    n[3][2] = A[0][2] * B[3][0] + A[1][2] * B[3][1] + A[2][2] * B[3][2] + A[3][2] * B[3][3];

    n[0][3] = A[0][3] * B[0][0] + A[1][3] * B[0][1] + A[2][3] * B[0][2] + A[3][3] * B[0][3];
    n[1][3] = A[0][3] * B[1][0] + A[1][3] * B[1][1] + A[2][3] * B[1][2] + A[3][3] * B[1][3];
    n[2][3] = A[0][3] * B[2][0] + A[1][3] * B[2][1] + A[2][3] * B[2][2] + A[3][3] * B[2][3];
    n[3][3] = A[0][3] * B[3][0] + A[1][3] * B[3][1] + A[2][3] * B[3][2] + A[3][3] * B[3][3];*/
    return n;
}

// Matrix multiply by a vector

Vector4f operator *(const Matrix4f& M, const Vector4f& v) {
    // TODO:
    Vector4f vec;
    /*vec.x = (M[0][0] * v.x + M[0][1] * v.y + M[0][2] * v.z + M[0][3] * v.w);
    vec.y = (M[1][0] * v.x + M[1][1] * v.y + M[1][2] * v.z + M[1][3] * v.w);
    vec.z = (M[2][0] * v.x + M[2][1] * v.y + M[2][2] * v.z + M[2][3] * v.w);
    vec.w = (M[3][0] * v.x + M[3][1] * v.y + M[3][2] * v.z + M[3][3] * v.w);*/
    vec.x = (M[0][0] * v.x + M[1][0] * v.y + M[2][0] * v.z + M[3][0] * v.w);
    vec.y = (M[0][1] * v.x + M[1][1] * v.y + M[2][1] * v.z + M[3][1] * v.w);
    vec.z = (M[0][2] * v.x + M[1][2] * v.y + M[2][2] * v.z + M[3][2] * v.w);
    vec.w = (M[0][3] * v.x + M[1][3] * v.y + M[2][3] * v.z + M[3][3] * v.w);

    return vec;
}


#endif
