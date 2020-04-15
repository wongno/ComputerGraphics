#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <vector>

#include "Renderable.h"

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */

class TreeNode
{



public:
    TreeNode();
    virtual ~TreeNode();

    // initialize Tree Node
    void init(const QString& textureFile, QString name, QMatrix4x4 localMatrix, float scaleSize);

    // update world matrix of this node and all children
    void updateWorldMatrix();

    // rotate local matrix based on frame seconds
    void update(const qint64 msSinceLastFrame);

    // draw TreeNode and child nodes
    void draw(const QMatrix4x4& view, const QMatrix4x4& projection);

    // add child to node
    void addChild(TreeNode* child);

    // set parent of this node to given node
    void setParent(TreeNode* node);

    // get name of this node
    QString getName() {
        return name_;
    }

    // get world matrix
    QMatrix4x4 getWorldMatrix();

private:
    // renderable object
    Renderable* renderable_;
    // name of tree (useful for debuggin)
    QString name_;
    // matrix that represents the world
    QMatrix4x4 worldMatrix_;
    // matrix that represents position of this node
    QMatrix4x4 localMatrix_;
    // children
    std::vector<TreeNode*> children_;
    // parent node
    TreeNode* parent_;
    // how big or small this node should be
    float scaleSize_;
};