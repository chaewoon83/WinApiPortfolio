#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Boomerang : public GameEngineActor
{
public:
	// constrcuter destructer
	Boomerang();
	~Boomerang();

	// delete Function
	Boomerang(const Boomerang& _Other) = delete;
	Boomerang(Boomerang&& _Other) noexcept = delete;
	Boomerang& operator=(const Boomerang& _Other) = delete;
	Boomerang& operator=(Boomerang&& _Other) noexcept = delete;
	float Time;


protected:
	void Start() override;
	void Update() override;
private:

};
