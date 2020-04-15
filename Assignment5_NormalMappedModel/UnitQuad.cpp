#include "UnitQuad.h"

UnitQuad::UnitQuad() : lightPos_(0.5f, 0.5f, -2.0f), sign_(1.0f)
{
}

UnitQuad::~UnitQuad()
{
}

void UnitQuad::init(const QString& textureFile, const QString& normalFile, std::vector<float>& positions, std::vector<unsigned int>& indexes)
{
    Renderable::init(positions, indexes, textureFile, normalFile);
}

void UnitQuad::update(const qint64 msSinceLastFrame)
{
    // This is where we want to maintain our light.
    float secs = (float)msSinceLastFrame / 1000.0f;
    float angle = secs * 180.0f;
    float angle2 = secs * 450.0f;
    // Rotate our light around the scene
    QMatrix4x4 rot;
    rot.setToIdentity();
    rot.rotate(angle, 0.0, 1.0, 0.0);
    QVector3D newPos = rot * lightPos_;

    lightPos_ = newPos;

    // Because we aren't doing any occlusion, the lighting on the walls looks
    // super wonky.  Instead, just move the light on the z axis.
    newPos.setX(0.5);

    // TODO:  Understand how the light gets initialized/setup.
    shader_.bind();
    shader_.setUniformValue("pointLights[0].color", 1.0f, 1.0f, 1.0f);
    shader_.setUniformValue("pointLights[0].position", newPos);

    shader_.setUniformValue("pointLights[0].ambientIntensity", 0.5f);
    shader_.setUniformValue("pointLights[0].specularStrength", 0.5f);
    shader_.setUniformValue("pointLights[0].constant", 1.0f);
    shader_.setUniformValue("pointLights[0].linear", 0.09f);
    shader_.setUniformValue("pointLights[0].quadratic", 0.032f);

    shader_.release();
}