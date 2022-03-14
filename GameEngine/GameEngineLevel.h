#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
// 설명 :
class GameEngine;

class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	//다른곳에서 Loading 실행을 막기 위하여 protected 로 건다.
	virtual void Loading() = 0;
	//레벨 수준의 업데이트
	virtual void Update() = 0;

private:
	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name)
	{
		return nullptr;
	}
};

