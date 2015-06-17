#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Shaders/shader.hpp"
#include "Model/Model.h"
#include "EulerCamera/EulerCamera.h"
#include "Texture/texture.h"
#include "GraphicsDevice/ShaderProgram.h"
#include "Scene/Model3D.h"
#include "GraphicsDevice/KeyFrameAnimationShader.h"
#include "MD2Model/md2model.h"
#include "CollisionDetection/CollisionManager.h"
#include "LevelMap.h"
#include "Enemy.h"
#include "Bullet.h"
#include "SkyBox\SkyBox.h"

struct StaticModelShaderAttributes
{
public:
	// Vertex attributes
	GLuint vertexPosition_modelspaceID, inputColorID, texCoordID, vertexNormal_modelspaceID;
};


class Renderer
{

	
    KeyFrameAnimationShader animatedModelShader;
	ShaderProgram staticModelShader;
	// Transformation
	GLuint AmbientLightID;
	GLuint LightPositionID;
	GLuint EyePositionID;
	GLuint AmientlightColorID;
	GLuint DiflightColorID;
	GLuint SpeclightColorID;


	std::unique_ptr<Model> floor;
	std::unique_ptr<Model> cursor;
	std::unique_ptr<Texture> floorTexture;
	std::vector<Bullet*> bullets;
	//Level1 Objects
	std::unique_ptr<LevelMap> level1;
	vector <std::unique_ptr< Enemy >>  enemy;

	std::unique_ptr<EulerCamera> myCamera;
	std::unique_ptr<Model3D> Gun;
	glm::mat4 MGun;
	std::unique_ptr<SkyBox> GSkyBox;

	glm::mat4 floorM;
	glm::mat4 cursorM;

	glm::vec3 ambientLight;
	glm::vec3 lightPosition;

	glm::mat4 initVP;


	std::unique_ptr<CollisionManager> collisionManager;
	StaticModelShaderAttributes staticModelShaderAttr;


public:
    Renderer();
    ~Renderer();
    
    void Initialize();
    void Draw();
	void HandleKeyboardInput(int key);
	void HandleMouse(double deltaX,double deltaY);
	void HandleMouseButtons(int button);
	void Update(double deltaTime);
    void Cleanup();
};

#endif // Renderer_h__

