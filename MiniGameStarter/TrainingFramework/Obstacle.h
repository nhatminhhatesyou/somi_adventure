#pragma once
#include "Sprite2D.h"

class Obstacle : public Sprite2D
{
public:
	Obstacle() : Sprite2D() {};
	Obstacle(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~Obstacle();
	bool	CollisionCheck(std::shared_ptr<Sprite2D> obs);
	
};