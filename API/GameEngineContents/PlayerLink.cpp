#include "PlayerLink.h"
#include <windows.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>


PlayerLink::PlayerLink() 
{
}

PlayerLink::~PlayerLink() 
{
}

void PlayerLink::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 200, 200 });
	//�Ʒ����� ���� ���������� �� ������ ���´�
	CreateRenderer("LinkStandStill.bmp");
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
}
 
void PlayerLink::Update()
{

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
