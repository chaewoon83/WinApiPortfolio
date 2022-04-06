#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineTime.h>

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, TransColor_(RGB(255, 0, 255))
	//11111111 00000000 11111111 �� ���� ����� �����̴� (unsigned int �� RBGA�� ǥ���Ѵ�)
	, RenderImagePivot_({ 0, 0 })
	, IsCameraEffect_(true)

{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �ʴ� �̹����� ũ�⸦ �����Ϸ� �߽��ϴ�");
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
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �������� �����Ϸ� �߽��ϴ�.");
		return;
	}
	Image_ = FindImage;
	SetImageScale();
}

void GameEngineRenderer::Render()
{

	if (nullptr != CurrentAnimation_)
	{
		CurrentAnimation_->Update();
	}

	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �̹����� ���õǾ����� �ʾ� �������� ���� �ʾҽ��ϴ�.");
		return;
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	if (true == IsCameraEffect_)
	{
		RenderPos -= GetActor()->GetLevel()->GetCameraPos();
	}

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		//void GameEngineImage::TransCopy(GameEngineImage * _Other, const float4 & _CopyPos, const float4 & _CopyScale
		//	, const float4 & _OtherPivot, const float4 & _OtherScale, unsigned int _TransColor)
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	case RenderPivot::BOT:
	{
		float4 Scale = RenderScale_.Half();
		Scale.y *= 2;

		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	}
	default:
		break;
	}
	//GameEngine::BackBufferImage()->BitCopyBot(Image_, GetActor()->GetPosition());
}

void GameEngineRenderer::SetIndex(size_t _Index, float4 _Scale)
{
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("�̹����� �κ������� ����� �� �ְ� �߷����� ���� �̹����Դϴ�");
		return;
	}
	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	if (-1.0f == _Scale.x ||
		-1.0f == _Scale.y)
	{
		// �ڸ� �̹��� ũ�� �״�� ������ ȭ�鿡 ����
		RenderScale_ = Image_->GetCutScale(_Index);
	}
	else
	{
		// �Էµ� �������� �̹��� ũ��� ������ ȭ�鿡 ���� 
		RenderScale_ = _Scale;
	}
	RenderImageScale_ = Image_->GetCutScale(_Index);
}


//////////////////////////////////////////////////////////////////////////////////////////// Animation

void GameEngineRenderer::ChangeAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);
	if (Animations_.end() == FindIter)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� �ٲٷ� �մϴ�");
		return;
	}

	CurrentAnimation_ = &(FindIter->second);
}

void GameEngineRenderer::CreateAnimation(
	const std::string& _Image,
	const std::string& _Name,
	int _StartIndex,
	int _EndIndex,
	float _InterTime,
	bool _Loop /*= true*/)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssert("�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�");
		return;
	}
	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� �� ������� �߽��ϴ�");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];
	NewAnimation.Renderer_ = this;
	NewAnimation.Image_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;
}

void GameEngineRenderer::FrameAnimation::Update()
{
	CurrentInterTime_ -= GameEngineTime::GetDeltaTime();
	if (0 >= CurrentInterTime_)
	{
		CurrentInterTime_ = InterTime_;
		++CurrentFrame_;
		if (EndFrame_ < CurrentFrame_)
		{
			if (true == Loop_)
			{
				CurrentFrame_ = StartFrame_;
			}
			else
			{
				CurrentFrame_ = EndFrame_;
			}
		}
	}
	Renderer_->Image_ = Image_;
	Renderer_->SetIndex(CurrentFrame_);
}

void GameEngineRenderer::SetOrder(int _Order)
{
	if (nullptr == GetActor())
	{
		MsgBoxAssert("������ ������ �����ϴ��� ���Ͱ� ���õǾ����� �ʽ��ϴ�");
	}

	if (nullptr == GetActor()->GetLevel())
	{
		MsgBoxAssert("������ ������ �����ϴ��� ������ ���õǾ����� �ʽ��ϴ�");
	}

	GetActor()->GetLevel()->ChangeRenderOrder(this, _Order);
}