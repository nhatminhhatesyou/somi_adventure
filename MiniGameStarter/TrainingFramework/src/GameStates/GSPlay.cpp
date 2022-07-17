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



GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG.tga");

	// background
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
		//layer3
	texture = ResourceManagers::GetInstance()->GetTexture("Big Clouds.tga");
	m_background_3 = std::make_shared<Sprite2D>(model, shader, texture);
	m_background_3->Set2DPosition(3 * (float)Globals:: screenWidth / 2, (float)Globals::screenHeight / 2 + 15);
	m_background_3->SetSize(1080, 243);

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
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Idle1.tga");
	std::shared_ptr<SpriteAnimation> obj_idle1 = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 1, 0, 0.1f);
	
	obj_idle1->Set2DPosition(120, 120);
	obj_idle1->SetSize(150, 150);
	m_listAnimation.push_back(obj_idle1);
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
	switch (m_KeyPress)//Handle Key event
	{

	case 1: // move left
		for (auto it : m_listAnimation) {
			it->Set2DPosition(it->GetPosition().x - 100 * deltaTime, it->GetPosition().y);
		}
		break;
	case 2: // move down
		for (auto it : m_listAnimation) {
			it->Set2DPosition(it->GetPosition().x, it->GetPosition().y + 100 * deltaTime);
		}
		break;
	case 4: // move right
		for (auto it : m_listAnimation) {
			it->Set2DPosition(it->GetPosition().x + 100 * deltaTime, it->GetPosition().y);
		}
		break;
	case 8: // JUMP	
		for (auto it : m_listAnimation) {
			printf("forward ");
			it->Set2DPosition(it->GetPosition().x, it->GetPosition().y - 100 * deltaTime);
		}
	default:
		break;
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}

	m_background_2->Set2DPosition(m_background_2->GetPosition().x - 100 * deltaTime, m_background_2->GetPosition().y);
	if (m_background_2->GetPosition().x < -(float)Globals::screenWidth / 2)
		m_background_2->Set2DPosition(m_background_2->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_background_2->GetPosition().y);

	m_background_3->Set2DPosition(m_background_3->GetPosition().x - 100 * deltaTime, m_background_3->GetPosition().y);
	if (m_background_3->GetPosition().x < -(float)Globals::screenWidth / 2)
		m_background_3->Set2DPosition(m_background_3->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_background_3->GetPosition().y);

}

void GSPlay::Draw()
{
	m_background_1->Draw();
	m_background_2->Draw();
	m_background_3->Draw();
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
}