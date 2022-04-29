#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
// ���� :

class Map1FRoom10Pot2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom10Pot2();
	~Map1FRoom10Pot2();

	// delete Function
	Map1FRoom10Pot2(const Map1FRoom10Pot2& _Other) = delete;
	Map1FRoom10Pot2(Map1FRoom10Pot2&& _Other) noexcept = delete;
	Map1FRoom10Pot2& operator=(const Map1FRoom10Pot2& _Other) = delete;
	Map1FRoom10Pot2& operator=(Map1FRoom10Pot2&& _Other) noexcept = delete;

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

