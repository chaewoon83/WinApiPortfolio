#include "GameEngineInput.h"
#include "GameEngineBase/GameEngineDebug.h"

///////////////////////////////////////////////////////////////////////////////////////////////
void GameEngineInput::GameEngineKey::Update()
{
	if (true == KeyCheck())
	{
		//키가 안눌린 상태에서 키를 눌렀을때
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
		//키가 눌린 상태에서 계속 눌러지고 있을때
		else if (true == Down_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
	}
	else
	{
		//키가 눌린 상태에서 키를 땠을때
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
		}

		//키가 안눌린 상태에서 키를 눌렀을때
		if (true == Up_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////

GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

bool GameEngineInput::IsKey(std::string _Name)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		return true;
	}
	return false;
}

void GameEngineInput::CreateKey(std::string _Name, int _Key)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 키를 또 만들려고 했습니다");
		return;
	}

	if ('a' <= _Key || 'z' >= _Key)
	{
		_Key = std::toupper(_Key);
	}

	AllInputKey_.insert(std::make_pair(_Name, GameEngineKey()));
	AllInputKey_[_Name].Key_ = _Key;
	AllInputKey_[_Name].Reset();

}

void GameEngineInput::Update()
{
	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();
	for (; KeyUpdateEnd != KeyUpdateStart; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;
		CurrentKey.Update();
	}
}


bool GameEngineInput::IsDown(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다");
		return false;
	}
	return AllInputKey_[_Name].Down_;
}
bool GameEngineInput::IsPress(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다");
		return false;
	}
	return AllInputKey_[_Name].Press_;
}
bool GameEngineInput::IsUp(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다");
		return false;
	}
	return AllInputKey_[_Name].Up_;
}
bool GameEngineInput::IsFree(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다");
		return false;
	}
	return AllInputKey_[_Name].Free_;
}