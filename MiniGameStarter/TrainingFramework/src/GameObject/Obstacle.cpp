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
	if (x >= (PosX - this->GetSize().x / 2 - 20) && x <= (PosX + this->GetSize().x / 2 + 20) && y >= (PosY - this->GetSize().y / 2 - 20) && y <= (PosY + this->GetSize().y / 2 + 20))
	{
		return true;
	}
	return false;
}


bool Obstacle::OnGround(GLfloat y) {
	float PosY = this->GetPosition().y;
	if (y < (PosY + this->GetSize().y / 2 + 30)) return false;
	else return true;
}

void Obstacle::ResetPos() {
		this->Set2DPosition(1080 + 31, 550);	
}

void Obstacle::Spawn(GLfloat deltaTime, float speed) {	
		this->Set2DPosition(this->GetPosition().x - speed * deltaTime, this->GetPosition().y); //Make Obstacle moves to the left	
}