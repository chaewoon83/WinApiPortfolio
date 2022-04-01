#include "PlayerLink.h"
#include <windows.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineLevel.h>
#include "Boomerang.h"

//��ũ�� ũ�� == 64x96

PlayerLink::PlayerLink() 
	:Speed_(250.0f)
{
}

PlayerLink::~PlayerLink() 
{
}

void PlayerLink::Start()
{
	//�÷��̾ ������ �����Ҷ����� ���� ������ �ٸ��� ������ Level���� ��ġ�� ��������Ѵ�
	//SetPosition(GameEngineWindow::GetScale().Half());
	GameEngineRenderer* Render = CreateRenderer();
	//true �� ���� false �� �����ƴ�
	Render->CreateAnimation("Link_Walk_Down.bmp", "Walk_Down", 0, 7, 0.035f, true);
	Render->ChangeAnimation("Walk_Down");
	//�Ʒ����� ���� ���������� �� ������ ���´�
	//CreateRenderer("LinkStandStill.bmp");
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		//�̶� �빮�ڿ��� �Ѵ�
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Fire", 'K');
		GameEngineInput::GetInst()->CreateKey("Attack", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("InterAct", VK_LSHIFT);
	}
}
 
void PlayerLink::Update()
{
	GameEngineImage* ColMap = GameEngineImageManager::GetInst()->Find("ExMapColMap.bmp");

	if (nullptr == ColMap)
	{
		MsgBoxAssert("�浹�� ���� ã�� ���߽��ϴ�");
	}

	float4 CheckPos;
	float4 MoveDir = float4::ZERO;
	//�� �̹����� ĳ������ �̹����� �ȼ� ��ġ�� �����ϰ� ��������Ѵ�
	bool MoveLeft = false;
	bool MoveRight = false;
	bool MoveUp = false;
	bool MoveDown = false;

	//float DeltaTime = GameEngineTime::GetInst()->GetDeltaTime()
	//���� Ű�� �������ִٸ� �����̱�
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT;
		MoveLeft = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT;
		MoveRight = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir += float4::UP;
		MoveUp = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir += float4::DOWN;
		MoveDown = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}

	//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	{
		int Black = RGB(0, 0, 0);
		float4 MyPos = GetPosition();
		float4 MyPosTopRight = MyPos + float4{ 32.0f, -30.0f };
		float4 MyPosTopLeft = MyPos + float4{ -32.0f, -30.0f };
		float4 MyPosBotRight = MyPos + float4{ 32.0f, 42.0f };
		float4 MyPosBotLeft = MyPos + float4{ -32.0f, 42.0f };
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPosTopRight = NextPos + float4{ 32.0f, -30.0f };
		float4 CheckPosTopLeft = NextPos + float4{ -32.0f, -30.0f };
		float4 CheckPosBotRight = NextPos + float4{ 32.0f, 42.0f };
		float4 CheckPosBotLeft = NextPos + float4{ -32.0f, 42.0f };


		int ColorTopRight = ColMap->GetImagePixel(CheckPosTopRight);
		int ColorTopLeft = ColMap->GetImagePixel(CheckPosTopLeft);
		int ColorBotRight = ColMap->GetImagePixel(CheckPosBotRight);
		int ColorBotLeft = ColMap->GetImagePixel(CheckPosBotLeft);
		if (Black != ColorTopRight &&
			Black != ColorTopLeft &&
			Black != ColorBotRight &&
			Black != ColorBotLeft)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
		else
		{
			if (true == MoveLeft)
			{
				if (Black != ColMap->GetImagePixel({ MyPosTopLeft.x + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).x, MyPosTopLeft.y }) &&
					Black != ColMap->GetImagePixel({ MyPosBotLeft.x + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).x, MyPosBotLeft.y }))
				{
					SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
				}
			}

			if (true == MoveRight)
			{
				if (Black != ColMap->GetImagePixel({ MyPosTopRight.x + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).x, MyPosTopRight.y }) &&
					Black != ColMap->GetImagePixel({ MyPosBotRight.x + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).x, MyPosBotRight.y }))
				{
					SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
				}
			}

			if (true == MoveUp)
			{
				if (Black != ColMap->GetImagePixel({MyPosTopRight.x, MyPosTopRight.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y}) &&
					Black != ColMap->GetImagePixel({MyPosTopLeft.x, MyPosTopLeft.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y}))
				{
					SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
				}
			}

			if (true == MoveDown)
			{
				if (Black != ColMap->GetImagePixel({ MyPosBotRight.x, MyPosBotRight.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y }) &&
					Black != ColMap->GetImagePixel({ MyPosBotLeft.x, MyPosBotLeft.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y }))
				{
					SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
				}
			}
		}


	}
	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		Boomerang* Ptr = GetLevel()->CreateActor<Boomerang>((int)PlayLevelOrder::PLAYER);
		Ptr->SetPosition(GetPosition());
	}

	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

}
//�������� �� ���� ���͵��� �����Լ��� ȣ���Ѵ�
void PlayerLink::Render()
{
	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("�̹��� ������ �������� �̹����� ã�� ���߽��ϴ�");
	//}
	//GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());

}
