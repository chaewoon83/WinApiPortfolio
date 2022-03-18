#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>

GameEngineActor::GameEngineActor()
	:Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor() 
{
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

