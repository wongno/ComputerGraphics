#include <QtGui>
#include <QtOpenGL>

#include "Tree.h"



Tree::Tree()
{
}

Tree::~Tree()
{
}

void Tree::setRoot(TreeNode* t) {
    root_ = t;
}

void Tree::traverse(const qint64 msSinceLastFrame, const QMatrix4x4& view, const QMatrix4x4& projection) {
    root_->update(msSinceLastFrame);
    root_->updateWorldMatrix();
    root_->draw(view, projection);

}