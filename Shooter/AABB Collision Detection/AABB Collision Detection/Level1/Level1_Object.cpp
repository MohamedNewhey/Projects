#include "Level1_Object.h"


Level1_Object::Level1_Object()
{
	
}


void Level1_Object::Initialize()
{
	Objects.resize(20);
	ObjectsM.resize(20);
	Objects[0].LoadFromFile("data/models/Jeep/jeep1.3ds");
	Objects[1].LoadFromFile("data/models/Level_1/Objects/Palm2/Mexican Palm Tree3.3ds");
	Objects[2].LoadFromFile("data/models/Level_1/Objects/Tree3/Coconut Tree.3ds");
	Objects[3].LoadFromFile("data/models/Level_1/Objects/Gun/Gun3.3DS");
	Objects[4].LoadFromFile("data/models/Level_1/Objects/House6/house.3ds");
	Objects[5].LoadFromFile("data/models/Level_1/Objects/House3/polHouse1.3ds");
	Objects[6].LoadFromFile("data/models/Level_1/Objects/Stable/Stable.3DS");
	Objects[7].LoadFromFile("data/models/Level_1/Objects/Wagen/wagen1_Lp_End.3ds");
	Objects[8].LoadFromFile("data/models/Level_1/Objects/Jeep/Jeep.3ds");
	Objects[9].LoadFromFile("data/models/Level_1/Objects/Cactus/cactus.3ds");
	Objects[10].LoadFromFile("data/models/Level_1/Objects/House5/m12.3ds");

	for (int i = 0; i < 11; i++){
		Objects[i].Initialize();
	}


	ObjectsM[0] = glm::translate(0.0f, -0.2f, 0.0f) *glm::scale(0.1f, 0.1f, 0.1f);
	ObjectsM[1] = glm::translate(5.0f, -0.2f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f);
	ObjectsM[2] = glm::translate(-5.0f, -0.2f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f);
	ObjectsM[3] = glm::translate(0.0f, -0.2f, 0.0f);
	ObjectsM[4] = glm::translate(-3.0f, -0.2f, 0.0f)*glm::rotate(90.0f, 1.0f, 0.0f, 0.0f)* glm::scale(0.1f, 0.1f, 0.1f);
	ObjectsM[5] = glm::translate(-6.0f, -0.2f, 0.0f)*  glm::scale(0.01f, 0.01f, 0.01f);
	ObjectsM[6] = glm::translate(-5.0f, -0.2f, -6.0f) * glm::scale(0.01f, 0.01f, 0.01f);
	ObjectsM[7] = glm::translate(5.0f, -0.2f, -6.0f) * glm::scale(0.01f, 0.01f, 0.01f);
	ObjectsM[8] = glm::translate(6.0f, -0.2f, -6.0f) * glm::scale(0.01f, 0.01f, 0.01f);
	ObjectsM[9] = glm::translate(7.0f, -0.2f, -6.0f) * glm::scale(0.01f, 0.01f, 0.01f);
	ObjectsM[10] = glm::translate(8.0f, -0.2f, 6.0f) * glm::scale(0.01f, 0.01f, 0.01f);

}

void Level1_Object::Draw(ShaderProgram shader)
{

	for (int i = 0; i < 11; i++){
		Objects[i].Render(&shader, ObjectsM[i]);
	}
}

Level1_Object::~Level1_Object()
{
}
