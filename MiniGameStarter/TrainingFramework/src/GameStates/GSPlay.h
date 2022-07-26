#pragma once
#include "GameStateBase.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;
class Obstacle;
class Player;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;
	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	int m_KeyPress;
	float Player_Pos_X, Player_Pos_Y;
	float Timer = 0;
	float speed = 200;
	int rd = rand() % (2 - 1 + 1) + 1;
	int cur_score = 0;
	std::string score;
	std::string hi_score ;

private:
	std::shared_ptr<Player>		m_player;
	std::shared_ptr<Sprite2D>	m_background_1, m_background_2, m_background_3, small_cloud_1, small_cloud_2, small_cloud_3;
	std::shared_ptr<Sprite2D>	m_ground1, m_ground2;
	std::shared_ptr<Obstacle>	spike_1, spike_2, spike_3, spike_4;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::vector<std::shared_ptr<Obstacle>>	m_listObstacles;
};

