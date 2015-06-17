#ifndef LevelMap_h__
#define LevelMap_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>

#include "GraphicsDevice/ShaderProgram.h"
#include "Scene/Model3D.h"

class LevelMap
{
	
public:
	std::vector<Model3D> Objects;
	std::vector<glm::mat4> ObjectsM;
	LevelMap();
	void Initialize();
	void Draw(ShaderProgram shader);
	~LevelMap();
};

#endif