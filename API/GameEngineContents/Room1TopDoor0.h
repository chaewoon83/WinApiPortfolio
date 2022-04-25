#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class GameEngineRenderer;
class GameEngineCollision;
class Room1TopDoor0 : public GameEngineActor
{
public:
	// constrcuter destructer
	Room1TopDoor0();
	~Room1TopDoor0();

	// delete Function
	Room1TopDoor0(const Room1TopDoor0& _Other) = delete;
	Room1TopDoor0(Room1TopDoor0&& _Other) noexcept = delete;
	Room1TopDoor0& operator=(const Room1TopDoor0& _Other) = delete;
	Room1TopDoor0& operator=(Room1TopDoor0&& _Other) noexcept = delete;

	static GameEngineRenderer* Room1TopDoor0_;
	static GameEngineCollision* Room1Door0Col_;
protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	float4 DoorPos_;

public:
};

