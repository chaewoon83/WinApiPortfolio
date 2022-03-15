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
	//시점함수
	//다른곳에서 Loading 실행을 막기 위하여 protected 로 건다.
	//만들어지면서 리소스나 액터를 만들때 써라
	virtual void Loading() = 0;
	//레벨 수준의 업데이트
	virtual void Update() = 0;
	//이전레벨에서 현재레벨로 이전할때 "현재"레벨이 실행하는 함수
	virtual void SceneChangeStart() = 0;
	//이전레벨에서 현재레벨로 이전할때 "이전"레벨이 실행하는 함수
	virtual void SceneChangeEnd() = 0;

	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name)
	{
		return nullptr;
	}

private:
};

