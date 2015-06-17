#include "SkyBox.h"



#include <glm\gtx\transform.hpp>

SkyBox::SkyBox(void) {}
SkyBox::~SkyBox(void) {}

void SkyBox::Initialize()
{
	skyBoxModel = std::unique_ptr<Model>(new Model());

	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, -1.0f, -1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, -1.0f, 1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, 1.0f, -1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, -1.0f, 1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));

	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	skyBoxModel->VertexData.push_back(glm::vec3(1.0f, -1.0f, 1.0f));


	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.333f));
	skyBoxModel->UVData.push_back(glm::vec2(0.0f, 0.333f));
	skyBoxModel->UVData.push_back(glm::vec2(0.0f, 0.666f));

	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.333f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.666f));

	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.0f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.333f));
	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.333f));

	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.333f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.333f));

	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.333f));
	skyBoxModel->UVData.push_back(glm::vec2(0.0f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.666f));

	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.0f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.0f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.333f));

	skyBoxModel->UVData.push_back(glm::vec2(1.0f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(1.0f, 0.333f));
	skyBoxModel->UVData.push_back(glm::vec2(0.75f, 0.333f));

	skyBoxModel->UVData.push_back(glm::vec2(0.75f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.333f));
	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.666f));

	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.333f));
	skyBoxModel->UVData.push_back(glm::vec2(0.75f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(0.75f, 0.333f));

	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 1.0f));
	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.666f));

	skyBoxModel->UVData.push_back(glm::vec2(0.5f, 1.0f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(0.25f, 1.0f));
	
	skyBoxModel->UVData.push_back(glm::vec2(0.75f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(1.0f, 0.666f));
	skyBoxModel->UVData.push_back(glm::vec2(0.75f, 0.333f));
	

	skyBoxModel->NormalsData.push_back(LEFT_NORMAL);
	skyBoxModel->NormalsData.push_back(LEFT_NORMAL);
	skyBoxModel->NormalsData.push_back(LEFT_NORMAL);

	skyBoxModel->NormalsData.push_back(FRONT_NORMAL);
	skyBoxModel->NormalsData.push_back(FRONT_NORMAL);
	skyBoxModel->NormalsData.push_back(FRONT_NORMAL);

	skyBoxModel->NormalsData.push_back(BOTTOM_NORMAL);
	skyBoxModel->NormalsData.push_back(BOTTOM_NORMAL);
	skyBoxModel->NormalsData.push_back(BOTTOM_NORMAL);

	skyBoxModel->NormalsData.push_back(FRONT_NORMAL);
	skyBoxModel->NormalsData.push_back(FRONT_NORMAL);
	skyBoxModel->NormalsData.push_back(FRONT_NORMAL);

	skyBoxModel->NormalsData.push_back(LEFT_NORMAL);
	skyBoxModel->NormalsData.push_back(LEFT_NORMAL);
	skyBoxModel->NormalsData.push_back(LEFT_NORMAL);

	skyBoxModel->NormalsData.push_back(BOTTOM_NORMAL);
	skyBoxModel->NormalsData.push_back(BOTTOM_NORMAL);
	skyBoxModel->NormalsData.push_back(BOTTOM_NORMAL);

	skyBoxModel->NormalsData.push_back(BACK_NORMAL);
	skyBoxModel->NormalsData.push_back(BACK_NORMAL);
	skyBoxModel->NormalsData.push_back(BACK_NORMAL);

	skyBoxModel->NormalsData.push_back(RIGHT_NORMAL);
	skyBoxModel->NormalsData.push_back(RIGHT_NORMAL);
	skyBoxModel->NormalsData.push_back(RIGHT_NORMAL);

	skyBoxModel->NormalsData.push_back(RIGHT_NORMAL);
	skyBoxModel->NormalsData.push_back(RIGHT_NORMAL);
	skyBoxModel->NormalsData.push_back(RIGHT_NORMAL);

	skyBoxModel->NormalsData.push_back(TOP_NORMAL);
	skyBoxModel->NormalsData.push_back(TOP_NORMAL);
	skyBoxModel->NormalsData.push_back(TOP_NORMAL);

	skyBoxModel->NormalsData.push_back(TOP_NORMAL);
	skyBoxModel->NormalsData.push_back(TOP_NORMAL);
	skyBoxModel->NormalsData.push_back(TOP_NORMAL);

	skyBoxModel->NormalsData.push_back(BACK_NORMAL);
	skyBoxModel->NormalsData.push_back(BACK_NORMAL);
	skyBoxModel->NormalsData.push_back(BACK_NORMAL);

	skyBoxModel->Initialize();


	skyBoxTexture = std::unique_ptr<Texture>(new Texture("above_the_sea.png", 0));

	skyBoxModelMatrix = glm::translate(0.0f, 0.0f, 0.0f) * glm::scale(10.0f, 10.0f, 10.0f);;
}

void SkyBox::Draw(GLuint vertexPosition_modelspaceID, GLuint inputColorID, GLuint texCoordID, GLuint vertexNormal_modelspaceID ,ShaderProgram *shader,glm::mat4 VP)
{
	shader->BindRenderMode(1);
	shader->BindVPMatrix(&VP[0][0]);
	shader->BindModelMatrix(&skyBoxModelMatrix[0][0]);
	skyBoxTexture->Bind();
	skyBoxModel->Draw(vertexPosition_modelspaceID,  inputColorID, texCoordID, vertexNormal_modelspaceID);
	shader->BindRenderMode(0);
}