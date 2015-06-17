#include "MD2Model\md2model.h"
class Enemy : public CMD2Model
{

	KeyFrameAnimationShader * Eshader;
	animState_t EanimationState;
	glm::vec3 Position,Direction;
	float speed;
	glm::mat4 EModelMatrix, Initial;
	bool dead;
	int health;
	
public:

	Enemy(KeyFrameAnimationShader *shader, glm::vec3 start );
	void Initialize(char* path);
	void updateanimation(float delta);
	void Render(glm::mat4 VP);
	void UpdateMove(float delta);
	virtual void Collided(ObjectType CollType);
	~Enemy();
};

