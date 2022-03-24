#include "GameEngineInput.h"
#include "GameEngineBase/GameEngineDebug.h"

GameEngineInput* GameEngineInput::Inst_ = nullptr;

GameEngineInput::GameEngineInput() 
{
}

GameEngineInput::~GameEngineInput() 
{
}

void GameEngineInput::CreateKey(std::string _Name, int _Key)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 키를 또 만들려고 했습니다")
	}

	AllInputKey_.insert(std::make_pair(_Name, GameEngineKey()));
	
}


