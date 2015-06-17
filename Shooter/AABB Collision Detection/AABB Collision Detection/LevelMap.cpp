#include "LevelMap.h"


LevelMap::LevelMap()
{
}


void LevelMap::Initialize()
{
	Objects.resize(20);
	ObjectsM.resize(21);

	//Objects Loading
	Objects[0].LoadFromFile("data/models/Level_1/Working texture/Mountain2/MountnN14_3ds.3ds");
	Objects[1].LoadFromFile("data/models/Level_1/Working texture/Stable/Stable.3ds");
	Objects[2].LoadFromFile("data/models/Level_1/Working texture/House3/polHouse1.3ds");
	Objects[3].LoadFromFile("data/models/Level_1/Working texture/House8/3ds file.3ds");
	Objects[4].LoadFromFile("data/models/Level_1/Working texture/House4/fachwerk40T.3ds");
	Objects[5].LoadFromFile("data/models/Level_1/Working texture/Jeep/Jeep.3ds");
	Objects[6].LoadFromFile("data/models/Level_1/Working texture/Tent/Tent yurt N231013.3ds");
	Objects[7].LoadFromFile("data/models/Level_1/Working texture/Wagen/wagen1_Lp_End.3ds");
	Objects[8].LoadFromFile("data/models/Level_1/Working texture/Tree4/dead_trees.3ds");

	for (int i = 0; i < 9; i++){
		Objects[i].Initialize();
	}

	//setting bounding Boxes
	for (int i = 1; i < 9; i++)
	{
		Objects[i].SetBoundingBox(CollidableModel::CalculateBoundingBox(Objects[i].GetVertices()));
	}

	ObjectsM[0] = glm::mat4(1);
	ObjectsM[1] = glm::translate(5.5f, -0.2f, -4.3f) *glm::rotate(270.0f, 0.0f, 1.0f, 0.0f) *glm::scale(0.003f, 0.003f, 0.003f);
	auto tempBox = Objects[1].GetBoundingBox();
	tempBox.Scale(0.003f, 0.003f, 0.003f);
	tempBox.Rotate(270.0f, 0.0f, 1.0f, 0.0f);
	tempBox.Translate(5.5f, -0.2f, -4.3f);
	Objects[1].SetBoundingBox(tempBox);

	ObjectsM[2] = glm::translate(5.5f, -0.2f, 0.0f) *glm::rotate(270.0f, 0.0f, 1.0f, 0.0f) *glm::scale(0.03f, 0.03f, 0.03f);
	tempBox = Objects[2].GetBoundingBox();
	tempBox.Scale(0.03f, 0.03f, 0.03f);
	tempBox.Rotate(270.0f, 0.0f, 1.0f, 0.0f);
	tempBox.Translate(5.5f, -0.2f, 0.0f);
	Objects[2].SetBoundingBox(tempBox);

	ObjectsM[3] = glm::translate(-2.9f, -0.2f, -3.4f) *glm::rotate(90.0f, 0.0f, 1.0f, 0.0f) *glm::scale(0.06f, 0.06f, 0.06f);
	tempBox = Objects[3].GetBoundingBox();
	tempBox.Scale(0.06f, 0.06f, 0.06f);
	tempBox.Rotate(90.0f, 0.0f, 1.0f, 0.0f);
	tempBox.Translate(-2.9f, -0.2f, -3.4f);
	Objects[3].SetBoundingBox(tempBox);

	ObjectsM[4] = glm::translate(1.7f, -0.2f, 5.0f) *glm::rotate(270.0f, 0.0f, 1.0f, 0.0f) *glm::scale(0.18f, 0.18f, 0.18f);
	tempBox = Objects[4].GetBoundingBox();
	tempBox.Scale(0.18f, 0.18f, 0.18f);
	tempBox.Rotate(270.0f, 0.0f, 1.0f, 0.0f);
	tempBox.Translate(1.7f, -0.2f, 5.0f);
	Objects[4].SetBoundingBox(tempBox);

	ObjectsM[5] = glm::translate(5.5f, -0.2f, 5.0f) *glm::rotate(180.0f, 0.0f, 1.0f, 0.0f) *glm::scale(0.004f, 0.004f, 0.004f);
	tempBox = Objects[5].GetBoundingBox();
	tempBox.Scale(0.004f, 0.004f, 0.004f);
	tempBox.Rotate(180.0f, 0.0f, 1.0f, 0.0f);
	tempBox.Translate(5.5f, -0.2f, 5.0f);
	Objects[5].SetBoundingBox(tempBox);

	ObjectsM[6] = glm::translate(-5.5f, -0.2f, 1.4f) *glm::scale(0.001f, 0.001f, 0.001f);
	tempBox = Objects[6].GetBoundingBox();
	tempBox.Scale(0.001f, 0.001f, 0.001f);
	tempBox.Translate(-5.5f, -0.2f, 1.4f);
	Objects[6].SetBoundingBox(tempBox);

	ObjectsM[7] = glm::translate(-4.7f, -0.2f, 3.4f) *glm::rotate(270.0f, 0.0f, 1.0f, 0.0f) *glm::scale(0.002f, 0.002f, 0.002f);
	tempBox = Objects[7].GetBoundingBox();
	tempBox.Scale(0.002f, 0.002f, 0.002f);
	tempBox.Rotate(270.0f, 0.0f, 1.0f, 0.0f);
	tempBox.Translate(-4.7f, -0.2f, 3.4f);
	Objects[7].SetBoundingBox(tempBox);

	ObjectsM[8] = glm::translate(-2.4f, -0.2f, 7.0f) * glm::scale(0.06f, 0.06f, 0.06f);
	tempBox = Objects[8].GetBoundingBox();
	tempBox.Scale(0.06f, 0.06f, 0.06f);
	tempBox.Translate(-2.4f, -0.2f, 7.0f);
	Objects[8].SetBoundingBox(tempBox);

	//right
	ObjectsM[9] = glm::translate(12.0f, -0.4f, 0.0f) * glm::scale(0.002f, 0.002f, 0.002f);
	AABoundingBox box(glm::vec3(8.0f, -0.2f, 0.0f), glm::vec3(1.0f, 10.0f, 30.0f));
	Objects[0].SetBoundingBox(box);
	ObjectsM[10] = glm::translate(12.0f, -0.4f, 8.0f) * glm::scale(0.002f, 0.002f, 0.002f);
	ObjectsM[11] = glm::translate(12.0f, -0.4f, -8.0f) * glm::scale(0.002f, 0.002f, 0.002f);
	
	//Left 
	ObjectsM[12] = glm::translate(-12.0f, -0.4f, 0.0f) * glm::scale(0.002f, 0.002f, 0.002f);
	AABoundingBox box1(glm::vec3(-8.0f, -0.2f, 0.0f), glm::vec3(1.0f, 10.0f, 30.0f));
	Objects[9].SetBoundingBox(box1);
	ObjectsM[13] = glm::translate(-12.0f, -0.4f, 8.0f) * glm::scale(0.002f, 0.002f, 0.002f);
	ObjectsM[14] = glm::translate(-12.0f, -0.4f, -8.0f) * glm::scale(0.002f, 0.002f, 0.002f);
	
	//Front
	ObjectsM[15] = glm::translate(0.0f, -0.4f, -11.0f) * glm::scale(0.002f, 0.002f, 0.002f);
	AABoundingBox box2(glm::vec3(0.0f, -0.2f, -7.0f), glm::vec3(30.0f, 10.0f, 1.0f));
	Objects[10].SetBoundingBox(box2);
	ObjectsM[16] = glm::translate(7.0f, -0.4f, -11.0f) * glm::scale(0.002f, 0.002f, 0.002f);
	ObjectsM[17] = glm::translate(-7.0f, -0.4f, -11.0f) * glm::scale(0.002f, 0.002f, 0.002f);
	
	////BackMountains
	ObjectsM[18] = glm::translate(0.0f, -0.4f, 11.0f) *glm::rotate(270.0f, 0.0f, 1.0f, 0.0f)* glm::scale(0.002f, 0.002f, 0.002f);
	AABoundingBox box3(glm::vec3(0.0f, -0.2f, 7.0f), glm::vec3(30.0f, 10.0f, 1.0f));
	Objects[11].SetBoundingBox(box3);
	ObjectsM[19] = glm::translate(7.0f, -0.4f, 11.0f) *glm::rotate(270.0f, 0.0f, 1.0f, 0.0f)* glm::scale(0.002f, 0.002f, 0.002f);
	ObjectsM[20] = glm::translate(-7.0f, -0.4f, 11.0f) *glm::rotate(270.0f, 0.0f, 1.0f, 0.0f)* glm::scale(0.002f, 0.002f, 0.002f);
	

}


void LevelMap::Draw(ShaderProgram shader)
{

	for (int i = 9; i < 21; i++)
		Objects[0].Render(&shader, ObjectsM[i]);

	for (int i = 1; i <9; i++){
		Objects[i].Render(&shader, ObjectsM[i]);
	}
}
LevelMap::~LevelMap()
{
}