#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngine.h"

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer() 
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, TransColor_(RGB(255, 0, 255))
	//11111111 00000000 11111111 �� ���� ����� �����̴� (unsigned int �� RBGA�� ǥ���Ѵ�)
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name+ "�������� �ʴ� �̹����� �������� �����Ϸ� �߽��ϴ�.");
		return;
	}
	Image_ = FindImage;
}

void GameEngineRenderer::Render()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �̹����� ���õǾ����� �ʾ� �������� ���� �ʾҽ��ϴ�.");
		return;
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;
	float4 RenderScale = RenderScale_;

	switch (ScaleMode_)
	{
	case RenderScaleMode::Image:
		RenderScale = Image_->GetScale();
		break;
	case RenderScaleMode::User:
		break;
	default:
		break;
	}

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale, TransColor_);
		break;
	case RenderPivot::BOT:
		//GameEngine::BackBufferImage()->BitCopyCenter(Image_, RenderPos);
		break;
	default:
		break;
	}
	//GameEngine::BackBufferImage()->BitCopyBot(Image_, GetActor()->GetPosition());
}
