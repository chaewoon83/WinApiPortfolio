#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
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

protected:
	float Speed_;
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

