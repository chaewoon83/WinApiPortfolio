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
		MsgBoxAssert("�̹� �����ϴ� Ű�� �� ������� �߽��ϴ�")
	}

	AllInputKey_.insert(std::make_pair(_Name, GameEngineKey()));
	
}


