#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include "GameEngineRenderer.h"

GameEngineActor::GameEngineActor()
	:Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor() 
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

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);

	//�����Կ� ���� �⺻������ �߾��� �������� �Ѵ�.

	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

GameEngineRenderer* GameEngineActor::CreateRenderer(
	const std::string& _Image, 
	RenderPivot _PivotType, 
	const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();
	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetImageScale();
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetType(_PivotType);
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
	NewRenderer->SetType(_PivotType);
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

