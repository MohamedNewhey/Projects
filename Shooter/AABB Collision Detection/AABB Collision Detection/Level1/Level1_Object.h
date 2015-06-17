#pragma once
#include "Renderer\Renderer.h"
class Level1_Object
{

	

public:
	std::vector<Model3D> Objects;
	std::vector<glm::mat4> ObjectsM;
	Level1_Object();
	void Initialize();
	void Draw(ShaderProgram shader);
	~Level1_Object();
};

