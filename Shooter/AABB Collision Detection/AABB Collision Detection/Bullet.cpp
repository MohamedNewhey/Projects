#include "Bullet.h"


Bullet::Bullet(glm::vec3 start ,glm::vec3 Sdir)
{
	Poistion = start;
	Direction = Sdir;
	type = ObjectType::BULLET;
	destorid = false;
	Speed = 10.0;
	Maxdistance = 10;
	Traveld = 0;
	//Initial =  glm::scale(0.001f, 0.001f, 0.001f);
	AABoundingBox box = AABoundingBox(Poistion, glm::vec3(0.2f, 0.2f, 0.2f));
	Model3D::SetBoundingBox(box);
}


//void Bullet::Draw(ShaderProgram *sent,glm::mat4 VP)
//{
//	sent->UseProgram();
//	sent->BindModelMatrix(&Modelmatrix[0][0]);
//	sent->BindVPMatrix(&VP[0][0]);
//	//Model3D::Render(sent, Modelmatrix);
//}


void Bullet::UpdatePos(float delta)
{	
	float dist = Speed * delta;
	//Traveld += dist;
	auto newpos = Poistion;
	auto direc = Direction;
	newpos += dist*Direction;
	Poistion = newpos;
	//Modelmatrix = glm::translate(Poistion)*Initial;
	glm::vec3 plcenter = Poistion;
	AABoundingBox plbox(plcenter, glm::vec3(0.2f, 0.2f, 0.2f));
	Model3D::SetBoundingBox(plbox);

}

void Bullet::Collided(ObjectType colltype)
{
	if (colltype == ObjectType::ENEMY)
		printf("Bullet Class colllided with enemy \n");
	destorid = true;
}
Bullet::~Bullet()
{

}
