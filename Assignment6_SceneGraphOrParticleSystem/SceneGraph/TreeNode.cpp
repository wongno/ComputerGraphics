#include "TreeNode.h"
#include "Sphere.h"

#include <QtGui>
#include <QtOpenGL>



TreeNode::TreeNode()
{
}

TreeNode::~TreeNode()
{
}

void TreeNode::init(const QString& textureFile, QString name, QMatrix4x4 localMatrix, float scaleSize) {
    name_ = name;
    localMatrix_ = localMatrix;
    worldMatrix_ = localMatrix_;
    parent_ = NULL;
    scaleSize_ = scaleSize;

    // create a sphere with proper vertices and indices
    Sphere planet = Sphere();
    std::vector<float> vertexInfo = planet.getVertexInfo();
    std::vector<unsigned int> faces = planet.indexes();

    // create a renderable with local matrix as world
    Renderable* ren = new Renderable();
    ren->init(vertexInfo, faces, textureFile);
    ren->setModelMatrix(localMatrix);
    renderable_ = ren;

}



void TreeNode::updateWorldMatrix() {

    if (parent_ != NULL) {
        worldMatrix_ = parent_->getWorldMatrix() * localMatrix_;

    }

    else {
        worldMatrix_ = localMatrix_;
    }


    for (auto child : children_)
    {

        child->updateWorldMatrix();
    }


}

void TreeNode::draw(const QMatrix4x4& view, const QMatrix4x4& projection) {

    renderable_->draw(worldMatrix_, view, projection, scaleSize_);


    for (auto child : children_)
    {

        child->draw(view, projection);
    }
}

void TreeNode::update(const qint64 msSinceLastFrame) {

    // this triggers the rotation
    float sec = msSinceLastFrame / 1000.0f;
    float anglePart = sec * .1 * 360.f;

    QMatrix4x4 rotationMatrix;
    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(anglePart, QVector3D(0, 1, 0));
    // rotate the localMatrix world
    localMatrix_ = localMatrix_ * rotationMatrix;

    for (auto child : children_)
    {
        child->update(msSinceLastFrame);
    }
}

void TreeNode::addChild(TreeNode* child) {
    children_.push_back(child);

    QString name = child->getName();

    child->setParent(this);

}

void TreeNode::setParent(TreeNode* node) {
    parent_ = node;
}

QMatrix4x4 TreeNode::getWorldMatrix() {
    return worldMatrix_;
}