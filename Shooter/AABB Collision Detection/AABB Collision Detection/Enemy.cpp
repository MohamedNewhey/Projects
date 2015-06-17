#include "Enemy.h"


Enemy::Enemy(KeyFrameAnimationShader *shader,glm::vec3 start )
{
	speed = 0.08f;
	Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	Position = start;
	Initial = glm::rotate(-90.0f, 1.0f, 0.0f, 0.0f)*glm::scale(0.01f, 0.01f, 0.01f);
	EModelMatrix = glm::translate(Position) * Initial;
	type = ObjectType::ENEMY;
	Eshader = shader;
	dead = false;
	health = 100;
}

void Enemy::Initialize( char* path)
{

	CMD2Model::LoadModel(path);
	EanimationState = this->StartAnimation(animType_t::STAND);
	CMD2Model::SetBoundingBox(CollidableModel::CalculateBoundingBox(CMD2Model::GetVertices()));
	auto bound = CMD2Model::GetBoundingBox();
	bound.Scale(0.01f, 0.01f, 0.01f);
	bound.Translate(Position);
	CMD2Model::SetBoundingBox(bound);
	
}


void Enemy::updateanimation(float delta)
{
	if (CMD2Model::UpdateAnimation(&EanimationState, delta, dead))
	{
		if (!dead)
		{
			EanimationState = CMD2Model::StartAnimation(animType_t::STAND);
		}
	}
}

void Enemy::Render(glm::mat4 VP)
{

	if (dead == true)
	{
		//EanimationState = CMD2Model::StartAnimation(animType_t::DEATH_FALLBACKSLOW);
		//CMD2Model::PauseAnimation();
	}
	Eshader->UseProgram();
	Eshader->BindModelMatrix(&EModelMatrix[0][0]);
	Eshader->BindVPMatrix(&VP[0][0]);
	CMD2Model::RenderModel(&EanimationState, Eshader);
}


void Enemy::Collided(ObjectType CollType)
{
	if (CollType == ObjectType::PLAYER)
	{
		//printf("Enemy attack \n");
	}
	else  if (CollType==ObjectType::BULLET)
	{
		health -= 10;

			EanimationState = CMD2Model::StartAnimation(animType_t::PAIN_B);
			//CMD2Model::PauseAnimation();

			if (health < 0)
			{
				EanimationState = CMD2Model::StartAnimation(animType_t::DEATH_FALLBACKSLOW);
			}
				dead = true;
	}
}

void Enemy::UpdateMove(float delta)
{

		EanimationState = CMD2Model::StartAnimation(animType_t::RUN);


	float dist = speed * delta;
	auto newpos = Position;
	auto direc = Direction;
	newpos += dist*Direction;
	Position = newpos;
	EModelMatrix = glm::translate(Position)*Initial;
	//glm::vec3 plcenter = Position;
	auto bound = CMD2Model::GetBoundingBox();
	bound.SetCenter(Position);
	CMD2Model::SetBoundingBox(bound);
}
Enemy::~Enemy()
{
}
