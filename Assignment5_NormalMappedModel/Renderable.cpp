#include "Renderable.h"

#include <QtGui>
#include <QtOpenGL>

Renderable::Renderable() : vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer), texture_(QOpenGLTexture::Target2D), bumpTexture_(QOpenGLTexture::Target2D), numTris_(0), vertexSize_(0), rotationAxis_(0.0, 0.0, 1.0), rotationSpeed_(0.25)
{
	rotationAngle_ = 0.0;
}

Renderable::~Renderable()
{
	if (texture_.isCreated())
	{
		texture_.destroy();
	}
	if (bumpTexture_.isCreated())
	{
		bumpTexture_.destroy();
	}
	if (vbo_.isCreated())
	{
		vbo_.destroy();
	}
	if (ibo_.isCreated())
	{
		ibo_.destroy();
	}
	if (vao_.isCreated())
	{
		vao_.destroy();
	}
}

void Renderable::createShaders()
{
	QString vertexFilename = "../vert.glsl";
	bool ok = shader_.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexFilename);
	if (!ok)
	{
		qDebug() << shader_.log();
	}
	QString fragmentFilename = "../frag.glsl";
	ok = shader_.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentFilename);
	if (!ok)
	{
		qDebug() << shader_.log();
	}
	ok = shader_.link();
	if (!ok)
	{
		qDebug() << shader_.log();
	}
}

void Renderable::init(std::vector<float>& positions, std::vector<unsigned int>& indexes, const QString& textureFile, const QString& normalFile)
{

	// Set our model matrix to identity
	modelMatrix_.setToIdentity();
	// Load our texture.
	QImage myImage(textureFile);

	myImage = myImage.mirrored(true, true);
	texture_.setData(myImage);

	// load normal texture
	QImage bumpImage(normalFile);
	bumpImage = bumpImage.mirrored(true, true);
	bumpTexture_.setData(bumpImage);

	// set our number of trianges.
	numTris_ = indexes.size() / 3;

	// num verts (used to size our vbo)
	int numVerts = positions.size();
	vertexSize_ = 3 + 2 + 3 + 3 + 3; // Position + normal + texCoord + tangent + bitangent
	int numVBOEntries = numVerts * vertexSize_;

	// Setup our shader.
	createShaders();

	// Now we can set up our buffers.
	// The VBO is created -- now we must create our VAO
	vao_.create();
	vao_.bind();
	vbo_.create();
	vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbo_.bind();

	float* data = &positions[0];
	vbo_.allocate(data, positions.size() * sizeof(float));

	// Create our index buffer
	ibo_.create();
	ibo_.bind();
	ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

	unsigned int* facesArr = &indexes[0];
	ibo_.allocate(facesArr, indexes.size() * sizeof(unsigned int));

	// Make sure we setup our shader inputs properly
	shader_.enableAttributeArray(0);
	shader_.setAttributeBuffer(0, GL_FLOAT, 0, 3, vertexSize_ * sizeof(float));

	shader_.enableAttributeArray(1);
	shader_.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 2, vertexSize_ * sizeof(float));

	shader_.enableAttributeArray(2);
	shader_.setAttributeBuffer(2, GL_FLOAT, 5 * sizeof(float), 3, vertexSize_ * sizeof(float));

	shader_.enableAttributeArray(3);
	shader_.setAttributeBuffer(3, GL_FLOAT, 8 * sizeof(float), 3, vertexSize_ * sizeof(float));

	shader_.enableAttributeArray(4);
	shader_.setAttributeBuffer(4, GL_FLOAT, 11 * sizeof(float), 3, vertexSize_ * sizeof(float));

	// Release our vao and THEN release our buffers.
	vao_.release();
	vbo_.release();
	ibo_.release();
}

void Renderable::update(const qint64 msSinceLastFrame)
{
	// For this lab, we want our polygon to rotate.
	float sec = msSinceLastFrame / 1000.0f;
	float anglePart = sec * rotationSpeed_ * 360.f;
	rotationAngle_ += anglePart;
	while (rotationAngle_ >= 360.0)
	{
		rotationAngle_ -= 360.0;
	}
}

void Renderable::draw(const QMatrix4x4& world, const QMatrix4x4& view, const QMatrix4x4& projection)
{
	// Create our model matrix.
	QMatrix4x4 rotMatrix;
	rotMatrix.setToIdentity();
	rotMatrix.rotate(rotationAngle_, rotationAxis_);

	// incorporate a real world transform if want it.
	QMatrix4x4 modelMat = modelMatrix_ * rotMatrix;
	modelMat = world * modelMat;
	// Make sure our state is what we want
	shader_.bind();
	// Set our matrix uniforms!
	QMatrix4x4 id;
	id.setToIdentity();
	shader_.setUniformValue("modelMatrix", modelMat);
	shader_.setUniformValue("viewMatrix", view);
	shader_.setUniformValue("projectionMatrix", projection);

	vao_.bind();

	//glActiveTexture(GL_TEXTURE0);

	texture_.bind();
	// // And our color texture at Texture Unit 1.
	//glActiveTexture(GL_TEXTURE1);
	bumpTexture_.bind();

	// TODO: I had to comment this out for my mac, but you might need this on windows
	// shader_.setUniformValue("tex", GL_TEXTURE0);
	shader_.setUniformValue("bumpTex", GL_TEXTURE1 - GL_TEXTURE0);

	glDrawElements(GL_TRIANGLES, numTris_ * 3, GL_UNSIGNED_INT, 0);
	texture_.release();
	bumpTexture_.release();
	vao_.release();
	shader_.release();
}

void Renderable::setModelMatrix(const QMatrix4x4& transform)
{
	modelMatrix_ = transform;
}

void Renderable::setRotationAxis(const QVector3D& axis)
{
	rotationAxis_ = axis;
}

void Renderable::setRotationSpeed(float speed)
{
	rotationSpeed_ = speed;
}