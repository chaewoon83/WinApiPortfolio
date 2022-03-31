#include "GameEngineInput.h"
#include "GameEngineBase/GameEngineDebug.h"
#include "GameEngineString.h"

///////////////////////////////////////////////////////////////////////////////////////////////
void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{
		//Ű�� �ȴ��� ���¿��� Ű�� ��������
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ = 0.0f;
			Time_ += _DeltaTime;
		}
		//Ű�� ���� ���¿��� ��� �������� ������
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ += _DeltaTime;
		}
	}
	else
	{
		//Ű�� ���� ���¿��� Ű�� ������
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
			Time_ = 0.0f;
		}

		//Ű�� �ȴ��� ���¿��� Ű�� ��������
		else if (true == Up_)
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

bool GameEngineInput::IsKey(const std::string& _Name)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		return true;
	}
	return false;
}

void GameEngineInput::CreateKey(const std::string& _Name, int _Key)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() != AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�̹� �����ϴ� Ű�� �� ������� �߽��ϴ�");
		return;
	}

	if ('a' <= _Key || 'z' >= _Key)
	{
		_Key = std::toupper(_Key);
	}

	AllInputKey_.insert(std::make_pair(UpperKey, GameEngineKey()));
	AllInputKey_[UpperKey].Key_ = _Key;
	AllInputKey_[UpperKey].Reset();

}

void GameEngineInput::Update(float _DeltaTime)
{
	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();
	for (; KeyUpdateEnd != KeyUpdateStart; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;
		CurrentKey.Update(_DeltaTime);
	}
}


float GameEngineInput::GetTime(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�");
		return false;
	}
	return AllInputKey_[UpperKey].Time_;
}

bool GameEngineInput::IsDown(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�");
		return false;
	}
	return AllInputKey_[UpperKey].Down_;
}
bool GameEngineInput::IsPress(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�");
		return false;
	}
	return AllInputKey_[UpperKey].Press_;
}
bool GameEngineInput::IsUp(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�");
		return false;
	}
	return AllInputKey_[UpperKey].Up_;
}
bool GameEngineInput::IsFree(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);
	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�");
		return false;
	}
	return AllInputKey_[UpperKey].Free_;
}
