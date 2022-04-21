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
	//11111111 00000000 11111111 의 색을 만들어 낸것이다 (unsigned int 가 RBGA를 표현한다)
	, RenderImagePivot_({ 0, 0 })
	, IsCameraEffect_(true)
	, Alpha_(255)
	, RotZ_(0.0f)
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
	RenderScale_ = Image_->GetScale();		//화면 출력 크기, 이미지 크기로
	RenderImageScale_ = Image_->GetScale(); //실제 이미지를, 이미지크기로
	RenderImagePivot_ = float4::ZERO;
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지를 랜더러에 세팅하려 했습니다.");
		return;
	}
	Image_ = FindImage;
	SetImageScale();
}

void GameEngineRenderer::SetRotationFilter(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지를 랜더러에 세팅하려고 했습니다.");
		return;
	}

	RotationFilterImage_ = FindImage;
}


void GameEngineRenderer::Render()
{

	if (nullptr != CurrentAnimation_) //CurrentAnimation이 nullptr이면 애니메이션이 지정된 렌더러가 아니므로
	{
		CurrentAnimation_->Update();
	}

	if (nullptr == Image_)
	{
		MsgBoxAssert("렌더러에 이미지가 세팅되어있지 않아 렌더링이 되지 않았습니다.");
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

		if (Alpha_ != 255)
		{
			GameEngine::BackBufferImage()->AlphaCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, Alpha_);
		}
		else if (RotZ_ != 0.0f)
		{
			GameEngine::BackBufferImage()->PlgCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, RotZ_, RotationFilterImage_);
		}
		else 
		{
			GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		} 
		break;
		//void GameEngineImage::TransCopy(GameEngineImage * _Other, const float4 & _CopyPos, const float4 & _CopyScale
		//	, const float4 & _OtherPivot, const float4 & _OtherScale, unsigned int _TransColor)
	case RenderPivot::BOT:
	{
		float4 Scale = RenderScale_.Half();
		Scale.y *= 2;

		if (Alpha_ == 255)
		{
			GameEngine::BackBufferImage()->AlphaCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, Alpha_);
		}
		else if (RotZ_ != 0.0f)
		{
			GameEngine::BackBufferImage()->PlgCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, RotZ_, RotationFilterImage_);
		}
		else
		{
			GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		}

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
		MsgBoxAssert("이미지가 부분적으로 사용할 수 있게 잘려있지 않은 이미지입니다");
		return;
	}
	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	if (-1.0f == _Scale.x ||
		-1.0f == _Scale.y)
	{
		// 자른 이미지 크기 그대로 렌더링 화면에 띄우기
		RenderScale_ = Image_->GetCutScale(_Index);
	}
	else
	{
		// 입력된 스케일의 이미지 크기로 렌더링 화면에 띄우기 
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
		MsgBoxAssert("존재하지 않는 애니메이션으로 바꾸려 합니다");
		return;
	}
	CurrentAnimation_ = &(FindIter->second); //FrameAnimation은 값형이다
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
		MsgBoxAssert("존재하지 않는 이미지로 애니메이션을 만드려고 했습니다");
		return;
	}
	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];
	NewAnimation.SetName(_Name);
	NewAnimation.TimeKey = 0;
	NewAnimation.Renderer_ = this;
	NewAnimation.Image_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;
}


void GameEngineRenderer::CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop /*= true*/)
{
	GameEngineFolderImage* FindImage = GameEngineImageManager::GetInst()->FolderImageFind(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지로 애니메이션을 만들려고 했습니다.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];
	NewAnimation.SetName(_Name);
	NewAnimation.TimeKey = 0;
	NewAnimation.Renderer_ = this;
	NewAnimation.FolderImage_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;

}

void GameEngineRenderer::CreateFolderAnimationTimeKey(const std::string& _Image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop /*= true*/)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지로 애니메이션을 만들려고 했습니다.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];

	NewAnimation.SetName(_Name);
	NewAnimation.Renderer_ = this;
	NewAnimation.TimeKey = _TimeScaleKey;
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
	IsEnd = false;
	if (false == Renderer_->Pause_)
	{
		CurrentInterTime_ -= GameEngineTime::GetInst()->GetDeltaTime(TimeKey);
		if (0 >= CurrentInterTime_)
		{
			CurrentInterTime_ = InterTime_;
			++CurrentFrame_;
			if (EndFrame_ < CurrentFrame_)
			{
				if (true == Loop_)
				{
					IsEnd = true;
					CurrentFrame_ = StartFrame_;	// Loop가 True라면 이미지를 반복시킨다.
				}
				else
				{
					IsEnd = true;
					CurrentFrame_ = EndFrame_;	// Loop가 false라면 애니메이션 진행후 EndFrame으로 고정시킨다.
				}
			}
	}

	}
	if (nullptr != Image_)
	{
		Renderer_->Image_ = Image_;		// 렌더러에게 이 애니메이션 만들때 세팅했던 이미지를 세팅해준다.
		if (Renderer_->ScaleMode_ == RenderScaleMode::User)
		{
			Renderer_->SetIndex(CurrentFrame_, Renderer_->RenderScale_);
		}
		else
		{
			Renderer_->SetIndex(CurrentFrame_);	// 렌더러에게 인덱스도 세팅해준다. 즉, 해당 애니메이션 이미지의 몇번째 칸(Index) 세팅해주면 렌더러는 알아서 출력한다.
		}
	}
	else if (nullptr != FolderImage_)
	{
		Renderer_->Image_ = FolderImage_->GetImage(CurrentFrame_);		// 렌더러에게 이 애니메이션 만들때 세팅했떤 이미지를 세팅해준다.
		Renderer_->SetImageScale();	// 렌더러에게 인덱스도 세팅해준다. 즉, 해당 애니메이션 이미지의 몇번째 칸(Index) 세팅해주면 렌더러는 알아서 출력한다.
	}
}

void GameEngineRenderer::SetOrder(int _Order)
{
	if (nullptr == GetActor())
	{
		MsgBoxAssert("렌더링 오더를 세팅하는중 액터가 세팅되어있지 않습니다");
	}

	if (nullptr == GetActor()->GetLevel())
	{
		MsgBoxAssert("렌더링 오더를 세팅하는중 레벨이 세팅되어있지 않습니다");
	}

	GetActor()->GetLevel()->ChangeRenderOrder(this, _Order);
}

bool GameEngineRenderer::IsEndAnimation()
{
	return CurrentAnimation_->IsEnd;
}

bool GameEngineRenderer::IsAnimationName(const std::string& _Name)
{
	return CurrentAnimation_->GetNameConstRef() == _Name;
}

const GameEngineRenderer::FrameAnimation* GameEngineRenderer::FindAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);

	if (Animations_.end() == FindIter)
	{
		return nullptr;
	}

	return &FindIter->second;
}