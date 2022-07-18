#include "Obstacle.h"

Obstacle::Obstacle(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-1, model, shader, texture)
{
}

Obstacle::~Obstacle()
{
}

bool	Obstacle::CollisionCheck(std::shared_ptr<Sprite2D> obs)
{
	float obs_PosX = obs->GetPosition().x;
	float obs_PosY = obs->GetPosition().y;
	if (this->GetPosition().x >= obs->GetPosition().x - obs_PosX / 2 && this->GetPosition().x <= obs->GetPosition().x + obs_PosX / 2)
		return true;
	if (this->GetPosition().y >= obs->GetPosition().y - obs_PosY / 2 && this->GetPosition().y <= obs->GetPosition().y + obs_PosY / 2)
		return true;
	return false;
};