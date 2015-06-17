 #include "EulerCamera.h"

EulerCamera::EulerCamera(void)
{

	CMD2Model::type = ObjectType::PLAYER;
	mAngleX = 0;
	mAngleY = 0;
	this->Reset(0, 1, 0,
		0, 0, -1,
		0, 1, 0);

	SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	old_time = 0;
	curr_time = 0;
	jumping = false;
}

EulerCamera::~EulerCamera(void)
{
}

glm::vec3 EulerCamera::GetLookDirection()
{
	return -mDirection;
}

glm::vec3 EulerCamera::GetPosition()
{
	return mPosition;
}

void EulerCamera::Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	glm::vec3 eyePt(eyeX, eyeY, eyeZ);
	glm::vec3 centerPt(centerX, centerY, centerZ);
	glm::vec3 upVec(upX, upY, upZ);
	Reset(eyePt, centerPt, upVec);
}

void EulerCamera::Reset(const glm::vec3 &eye, const glm::vec3 &center, glm::vec3 &up)
{
	mPosition = eye;

	//still needs normalization
	mDirection = center - mPosition;
	//i = j x k
	mRight = glm::cross(mDirection, up);
	//j = k x i
	mUp = up;
	//normalize all
	mUp = glm::normalize(mUp);
	mRight = glm::normalize(mRight);
	mDirection = glm::normalize(mDirection);

	mViewMatrix = glm::lookAt(mPosition, center, mUp);
	//UpdateViewMatrix();
}

glm::mat4 EulerCamera::GetViewMatrix()
{
	return mViewMatrix;
}

void EulerCamera::UpdateViewMatrix()
{
	const float PI = 3.14f;
	mDirection = glm::vec3(
		-cos(mAngleY)*sin(mAngleX),
		sin(mAngleY),
		-cos(mAngleY)*cos(mAngleX));


	mDirection = glm::normalize(mDirection);


	mRight = glm::cross(mDirection, glm::vec3(0, 1, 0));

	mUp = glm::cross(mRight, mDirection);

	glm::vec3 center = mPosition + mDirection;
	mViewMatrix = glm::lookAt(mPosition, center, mUp);

	//glm::mat4 view = glm::mat4(	mRight.x,		mRight.y,		mRight.z,		-glm::dot(mPosition,mRight),
	//	mUp.x,			mUp.y,			mUp.z,			-glm::dot(mPosition,mUp),
	//	mDirection.x,	mDirection.y,	mDirection.z,	-glm::dot(mPosition,mDirection),
	//	0,				0,				0,				1);
	//mViewMatrix = glm::transpose(view);
}

glm::mat4 EulerCamera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}

void EulerCamera::SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	mProjectionMatrix = glm::perspective(FOV, aspectRatio, near, far);
}

void EulerCamera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR *mRight;
	mPosition += stepU * mUp;
	//next transition needs to be tested!!.
	mPosition += stepD * mDirection;
}

void EulerCamera::Yaw(float angleDegrees)
{
	mAngleX += angleDegrees;
}

void EulerCamera::Pitch(float angleDegrees)
{
	double PI = 3.14;
	if (mAngleY + angleDegrees < PI / 2.0 && mAngleY + angleDegrees > -PI / 2.0)
		mAngleY += angleDegrees;
}

void EulerCamera::Roll(float angleDegrees)
{
	//no ROLL!!!
}

void EulerCamera::Walk(float dist)
{
	if (dist > 0)
		LastMove = Moves::Forward;
	else if (dist < 0)
		LastMove = Moves::Backward;
	mPosition[0] += dist * mDirection[0];
	mPosition[2] += dist * mDirection[2];
}

void EulerCamera::Strafe(float dist)
{
	if (dist > 0)
		LastMove = Moves::Right;
	else if (dist < 0)
		LastMove = Moves::Left;

	mPosition += dist *mRight;
}

void EulerCamera::Fly(float dist)
{
	//no FLY
	mPosition += dist * mUp;
}


void EulerCamera::Collided(ObjectType colltype)
{

	if (colltype == ObjectType::ENEMY)
	{
		printf("Enemy collision");
	}
	else if (colltype == ObjectType::OBJECT)
	{
		printf("Object \n");
		if (LastMove==Moves::Forward)
			Walk(-0.1f);
		else if (LastMove == Moves::Backward)
			Walk(0.1f);
		else if (LastMove == Moves::Left)
			Strafe(0.1f);
		else if (LastMove == Moves::Right)
			Strafe(-0.1f);
	}

}

Bullet* EulerCamera::Fire(glm::vec3 pos,glm::vec3 dir)
{
	Bullet *myBullet = new Bullet(pos, dir);
	return myBullet;
}


void EulerCamera::Jumping(double fTimePassed)
{
	curr_time += fTimePassed;
	if (jump_count == 12)
		phase = false;

	if (curr_time - old_time > (0.005f))
	{
		if (phase == true)
		{
			Fly(0.02);
			jump_count++;
		}
		else
		{
			Fly(-0.03);
			jump_count--;
			if (jump_count == 4) jumping = false;
		}
		old_time = curr_time;
	}

	UpdateViewMatrix();
}

void EulerCamera::StartJumping()
{
	if (jumping == false)
	{
		curr_time = 0;
		old_time = 0;
		jumping = true;
		phase = true;
		jump_count = 0;
	}
}




