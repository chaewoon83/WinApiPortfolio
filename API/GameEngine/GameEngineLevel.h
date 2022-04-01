#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <map>
#include <list>
#include <GameEngineBase/GameEngineMath.h>
// 설명 :
class GameEngine;
class GameEngineActor;

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
	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0 , const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		//protected에 접근하기위한 업케스팅
		GameEngineActor* StartActor = NewActor;
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		//맘대로 호출하면 안됨
		//protected에 접근하기위한 업케스팅 (GameEngineActo에서 friends 되어있음)
		StartActor->Start();
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);
		//NewActor는 무조건 GameEngineActor*의 값이어야 한다
		//insert 와 find 의 역할을 동시에 한다
		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline float4 SetCameraPos(const float4& _Value)
	{
		return CameraPos_ = _Value;
	}

	inline float4 MoveCameraPos(const float4& _Value)
	{
		return CameraPos_ += _Value;
	}

	float4 CameraPos_;

protected:
	//시점함수
	//다른곳에서 Loading 실행을 막기 위하여 protected 로 건다.
	//만들어지면서 리소스나 액터를 만들때 써라
	virtual void Loading() = 0;
	//레벨 수준의 업데이트
	virtual void Update() = 0;
	//이전레벨에서 현재레벨로 이전할때 "현재"레벨이 실행하는 함수
	virtual void LevelChangeStart() {};
		//이전레벨에서 현재레벨로 이전할때 "이전"레벨이 실행하는 함수
	virtual void LevelChangeEnd() {}

private:
	// std::vector 로 관리하는게 더 좋다고 생각한다
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
	void ActorRelease();
};

