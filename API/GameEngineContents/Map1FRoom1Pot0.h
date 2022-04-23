#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
// ���� :

class Map1FRoom1Pot0 : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom1Pot0();
	~Map1FRoom1Pot0();

	// delete Function
	Map1FRoom1Pot0(const Map1FRoom1Pot0& _Other) = delete;
	Map1FRoom1Pot0(Map1FRoom1Pot0&& _Other) noexcept = delete;
	Map1FRoom1Pot0& operator=(const Map1FRoom1Pot0& _Other) = delete;
	Map1FRoom1Pot0& operator=(Map1FRoom1Pot0&& _Other) noexcept = delete;

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
	GameEngineCollision* PotHitBox_2;
	float4 MoveDir_;
	float Speed_;
	float YSpeed_;
	float AirTime_;
	float CurAirTime_;


	///FSM
	PotState CurPotState_;
	void PotStateUpdate();
	void PotStateChange(PotState _State);

	void IdleStart();
	void CarriedStart();
	void InAirStart();
	void DeathStart();

	void IdleUpdate();
	void CarriedUpdate();
	void InAirUpdate();
	void DeathUpdate();
};

