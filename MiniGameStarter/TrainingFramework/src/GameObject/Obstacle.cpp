#include "Obstacle.h"

Obstacle::Obstacle(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-2, model, shader, texture)
{
}

Obstacle::~Obstacle()
{
}




