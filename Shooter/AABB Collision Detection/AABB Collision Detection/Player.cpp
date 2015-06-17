#include "Player.h"


Player::Player(KeyFrameAnimationShader *shader)
{
	type=ObjectType::PLAYER;
	HanimationState = this->StartAnimation(animType_t::STAND);
	Hshader = shader;
	Hpos = glm::vec3(0);
	HDirection = glm::vec3(1.0f, 0.0f, 0.0f);
	HAngle = 0;
	HModelMatrix = glm::mat4(1);
	Initialize();

}


Player::Player(KeyFrameAnimationShader *shader, glm::vec3 Npos, glm::vec3 dir)
{
	type = ObjectType::PLAYER;
	Hshader = shader;
	Hpos = Npos;
	HDirection = dir;
	HAngle = glm::atan(HDirection.z /HDirection.x);
	HModelMatrix = glm::rotate(HAngle,0.0f,1.0f,0.0f);
	HModelMatrix = glm::translate(Npos);
	Initialize();
	
	auto Boundingbox = CMD2Model::GetBoundingBox();
	Boundingbox.Translate(Hpos);
	
}


void Player::Render(glm::mat4 VP)
{
	Hshader->UseProgram();
	Hshader->BindModelMatrix(&HModelMatrix[0][0]);
	Hshader->BindVPMatrix(&VP[0][0]);
	CMD2Model::RenderModel(&HanimationState,Hshader);
}

void Player::Collided(ObjectType CollType)
{
	if (CollType == ObjectType::OBJECT){
		printf("Player collided with an Object \n");
	}
	else if (CollType == ObjectType::ENEMY)
	{
		printf("Player collided with an Enemy \n");
	}
	
}


void Player::updateanimation(float delta)
{
	CMD2Model::UpdateAnimation(&HanimationState, delta);
}


void Player::Initialize()
{
	CMD2Model::LoadModel("data/models/blade/Blade.md2");
	HanimationState = this->StartAnimation(animType_t::STAND);
	//calculate AABB
	CMD2Model::SetBoundingBox(CollidableModel::CalculateBoundingBox(CMD2Model::GetVertices()));
	Initial = glm::rotate(-90.0f, 1.0f, 0.0f, 0.0f) * glm::scale(0.01f, 0.01f, 0.01f);
	auto BondingBox = CMD2Model::GetBoundingBox();
	BondingBox.Scale(0.01f, 0.01f, 0.01f);
	BondingBox.Rotate(-90.0f, 1.0f, 0.0f, 0.0f);
	CMD2Model::SetBoundingBox(BondingBox);
}


void Player::Move(glm::vec3 Direction)
{
	float stepsize = 0.1f;
	auto OldDir = HDirection;
	HDirection = Direction;
	HAngle = atan2(HDirection.z , HDirection.x) * 180/3.14159265359;
	auto Newpos = Hpos;
	Newpos = Newpos + Direction*stepsize;
	Hpos = Newpos;
	UpdateModel();
	auto bound = CollidableModel::GetBoundingBox();
	bound.SetCenter(Hpos);
	//float rotatangel = glm::acos(glm::dot(OldDir, Direction));
	//bound.Rotate(rotatangel, 0.0f, 1.0f, 0.0f);
	CMD2Model::SetBoundingBox(bound);
}


void Player::UpdateModel()
{

	HModelMatrix = glm::translate(Hpos)*glm::rotate(HAngle,0.0f,1.0f,0.0f)*Initial;
}
Player::~Player()
{
}
