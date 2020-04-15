#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

#include "TreeNode.h"

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */

class Tree
{

public:
    Tree();
    virtual ~Tree();

    // sets root of this Tree
    void setRoot(TreeNode* t);

    // updates and draws all nodes
    void traverse(const qint64 msSinceLastFrame, const QMatrix4x4& view, const QMatrix4x4& projection);

private:
    // root of tree
    TreeNode* root_;
};