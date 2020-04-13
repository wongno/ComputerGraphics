#pragma once

#include "Renderable.h"

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
	virtual void init(const QString& textureFile);
	virtual void update(const qint64 msSinceLastFrame) override;

private:
};