#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
// ���� :
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
	//�����Լ�
	//�ٸ������� Loading ������ ���� ���Ͽ� protected �� �Ǵ�.
	//��������鼭 ���ҽ��� ���͸� ���鶧 ���
	virtual void Loading() = 0;
	//���� ������ ������Ʈ
	virtual void Update() = 0;
	//������������ ���緹���� �����Ҷ� "����"������ �����ϴ� �Լ�
	virtual void SceneChangeStart() = 0;
	//������������ ���緹���� �����Ҷ� "����"������ �����ϴ� �Լ�
	virtual void SceneChangeEnd() = 0;

	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name)
	{
		return nullptr;
	}

private:
};

