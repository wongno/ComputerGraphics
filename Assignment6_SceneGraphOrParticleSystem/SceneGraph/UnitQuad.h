#pragma once

#include "Renderable.h"
#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <vector>

class UnitQuad : public Renderable
{
protected:
	QVector3D lightPos_;
	QVector3D lightPos2_;
	QVector3D lightPos3_;
	QVector3D lightPos4_;
	float sign_;

public:
	UnitQuad();
	virtual ~UnitQuad();

	// Our init method is much easier now.  We only need a texture!
	virtual void init(const QString& textureFile, std::vector<float>& positions, std::vector<unsigned int>& indexes);
	virtual void update(const qint64 msSinceLastFrame) override;

private:
};