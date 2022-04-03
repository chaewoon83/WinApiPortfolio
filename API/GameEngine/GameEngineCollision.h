#pragma once
//이미지가 없으면 렌더링을 할 수 없다
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
#include <map>
//#include "GameEngineImage.h"
// 설명 :
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

	//충돌한 대상이 존재하다면 true리턴
	bool CollisionCheck(const std::string& _TargetGroup, 
		CollisionType _This = CollisionType::Circle, 
		CollisionType _Target = CollisionType::Circle);

protected:

private:
	//엑터의 중심에서의 위치
	float4 Pivot_;
	//중심을 기준으로 한 크기
	float4 Scale_;

//////////////////////////////////////////////////////////////////////////////////////////////Animation

};
