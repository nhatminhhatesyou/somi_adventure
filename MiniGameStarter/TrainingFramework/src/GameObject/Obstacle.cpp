#include "Obstacle.h"

Obstacle::Obstacle(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-2, model, shader, texture)
{
}

Obstacle::~Obstacle()
{
}

bool Obstacle::CollisionCheck(GLfloat x, GLfloat y) {
	float PosX = this->GetPosition().x; //toa do x cua obstacle
	float PosY = this->GetPosition().y; //toa do y cua obstacle
	if (x >= (PosX - this->GetSize().x / 2 - 30) && x <= (PosX + this->GetSize().x / 2 + 30) && y >= (PosY - this->GetSize().y / 2 - 30) && y <= (PosY + this->GetSize().y / 2 + 30))
	{
		printf("VA CHAM!\n");
		return true;
	}
	return false;
}


bool Obstacle::OnGround(GLfloat y) {
	float PosY = this->GetPosition().y;
	if (y < (PosY + this->GetSize().y / 2 + 30)) return false;
	else return true;
}