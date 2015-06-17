#include <glm\glm.hpp>
#include "GraphicsDevice/ShaderProgram.h"
#include "GraphicsDevice/KeyFrameAnimationShader.h"
#include "MD2Model\md2model.h"
#include <math.h>
#include "Bullet.h"
class Player :public CMD2Model
{
	

	KeyFrameAnimationShader * Hshader;
	animState_t HanimationState;

public:
	glm::mat4 HModelMatrix;
	glm::mat4 Initial;
	glm::vec3 HDirection;
	float HAngle;
	glm::vec3 Hpos;

	Player(KeyFrameAnimationShader* shader);
	Player(KeyFrameAnimationShader* shader,glm::vec3 Npos, glm::vec3 dir);	
	void Initialize();
	void updateanimation(float delta);
	void Render(glm::mat4 VP);
	void Move(glm::vec3 Direction);
	void UpdateModel();
	Bullet Fire();
	~Player();

	virtual void Collided(ObjectType CollType);
};

