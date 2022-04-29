#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
// Ό³Έν :

class Map1FRoom10Pot0 : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom10Pot0();
	~Map1FRoom10Pot0();

	// delete Function
	Map1FRoom10Pot0(const Map1FRoom10Pot0& _Other) = delete;
	Map1FRoom10Pot0(Map1FRoom10Pot0&& _Other) noexcept = delete;
	Map1FRoom10Pot0& operator=(const Map1FRoom10Pot0& _Other) = delete;
	Map1FRoom10Pot0& operator=(Map1FRoom10Pot0&& _Other) noexcept = delete;

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

