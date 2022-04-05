#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class GameEngineImage;
class GmaeEngineCollision;
class PlayerLink : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerLink();
	~PlayerLink();

	// delete Function
	PlayerLink(const PlayerLink& _Other) = delete;
	PlayerLink(PlayerLink&& _Other) noexcept = delete;
	PlayerLink& operator=(const PlayerLink& _Other) = delete;
	PlayerLink& operator=(PlayerLink&& _Other) noexcept = delete;
	void PlayerMovement();

protected:


private:
	float Speed_;
	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision_;

	void Start() override;
	void Update() override;
	void Render() override;
};

