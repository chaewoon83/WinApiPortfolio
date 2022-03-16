#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
class GameEngineLevel;

// ���� :
class GameEngineActor : public GameEngineNameObject
{
public:
	//SetLevel�Լ��� GameEngineLevel������ ȣ�� �� �� �ְԲ� �������
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:
	//�����ڿ����� ó�����ϴ� ��������ų� �����Ҷ� ó���Ұ�
	virtual void Start() = 0; // ��� ���Ϳ��� ������ �����ؾ��Ѵ�
	//���������� ������ ����ɶ� ȣ���
	virtual void Update() {} // ���� ���� ���Ϳ��� �����ؾ��Ѵ�
	virtual void Render() {} // ���� ���� ���Ϳ��� �����ؾ��Ѵ�
private:
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;
};

