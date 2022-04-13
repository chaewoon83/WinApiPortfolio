#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <map>
#include <list>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineActor;
struct ChangeOrderItem
{
	GameEngineActor* TargetObject; // �̳༮��
	int ChangeOrder; // �̷��� �ٲ��.
};

// ���� :
class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;
	friend GameEngineRenderer;
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
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		//protected�� �����ϱ����� ���ɽ���
		GameEngineActor* StartActor = NewActor;
		NewActor->SetLevel(this);
		NewActor->SetOrder(_Order);
		NewActor->SetName(_Name);
		//����� ȣ���ϸ� �ȵ�
		//protected�� �����ϱ����� ���ɽ��� (GameEngineActo���� friends �Ǿ�����)
		StartActor->Start();
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);
		//NewActor�� ������ GameEngineActor*�� ���̾�� �Ѵ�
		//insert �� find �� ������ ���ÿ� �Ѵ�
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
	//�����Լ�
	//�ٸ������� Loading ������ ���� ���Ͽ� protected �� �Ǵ�.
	//��������鼭 ���ҽ��� ���͸� ���鶧 ���
	virtual void Loading() = 0;
	//���� ������ ������Ʈ
	virtual void Update() = 0;
	//������������ ���緹���� �����Ҷ� "����"������ �����ϴ� �Լ�
	virtual void LevelChangeStart() {};
	//������������ ���緹���� �����Ҷ� "����"������ �����ϴ� �Լ�
	virtual void LevelChangeEnd() {}

private:
	// std::vector �� �����ϴ°� �� ���ٰ� �����Ѵ�
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	std::vector<ChangeOrderItem> ChangeOrderList;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

private:
	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;

	void AddRenderer(GameEngineRenderer* _Renderer);

	void ChangeUpdateOrder(GameEngineActor* _Actor, int _Oreder);

	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);

private:
	//������ Actor���� ������ ���� ����� Level����
	//Level���� �Ժη� GameEngineCollision* �� delete�ϸ� �ȵȴ�
	//����� Level���� �ϴ� ������ Level�� ��� Actor���� ���־�
	//�ٸ� Actor���� �浹 ������ �ս��� �ڵ��� �� �ֱ� �����̴�
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};

