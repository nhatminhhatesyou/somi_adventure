#pragma once 
#include "Sprite2D.h"
#include <functional>

class Obstacle : public Sprite2D
{
public:
	Obstacle() : Sprite2D() {}
	Obstacle(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~Obstacle();
	bool CollisionCheck(GLfloat x, GLfloat y);
	bool OnGround(GLfloat y);
	void ResetPos();
	void Spawn(GLfloat deltaTime, float speed);
};
