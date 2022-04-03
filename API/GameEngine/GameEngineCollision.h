#pragma once
//�̹����� ������ �������� �� �� ����
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
#include <map>
//#include "GameEngineImage.h"
// ���� :
class GameEngineImage;
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;
public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	inline void SetPivot(const float4& _Pos)
	{
		Pivot_ = _Pos;
	}

	inline void SetScale(const float4& _Scale)
	{
		Scale_ = _Scale;
	}

	//�浹�� ����� �����ϴٸ� true����
	bool CollisionCheck(const std::string& _TargetGroup, 
		CollisionType _This = CollisionType::Circle, 
		CollisionType _Target = CollisionType::Circle);

protected:

private:
	//������ �߽ɿ����� ��ġ
	float4 Pivot_;
	//�߽��� �������� �� ũ��
	float4 Scale_;

//////////////////////////////////////////////////////////////////////////////////////////////Animation

};
