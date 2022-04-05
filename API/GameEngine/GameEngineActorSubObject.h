#pragma once
#include <GameEngine/GameEngineActor.h>

// Waterfall design �̱� ������ ��ȯ������ �Ͼ �� ����
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
		//���� ������ IsUpdate_�� True���߸� ������Ʈ�� �Ѵ�
		return GameEngineUpdateObject::IsUpdate() && Actor_->IsUpdate();
	}

	inline bool IsDeath() override
	{
		//���� �ϳ��� ����־ ����ִ°��̴�.
		return GameEngineUpdateObject::IsDeath() || Actor_->IsDeath();
	}


protected:
	//���� ���ؿ��� ������ �Ǿ���Ѵ�. (���� �θ� ���� ����)
	inline void SetActor(GameEngineActor* _Actor)
	{
		Actor_ = _Actor;
	}
private:
	GameEngineActor* Actor_;
};

