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
	//11111111 00000000 11111111 의 색을 만들어 낸것이다 (unsigned int 가 RBGA를 표현한다)
	, RenderImagePivot_({0, 0})

{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("존재하지 않는 이미지로 크기를 조절하려 했습니다");
		return;
	}
	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale();
	RenderImageScale_ = Image_->GetScale();
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name+ "존재하지 않는 이미지를 랜더러에 세팅하려 했습니다.");
		return;
	}
	Image_ = FindImage;
	SetImageScale();
}

void GameEngineRenderer::Render()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("렌더러에 이미지가 세팅되어있지 않아 렌더링이 되지 않았습니다.");
		return;
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		//void GameEngineImage::TransCopy(GameEngineImage * _Other, const float4 & _CopyPos, const float4 & _CopyScale
		//	, const float4 & _OtherPivot, const float4 & _OtherScale, unsigned int _TransColor)
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	case RenderPivot::BOT:
		//GameEngine::BackBufferImage()->BitCopyCenter(Image_, RenderPos);
		break;
	default:
		break;
	}
	//GameEngine::BackBufferImage()->BitCopyBot(Image_, GetActor()->GetPosition());
}

void GameEngineRenderer::SetIndex(size_t _Index, float4 _Scale)
{
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("이미지가 부분적으로 사용할 수 있게 잘려있지 않은 이미지입니다");
		return;
	}
	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	if (-1.0f == _Scale.x ||
		-1.0f == _Scale.y)
	{
		RenderScale_ = Image_->GetCutScale(_Index);
	}
	else
	{
		RenderScale_ = _Scale;
	}
	RenderImageScale_ = Image_->GetCutScale(_Index);
}
