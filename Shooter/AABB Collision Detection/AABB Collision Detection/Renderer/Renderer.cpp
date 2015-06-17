#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include "OBJLoader/objloader.hpp"

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{

	GSkyBox = std::unique_ptr<SkyBox>(new SkyBox());
	myCamera = std::unique_ptr<EulerCamera>(new EulerCamera());
	Gun = std::unique_ptr<Model3D>(new Model3D());
	collisionManager = std::unique_ptr<CollisionManager>( new CollisionManager());
	//////////////////////////////////////////////////////////////////////////
	GSkyBox->Initialize();
	//drawing a square.
	floor = std::unique_ptr<Model>(new Model());
	floor->VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(0.0f,0.0f));
	floor->VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(10.0f,0.0f));
	floor->VertexData.push_back(glm::vec3( 1.0f,  1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(10.0f,10.0f));
	floor->VertexData.push_back(glm::vec3( -1.0f,  1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(0.0f,10.0f));

	cursor = std::unique_ptr<Model>(new Model());
	cursor->VertexData.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	cursor->ColorData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	cursor->VertexData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	cursor->ColorData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	cursor->VertexData.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	cursor->ColorData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	cursor->Initialize();

	
	//first triangle.
	floor->IndicesData.push_back(0);
	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(3);

	//second triangle.
	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(2);
	floor->IndicesData.push_back(3);
	glm::vec3 squareNormal = glm::vec3(0.0,0.0,1.0);
	floor->NormalsData.push_back(squareNormal);
	floor->NormalsData.push_back(squareNormal);
	floor->NormalsData.push_back(squareNormal);
	floor->NormalsData.push_back(squareNormal);
	floor->Initialize();


	floorTexture = std::unique_ptr<Texture>(new Texture("data/textures/Desert.jpg",0));

	Gun->LoadFromFile("data/models/Level_1/Working texture/Guns/SMG/sub_mach.3DS");
	Gun->Initialize();
	MGun = glm::translate(0.25f,-0.3f,0.2f) * glm::rotate(110.0f,0.0f,1.0f,0.0f) * glm::scale(0.009f, 0.009f, 0.009f);
	cursorM = glm::scale(0.002f, 0.002f, 0.002f);
	//////////////////////////////////////////////////////////////////////////	
	//						Leve1 Objects								    //
	//////////////////////////////////////////////////////////////////////////

	level1 = std::unique_ptr<LevelMap>(new LevelMap);
	level1->Initialize();

	//////////////////////////////////////////////////////////////////////////
	// Create and compile our GLSL program from the shaders
	animatedModelShader.LoadProgram();
	animatedModelShader.UseProgram();


	glm::vec3 plcenter = myCamera->GetPosition();
	AABoundingBox plbox(plcenter, glm::vec3(0.2f, 0.2f, 0.2f));
	myCamera->SetBoundingBox(plbox);

	collisionManager->AddCollidableModel((CollidableModel*)myCamera.get());

	for (int i = 0; i < 12; i++){
		collisionManager->AddCollidableModel((CollidableModel*)&level1->Objects[i]);
	}

	enemy.resize(5);

	enemy[0] = std::unique_ptr<Enemy>(new Enemy(&animatedModelShader,glm::vec3(5.0f,0.0f,0.0f)));
	enemy[0]->Initialize("data/models/samourai/Samourai.md2");
	collisionManager->AddCollidableModel((CollidableModel*)enemy[0].get());

	enemy[1] = std::unique_ptr<Enemy>(new Enemy(&animatedModelShader, glm::vec3(0.0f, 0.0f, -5.0f)));
	enemy[1]->Initialize("data/models/samourai/Samourai.md2");
	collisionManager->AddCollidableModel((CollidableModel*)enemy[1].get());

	staticModelShader.LoadProgram();
	staticModelShader.UseProgram();
	staticModelShaderAttr.vertexPosition_modelspaceID = glGetAttribLocation(staticModelShader.programID, "vertexPosition_modelspace");
	staticModelShaderAttr.inputColorID = glGetAttribLocation(staticModelShader.programID, "inputColor");
	staticModelShaderAttr.texCoordID = glGetAttribLocation(staticModelShader.programID, "texCoord");
	staticModelShaderAttr.vertexNormal_modelspaceID = glGetAttribLocation(staticModelShader.programID,"vertexNormal_modelspace");
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Projection matrix : 
	myCamera->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// View matrix : 
	myCamera->Reset(0, 0.2, 0.5,
		0, 0, 0,
		0, 1, 0);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Configure the light.
	//setup the light position.
	staticModelShader.UseProgram();
	LightPositionID = glGetUniformLocation(staticModelShader.programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(5.0,5.0,0.0);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(staticModelShader.programID,"ambientLight");
	ambientLight = glm::vec3(0.1,0.1,0.1);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	AmientlightColorID = glGetUniformLocation(staticModelShader.programID, "ambientcolor");
	glm::vec3 colors = glm::vec3(1.0f, 1.0f, 1.0f);
	glUniform3fv(AmientlightColorID, 1, &colors[0]);
	DiflightColorID = glGetUniformLocation(staticModelShader.programID, "difcolor");
	colors = glm::vec3(1.0f, 1.0f, 1.0f);
	glUniform3fv(DiflightColorID, 1, &colors[0]);
	SpeclightColorID = glGetUniformLocation(staticModelShader.programID, "speccolor");
	colors = glm::vec3(1.0f, 1.0f, 1.0f);
	glUniform3fv(SpeclightColorID, 1, &colors[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(staticModelShader.programID,"EyePosition_worldspace");
	//send the eye position to the shaders.
	glUniform3fv(EyePositionID,1, &myCamera->GetPosition()[0]);

	///////////////////////////////////////////////////
	//repeat the process for the animated models shader.
	animatedModelShader.UseProgram();
	LightPositionID = glGetUniformLocation(animatedModelShader.programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(1.0,0.25,0.0);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(animatedModelShader.programID,"ambientLight");
	ambientLight = glm::vec3(0.5,0.5,0.5);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	AmientlightColorID = glGetUniformLocation(animatedModelShader.programID, "ambientcolor");
	colors = glm::vec3(1.0f, 1.0f, 1.0f);
	glUniform3fv(AmientlightColorID, 1, &colors[0]);
	DiflightColorID = glGetUniformLocation(animatedModelShader.programID, "difcolor");
	colors = glm::vec3(1.0f, 1.0f, 1.0f);
	 glUniform3fv(DiflightColorID, 1, &colors[0]);
	 SpeclightColorID = glGetUniformLocation(animatedModelShader.programID, "speccolor");
	 colors = glm::vec3(1.0f, 1.0f, 1.0f);
	 glUniform3fv(SpeclightColorID, 1, &colors[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	//send the eye position to the shaders.
	glUniform3fv(EyePositionID, 1, &myCamera->GetPosition()[0]);
	//////////////////////////////////////////////////////////////////////////
	//Setting the initaial transformations
	floorM = glm::translate(0.0f, -0.2f, 0.0f)*glm::scale(10.0f, 3.0f, 10.0f)*glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	initVP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
}

void Renderer::Draw()
{		

		//Bind the VP matrix (Camera matrices) to the current shader.
		glm::mat4 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();

		
		staticModelShader.BindRenderMode(0);

		staticModelShader.UseProgram();
		staticModelShader.BindVPMatrix(&initVP[0][0]);
		Gun->Render(&staticModelShader, MGun);
		staticModelShader.BindModelMatrix(&cursorM[0][0]);
		cursor->Draw(staticModelShaderAttr.vertexPosition_modelspaceID, staticModelShaderAttr.inputColorID, staticModelShaderAttr.texCoordID, staticModelShaderAttr.vertexNormal_modelspaceID);

		staticModelShader.BindVPMatrix(&VP[0][0]);
		staticModelShader.BindModelMatrix(&floorM[0][0]);
		floorTexture->Bind();
		floor->Draw(staticModelShaderAttr.vertexPosition_modelspaceID,staticModelShaderAttr.inputColorID,staticModelShaderAttr.texCoordID,staticModelShaderAttr.vertexNormal_modelspaceID);

	

		GSkyBox->Draw(staticModelShaderAttr.vertexPosition_modelspaceID, staticModelShaderAttr.inputColorID, staticModelShaderAttr.texCoordID, staticModelShaderAttr.vertexNormal_modelspaceID, &staticModelShader, VP);

		level1->Draw(staticModelShader);
		enemy[0]->Render(VP);
		enemy[1]->Render(VP);
}

void Renderer::Cleanup()
{
}

void Renderer::Update(double deltaTime)
{
	auto tempBox = myCamera->GetBoundingBox();
	glm::vec3 plcenter = myCamera->GetPosition();
	AABoundingBox plbox(plcenter, glm::vec3(1.0f,1.0f,1.0f));
	myCamera->SetBoundingBox(plbox);
	
	//enemy->UpdateMove(deltaTime / 1000);
	enemy[0]->updateanimation(deltaTime / 1000);
	enemy[1]->updateanimation(deltaTime / 1000);

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->UpdatePos(deltaTime / 1000);
	}
	if (myCamera->jumping)
		myCamera->Jumping(deltaTime/1000);

	collisionManager->UpdateCollisions();
}

void Renderer::HandleKeyboardInput(int key)
{
	float step = 0.1f;

	//NOTE!!! 
	//this is the worst way possible for moving an object with the camera.
	// but it'll serve our purpose for now.
	bool first = true;
	switch (key)
	{
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		myCamera->Walk(step);
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		myCamera->Walk(-step);
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		myCamera->Strafe(step);
		break;

		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		myCamera->Strafe(-step);
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		myCamera->StartJumping();
		break;

	default:
		break;
	}

	//Set the transformed bounding box again.

	//continue the remaining movements.
	myCamera->UpdateViewMatrix();

	//update the eye position uniform.
	staticModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(staticModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID, 1, &myCamera->GetPosition()[0]);

	animatedModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID, 1, &myCamera->GetPosition()[0]);
}

void Renderer::HandleMouse(double deltaX, double deltaY)
{
	
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
	myCamera->UpdateViewMatrix();
}


void Renderer::HandleMouseButtons(int button)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT){
		
		Bullet *TempBullet = myCamera->Fire(myCamera->GetPosition(),-myCamera->GetLookDirection());
		bullets.push_back(TempBullet);
		collisionManager->AddCollidableModel((CollidableModel*)TempBullet);
		
	}
	

}
