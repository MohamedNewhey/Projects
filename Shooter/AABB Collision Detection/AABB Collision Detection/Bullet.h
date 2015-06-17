#ifndef Bullet_h__
#define Bullet_h__

#include "Scene/Model3D.h"


class Bullet : public Model3D
{

	float Maxdistance,Traveld,Speed;
	glm::vec3 Poistion,Direction;
	bool destorid;
	//ShaderProgram *shader;
	glm::mat4 Modelmatrix,Initial;
public: 
	Bullet(glm::vec3 start ,glm::vec3 Sdir);
	//void Draw(ShaderProgram *sent,glm::mat4 VP);
	//void SetShader(ShaderProgram *sent);
	void UpdatePos(float delta);
	virtual void Collided(ObjectType CollType);
	~Bullet();
};

#endif

