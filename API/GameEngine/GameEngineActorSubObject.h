#pragma once
#include <GameEngine/GameEngineActor.h>

// Waterfall design 이기 때문에 순환참조가 일어날 수 없다
//
class GameEngineActorSubObject : public GameEngineUpdateObject
{
	friend GameEngineActor;
public:
	// constrcuter destructer
	GameEngineActorSubObject();
	virtual ~GameEngineActorSubObject();

	// delete Function
	GameEngineActorSubObject(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject(GameEngineActorSubObject&& _Other) noexcept = delete;
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject& operator=(GameEngineActorSubObject&& _Other) noexcept = delete;
	inline GameEngineActor* GetActor() 
	{
		return Actor_;
	}

	inline bool IsUpdate() override
	{
		//나와 엑터의 IsUpdate_가 True여야만 업데이트를 한다
		return GameEngineUpdateObject::IsUpdate() && Actor_->IsUpdate();
	}

	inline bool IsDeath() override
	{
		//둘중 하나만 살아있어도 살아있는것이다.
		return GameEngineUpdateObject::IsDeath() || Actor_->IsDeath();
	}


protected:
	//엔진 수준에서 관리가 되어야한다. (오직 부모만 세팅 가능)
	inline void SetActor(GameEngineActor* _Actor)
	{
		Actor_ = _Actor;
	}
private:
	GameEngineActor* Actor_;
};

