#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include "GameEngineRenderer.h"
#include "GameEngineCollision.h"


GameEngineActor::GameEngineActor()
	:Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor()
{
	{
		std::list <GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
		std::list <GameEngineRenderer*>::iterator EndIter = RenderList_.end();
		for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != *StartIter)
		{
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
	}
}
	{
		std::list <GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
		std::list <GameEngineCollision*>::iterator EndIter = CollisionList_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != *StartIter)
			{
				delete (*StartIter);
				(*StartIter) = nullptr;
			}
		}
	}

	
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);

	//선생님에 따라 기본적으로 중앙을 기준으로 한다.

	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

GameEngineRenderer* GameEngineActor::CreateRenderer(RenderPivot _PivotType /*= RenderPivot ::CENTER*/, const float4& _PivotPos /*= {0,0}*/)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();
	NewRenderer->SetActor(this);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRenderer(
	const std::string& _Image, 
	RenderPivot _PivotType, 
	const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();
	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRendererToScale
(const std::string& _Image, const float4& _Scale, RenderPivot _PivotType,
	const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();
	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetScale(_Scale);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

void GameEngineActor::Rendering()
{
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();
	
	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		(*StartRenderIter)->Render();
	}

}

GameEngineCollision* GameEngineActor::CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot /*= { 0, 0 }*/)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();
	NewCollision->SetActor(this);
	NewCollision->SetPivot(_Pivot);
	NewCollision->SetScale(_Scale);

	GetLevel()->AddCollision(_GroupName, NewCollision);
	CollisionList_.push_back(NewCollision);
	return NewCollision;
}

void GameEngineActor::Release()
{
	//엑터를 릴리즈하면 모두가 delete되지만, collision만 파괴하고 싶거나 render만 파괴하고 싶을 경우도 있기 때문에
	//분리해서 릴리즈 한다
	{
		std::list <GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
		std::list <GameEngineRenderer*>::iterator EndIter = RenderList_.end();
		for (; StartIter != EndIter; )
		{
			if (false == (*StartIter)->IsDeath())
			{
				++StartIter;
				continue;
			}
			delete (*StartIter);
			StartIter = RenderList_.erase(StartIter);
			(*StartIter) = nullptr;
		}

		{
			std::list <GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
			std::list <GameEngineCollision*>::iterator EndIter = CollisionList_.end();
			for (; StartIter != EndIter; )
			{
				if (false == (*StartIter)->IsDeath())
				{
					++StartIter;
					continue;
				}
				delete (*StartIter);
				StartIter = CollisionList_.erase(StartIter);
				(*StartIter) = nullptr;
			}
		}
	}
}

