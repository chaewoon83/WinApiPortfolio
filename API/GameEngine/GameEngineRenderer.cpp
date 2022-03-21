#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngine.h"

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name+ "�������� �ʴ� �̹����� �������� �����Ϸ� �߽��ϴ�.");
		return;
	}
	Image_ = FindImage;
}

void GameEngineRenderer::Render()
{
	GameEngine::BackBufferImage()->BitCopyBot(Image_, GetPosition());
}
