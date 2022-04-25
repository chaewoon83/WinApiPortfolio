#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
// ���� :

class Map1FRoom1Pot1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom1Pot1();
	~Map1FRoom1Pot1();

	// delete Function
	Map1FRoom1Pot1(const Map1FRoom1Pot1& _Other) = delete;
	Map1FRoom1Pot1(Map1FRoom1Pot1&& _Other) noexcept = delete;
	Map1FRoom1Pot1& operator=(const Map1FRoom1Pot1& _Other) = delete;
	Map1FRoom1Pot1& operator=(Map1FRoom1Pot1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	bool CheckPickUpEnd();

	GameEngineRenderer* Renderer_;
	GameEngineCollision* BlockCol_;
	GameEngineCollision* PickUpCol_;
	GameEngineCollision* PotHitBox_;
	GameEngineCollision* PotHitBox2_;
	float4 PotPos_;
	float4 MoveDir_;
	float Speed_;
	float YSpeed_;
	float CurYSpeed_;
	float AirTime_;
	float CurAirTime_;

	bool IsInRoom_;

	void Reset();

	///FSM
	PotState CurPotState_;
	void PotStateUpdate();
	void PotStateChange(PotState _State);

	void IdleStart();
	void CarriedStart();
	void InAirStart();
	void DeathAnimationStart();
	void DeathStart();

	void IdleUpdate();
	void CarriedUpdate();
	void InAirUpdate();
	void DeathAnimationUpdate();
	void DeathUpdate();
};
