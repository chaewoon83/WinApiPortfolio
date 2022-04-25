#pragma once
//�̹����� ������ �������� �� �� ����
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
#include <map>
#include <vector>
//#include "GameEngineImage.h"
// ���� :
class GameEngineImage;
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;
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


	inline float4 GetCollisionPos()
	{
		return Pivot_ + GetActor()->GetPosition();
	}
	
	inline GameEngineRect GetRect()
	{
		if (true == NextPos_.CompareInt2D(float4::ZERO))
		{
			return GameEngineRect(GetActor()->GetPosition() + Pivot_, Scale_);
		}
		else
		{
			return GameEngineRect(Pivot_ + NextPos_, Scale_);
		}

	}

	void CameraEffectOff()
	{
		IsCameraEffect_ = false;
	}

	void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}


	//�浹�� ����� �����ϴٸ� true����
	bool CollisionCheck(const std::string& _TargetGroup, 
		CollisionType _This = CollisionType::Circle, 
		CollisionType _Target = CollisionType::Circle);

	bool NextPostCollisionCheck(
		const std::string& _TargetGroup,
		float4 NextPos,
		CollisionType _This = CollisionType::Circle,
		CollisionType _Target = CollisionType::Circle
	);

	bool CollisionResult(const std::string& _TargetGroup,
		std::vector<GameEngineCollision*>& _ColResult,
		CollisionType _This = CollisionType::Circle,
		CollisionType _Target = CollisionType::Circle);

	void DebugRender();

protected:

private:
	//������ �߽ɿ����� ��ġ
	float4 Pivot_;
	//�߽��� �������� �� ũ��
	float4 Scale_;
	//�⺻ 0, NextPostCollisionCheck���� ���δ�
	float4 NextPos_;

	bool IsCameraEffect_;

	std::string CollisionName_;

	void NextPosReset()
	{
		NextPos_ = float4::ZERO;
	}
};
