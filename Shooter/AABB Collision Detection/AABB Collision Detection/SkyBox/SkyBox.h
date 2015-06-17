#ifndef __SKYBOX
#define __SKYBOX

#include "Model\Model.h"
#include "Texture/texture.h"
#include "GraphicsDevice/ShaderProgram.h"
#include <memory>

#define LEFT_NORMAL glm::vec3(1.0, 0.0, 0.0)
#define FRONT_NORMAL glm::vec3(0.0, 0.0, 1.0) 
#define BOTTOM_NORMAL glm::vec3(0.0, 1.0, 0.0)
#define BACK_NORMAL glm::vec3(0.0, 0.0, -1.0)
#define RIGHT_NORMAL glm::vec3(-1.0, 0.0, 0.0)
#define TOP_NORMAL glm::vec3(0.0, -1.0, 0.0)

class SkyBox
{

	std::unique_ptr<Model> skyBoxModel;
	std::unique_ptr<Texture> skyBoxTexture;

public:
	SkyBox(void);
	~SkyBox(void);

	glm::mat4 skyBoxModelMatrix;

	void Initialize();
	void Draw(GLuint vertexPosition_modelspaceID, GLuint inputColorID, GLuint texCoordID, GLuint vertexNormal_modelspaceID,ShaderProgram* shader, glm::mat4 VP);
	void Cleanup();
};

#endif