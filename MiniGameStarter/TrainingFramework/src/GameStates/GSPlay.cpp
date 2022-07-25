#include "GSPlay.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"
#include "Obstacle.h"
#include "Player.h"


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{	
	
	// background
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG.tga");	
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		//layer1	
		m_background_1 = std::make_shared<Sprite2D>(model, shader, texture);
		m_background_1->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
		m_background_1->SetSize(Globals::screenWidth, Globals::screenHeight);
		//Big clouds
		texture = ResourceManagers::GetInstance()->GetTexture("Big Clouds.tga");
		m_background_2 = std::make_shared<Sprite2D>(model, shader, texture);
		m_background_2->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2 + 15);
		m_background_2->SetSize(1080, 243);
		//Big clouds
		texture = ResourceManagers::GetInstance()->GetTexture("Big Clouds.tga");
		m_background_3 = std::make_shared<Sprite2D>(model, shader, texture);
		m_background_3->Set2DPosition(3 * (float)Globals:: screenWidth / 2, (float)Globals::screenHeight / 2 + 15);
		m_background_3->SetSize(1080, 243);
		// ground1
		texture = ResourceManagers::GetInstance()->GetTexture("Ground.tga");
		m_ground1 = std::make_shared<Obstacle>(model, shader, texture);
		m_ground1->Set2DPosition((float)Globals::screenWidth / 2, 660);
		m_ground1->SetSize(1080, 120);	
		// ground2
		texture = ResourceManagers::GetInstance()->GetTexture("Ground.tga");
		m_ground2 = std::make_shared<Obstacle>(model, shader, texture);
		m_ground2->Set2DPosition(3 * (float)Globals::screenWidth / 2, 660);
		m_ground2->SetSize(1080, 120);
	


	// Init Obstacle 
		//Spike 1
		texture = ResourceManagers::GetInstance()->GetTexture("Spike.tga");
		spike_1 = std::make_shared<Obstacle>(model, shader, texture);
		spike_1->Set2DPosition((float)Globals::screenWidth + 24, 560);
		spike_1->SetSize(47, 80);
		m_listObstacles.push_back(spike_1);
		//Spike 2
		texture = ResourceManagers::GetInstance()->GetTexture("Spike.tga");
		spike_2 = std::make_shared<Obstacle>(model, shader, texture);
		spike_2->Set2DPosition((float)Globals::screenWidth +24, 560);
		spike_2->SetSize(47, 80);
		m_listObstacles.push_back(spike_2);
		//Spike 3
		texture = ResourceManagers::GetInstance()->GetTexture("Spike.tga");
		spike_3 = std::make_shared<Obstacle>(model, shader, texture);
		spike_3->Set2DPosition((float)Globals::screenWidth +24, 560);
		spike_3->SetSize(47, 80);
		m_listObstacles.push_back(spike_3);
		//Spike 4
		texture = ResourceManagers::GetInstance()->GetTexture("Spike.tga");
		spike_4 = std::make_shared<Obstacle>(model, shader, texture);
		spike_4->Set2DPosition((float)Globals::screenWidth +24, 560);
		spike_4->SetSize(47, 80);
		m_listObstacles.push_back(spike_4);


	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
			GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "hihi", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));


	//Player
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Run.tga");
	m_player = std::make_shared<Player>(model, shader, texture, 8, 1, 0, 0.1f);
	Player_Pos_X = 120;
	Player_Pos_Y = 568;
	m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
	m_player->SetSize(128, 128);

	//
	m_KeyPress = 0;
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()

{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}


void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress |= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress |= 1<<1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress |= 1<<2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress |= 1<<3;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{

		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	bool Col;
	float Timer = 0;
	switch (m_KeyPress)//Handle Key event
	{
	case 1: // move left
		
			Player_Pos_X -= 300 * deltaTime;
			m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
		
		break;
	case 4: // move right
				
			Player_Pos_X += 300 * deltaTime;
			m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
		
		break;
	case 8: // JUMP	
		if (!m_player->OnGround())
			break;
		m_player->velocity *= -1;
		Player_Pos_Y += m_player->velocity * deltaTime;
		m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);		
	break;	
	case 9: // jump left
		if (!m_player->OnGround())
		{
			Player_Pos_X -= 300 * deltaTime;
			m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
		}
		else
		{
			m_player->velocity *= -1;
			Player_Pos_Y += m_player->velocity * deltaTime;
			m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
		}
		break;
	case 12: // jump right	
		if (!m_player->OnGround())
		{
			Player_Pos_X += 300 * deltaTime;
			m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
		}
		else {
			m_player->velocity *= -1;
			Player_Pos_Y += m_player->velocity * deltaTime;
			m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
		}
		break;

	}
	//
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
	m_player->Update(deltaTime);


	//Moving Clouds
		m_background_2->Set2DPosition(m_background_2->GetPosition().x - 100 * deltaTime, m_background_2->GetPosition().y);
		if (m_background_2->GetPosition().x < -(float)Globals::screenWidth / 2)
			m_background_2->Set2DPosition(m_background_2->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_background_2->GetPosition().y);

		m_background_3->Set2DPosition(m_background_3->GetPosition().x - 100 * deltaTime, m_background_3->GetPosition().y);
		if (m_background_3->GetPosition().x < -(float)Globals::screenWidth / 2)
			m_background_3->Set2DPosition(m_background_3->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_background_3->GetPosition().y);

	//Moving ground
		m_ground1->Set2DPosition(m_ground1->GetPosition().x - speed * deltaTime, m_ground1->GetPosition().y);
		if (m_ground1->GetPosition().x < -(float)Globals::screenWidth / 2)
			m_ground1->Set2DPosition(m_ground1->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_ground1->GetPosition().y);

		m_ground2->Set2DPosition(m_ground2->GetPosition().x - speed * deltaTime, m_ground2->GetPosition().y);
		if (m_ground2->GetPosition().x < -(float)Globals::screenWidth / 2)
			m_ground2->Set2DPosition(m_ground2->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_ground2->GetPosition().y);

	//Moving Spike
		int rd = rand() % (4 - 2 + 1) + 2;
		Timer += deltaTime;
		if (Timer > rd)
		{
			for (int i = 0; i < m_listObstacles.size(); i++) {
				if (m_listObstacles[i]->GetPosition().x == (float)Globals::screenWidth + 24) {
					m_listObstacles[i]->Set2DPosition(m_listObstacles[i]->GetPosition().x - speed * deltaTime, m_listObstacles[i]->GetPosition().y);
				}
				if (m_listObstacles[i]->GetPosition().x + 24 < 0) {
					m_listObstacles[i]->Set2DPosition((float)Globals::screenWidth + 24, m_listObstacles[i]->GetPosition().y);
				}				
			}
			Timer = 0;
		}


	//GRAVITY
		if (m_player->velocity < 350)
			m_player->velocity += 600 * deltaTime;
		if (!m_player->OnGround())
		{
			if (Player_Pos_Y + m_player->velocity * deltaTime > 568)
				Player_Pos_Y = 568;
			else
				Player_Pos_Y += m_player->velocity * deltaTime;

			m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
		}
		
}

void GSPlay::Draw()
{
	m_background_1->Draw();
	m_background_2->Draw();
	m_background_3->Draw();
	m_ground1->Draw();
	m_ground2->Draw();
	m_score->Draw();
	m_player->Draw();
	

	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}

	for (int i = 0; i < m_listObstacles.size(); i++) {
		m_listObstacles[i]->Draw();
	}

}