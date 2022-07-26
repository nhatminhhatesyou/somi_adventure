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
		//background	
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
		//Small clouds 1
		texture = ResourceManagers::GetInstance()->GetTexture("Small Cloud 1.tga");
		small_cloud_1 = std::make_shared<Sprite2D>(model, shader, texture);
		small_cloud_1->Set2DPosition((float)Globals::screenWidth / 2 -300, 200);
		small_cloud_1->SetSize(148, 48);
		//Small clouds 2
		texture = ResourceManagers::GetInstance()->GetTexture("Small Cloud 2.tga");
		small_cloud_2 = std::make_shared<Sprite2D>(model, shader, texture);
		small_cloud_2->Set2DPosition((float)Globals::screenWidth / 2 - 660 , 100);
		small_cloud_2->SetSize(266, 70);
		//Small clouds 3
		texture = ResourceManagers::GetInstance()->GetTexture("Small Cloud 2.tga");
		small_cloud_3 = std::make_shared<Sprite2D>(model, shader, texture);
		small_cloud_3->Set2DPosition((float)Globals::screenWidth / 2, 250);
		small_cloud_3->SetSize(280, 78);

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
		texture = ResourceManagers::GetInstance()->GetTexture("CATUS.tga");
		spike_1 = std::make_shared<Obstacle>(model, shader, texture);
		spike_1->Set2DPosition((float)Globals::screenWidth + 31, 550);
		spike_1->SetSize(61, 100);
		m_listObstacles.push_back(spike_1);
		//Spike 2
		texture = ResourceManagers::GetInstance()->GetTexture("CATUS.tga");
		spike_2 = std::make_shared<Obstacle>(model, shader, texture);
		spike_2->Set2DPosition((float)Globals::screenWidth +41, 550);
		spike_2->SetSize(61, 100);
		m_listObstacles.push_back(spike_2);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
			GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//button play again
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	m_playButton = std::make_shared<GameButton>(model, shader, texture);	
	m_playButton->SetSize(200, 200);
	m_playButton->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});	
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

	m_playButton->HandleTouchEvents(x, y, bIsPressed);
		
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{

	if (!GameOver){
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
	
	
		//Score
		cur_score += 1;
		auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Minecraft.ttf");
		m_score = std::make_shared<Text>(shader, font, "SCORE: " + std::to_string(cur_score), TextColor::WHITE, 1.0);
		m_score->Set2DPosition(Vector2(5, 50));
		m_hiScore = std::make_shared<Text>(shader, font, "HIGH SCORE: " + std::to_string(Globals::hi_score), TextColor::WHITE, 1.0);
		m_hiScore->Set2DPosition(Vector2(5, 25));
		//play Again text
		m_playAgain = std::make_shared<Text>(shader, font, "PLAY AGAIN", TextColor::BLACK, 1.0);
		m_playAgain->Set2DPosition(Globals::screenWidth / 2 - 70, Globals::screenHeight / 2 - 120);
		
		

		//Moving Clouds
		m_background_2->Set2DPosition(m_background_2->GetPosition().x - 200 * deltaTime, m_background_2->GetPosition().y);
		if (m_background_2->GetPosition().x < -(float)Globals::screenWidth / 2)
			m_background_2->Set2DPosition(m_background_2->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_background_2->GetPosition().y);

		m_background_3->Set2DPosition(m_background_3->GetPosition().x - 200 * deltaTime, m_background_3->GetPosition().y);
		if (m_background_3->GetPosition().x < -(float)Globals::screenWidth / 2)
			m_background_3->Set2DPosition(m_background_3->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_background_3->GetPosition().y);

		small_cloud_1->Set2DPosition(small_cloud_1->GetPosition().x - 100 * deltaTime, small_cloud_1->GetPosition().y);
		if (small_cloud_1->GetPosition().x < -small_cloud_1->GetSize().x / 2)
			small_cloud_1->Set2DPosition((float)Globals::screenWidth + small_cloud_1->GetSize().x / 2, small_cloud_1->GetPosition().y);

		small_cloud_2->Set2DPosition(small_cloud_2->GetPosition().x - 150 * deltaTime, small_cloud_2->GetPosition().y);
		if (small_cloud_2->GetPosition().x < -small_cloud_2->GetSize().x / 2)
			small_cloud_2->Set2DPosition((float)Globals::screenWidth + small_cloud_2->GetSize().x / 2, small_cloud_2->GetPosition().y);

		small_cloud_3->Set2DPosition(small_cloud_3->GetPosition().x - 175 * deltaTime, small_cloud_3->GetPosition().y);
		if (small_cloud_3->GetPosition().x < -small_cloud_3->GetSize().x / 2)
			small_cloud_3->Set2DPosition((float)Globals::screenWidth + small_cloud_3->GetSize().x / 2, small_cloud_3->GetPosition().y);

		//Moving ground
		m_ground1->Set2DPosition(m_ground1->GetPosition().x - speed * deltaTime, m_ground1->GetPosition().y);
		if (m_ground1->GetPosition().x < -(float)Globals::screenWidth / 2)
			m_ground1->Set2DPosition(m_ground1->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_ground1->GetPosition().y);

		m_ground2->Set2DPosition(m_ground2->GetPosition().x - speed * deltaTime, m_ground2->GetPosition().y);
		if (m_ground2->GetPosition().x < -(float)Globals::screenWidth / 2)
			m_ground2->Set2DPosition(m_ground2->GetPosition().x + 4 * (float)Globals::screenWidth / 2, m_ground2->GetPosition().y);

		//Moving Spike

		Timer += deltaTime;

		for (int i = 0; i < m_listObstacles.size(); i++) {
			if (m_listObstacles[i]->GetPosition().x + 24 < 0)
			{
				m_listObstacles[i]->ResetPos();		//If current obstacle is out of the screen, reset it's position
			}

		}
		m_listObstacles[0]->Spawn(deltaTime, speed);
		if (Timer > rd)
		{
			m_listObstacles[1]->Spawn(deltaTime, speed);
			rd = rand() % (2 - 1 + 1) + 1;
		}
		speed += 8 * deltaTime;

		for (int i = 0; i < m_listObstacles.size(); i++) {
			if (m_listObstacles[i]->CollisionCheck(Player_Pos_X, Player_Pos_Y))
			{
				if (Globals::hi_score < cur_score)
					Globals::hi_score = cur_score;
				m_playButton->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);

				GameOver = true;
				printf("VA CHAM! ");
			}
		}

		//GRAVITY
		if (m_player->velocity < 600)
			m_player->velocity += 1500 * deltaTime;


		if (!m_player->OnGround())
		{
			Player_Pos_Y += m_player->velocity * deltaTime;
			m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
		}
		else if (Player_Pos_Y > 568)
		{
			Player_Pos_Y = 568;
			m_player->Set2DPosition(Player_Pos_X, Player_Pos_Y);
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
		m_playButton->Update(deltaTime);
		m_player->Update(deltaTime);

	}
}

void GSPlay::Draw()
{	
	m_background_1->Draw();
	m_background_2->Draw();
	m_background_3->Draw();
	small_cloud_1->Draw();
	small_cloud_2->Draw();
	small_cloud_3->Draw();
	m_hiScore->Draw();
	m_ground1->Draw();
	m_ground2->Draw();
	m_score->Draw();
	m_player->Draw();
	if (GameOver)
	{
		m_playAgain->Draw();
		m_playButton->Draw();

	}

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