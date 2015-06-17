#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::LoadProgram()
{
	programID = LoadShaders( "SimpleTransformWithColor.vertexshader", "TextureLighting.fragmentshader");

	modelMatrixID = glGetUniformLocation(programID, "ModelMatrix");

	vpMatrixID = glGetUniformLocation(programID, "VP");

	mode = glGetUniformLocation(programID, "mode");
}

void ShaderProgram::BindModelMatrix(GLfloat* value)
{
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, value);
}

void ShaderProgram::BindVPMatrix(GLfloat* value)
{
	glUniformMatrix4fv(vpMatrixID, 1, GL_FALSE, value);
}

void ShaderProgram::BindRenderMode(GLuint value)
{
	glUniform1i(mode, value);
}

void ShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

void ShaderProgram::CleanUp()
{
	glDeleteProgram(programID);
}