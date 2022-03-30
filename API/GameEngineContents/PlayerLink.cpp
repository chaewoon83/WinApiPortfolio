#include "PlayerLink.h"
#include <windows.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h>
#include "Boomerang.h"


PlayerLink::PlayerLink() 
	:Speed_(200.0f)
{
}

PlayerLink::~PlayerLink() 
{
}

void PlayerLink::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	//GameEngineRenderer* Render = CreateRenderer("Right_Beam_Kirby.bmp");
	//Render->SetIndex(10);
	//�Ʒ����� ���� ���������� �� ������ ���´�
	CreateRenderer("LinkStandStill.bmp");

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

	//float DeltaTime = GameEngineTime::GetInst()->GetDeltaTime()
	//���� Ű�� �������ִٸ� �����̱�
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		Boomerang* Ptr = GetLevel()->CreateActor<Boomerang>((int)PlayLevelOrder::PLAYER);
		Ptr->SetPosition(GetPosition());

	}

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
