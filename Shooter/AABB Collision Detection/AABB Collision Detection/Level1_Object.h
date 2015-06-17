#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Scene/Model3D.h"
#include "Model/Model.h"

class Level1_Object
{

	std::vector<Model3D> Objects;
	std::vector<glm::mat4> ObjectsM;

public:
	
	Level1_Object();
	void Initialize();
	void Draw(ShaderProgram shader);
};

