#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <map>
#include <list>
// ���� :
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

protected:
	//�����Լ�
	//�ٸ������� Loading ������ ���� ���Ͽ� protected �� �Ǵ�.
	//��������鼭 ���ҽ��� ���͸� ���鶧 ���
	virtual void Loading() = 0;
	//���� ������ ������Ʈ
	virtual void Update() = 0;
	//������������ ���緹���� �����Ҷ� "����"������ �����ϴ� �Լ�
	virtual void SceneChangeStart() {};
		//������������ ���緹���� �����Ҷ� "����"������ �����ϴ� �Լ�
	virtual void SceneChangeEnd() {}

	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name, int _Order)
	{
		ActorType* NewActor = new ActorType();
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);
		//NewActor�� ������ GameEngineActor*�� ���̾�� �Ѵ�
		//insert �� find �� ������ ���ÿ� �Ѵ�
		return nullptr;
	}

private:
	// std::vector �� �����ϴ°� �� ���ٰ� �����Ѵ�
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
};

