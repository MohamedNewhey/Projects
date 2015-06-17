#ifndef GraphicsDevice_h__
#define GraphicsDevice_h__

#include <gl/glew.h>
#include "Shaders/shader.hpp"


class ShaderProgram
{
	public:
	GLuint programID;
	GLuint mRenderingModeID;
	GLuint modelMatrixID;
	GLuint vpMatrixID;
	GLuint mode;

	ShaderProgram();
	~ShaderProgram();

	void BindModelMatrix(GLfloat* value);
	void BindVPMatrix(GLfloat* value);
	void BindRenderMode(GLuint value);
	
	//calls glUseProgram.
	void UseProgram();
	//load shaders from files.
	virtual void LoadProgram();
	void CleanUp();
};

#endif // GraphicsDevice_h__