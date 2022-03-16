#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

// ���� :
class GameEngineActor : public GameEngineNameObject
{
private:
	float4 float1;
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
	virtual void Update() {}
	virtual void Render() {}
private:

};

