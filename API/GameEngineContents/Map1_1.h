#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Map1_1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1_1();
	~Map1_1();

	// delete Function
	Map1_1(const Map1_1& _Other) = delete;
	Map1_1(Map1_1&& _Other) noexcept = delete;
	Map1_1& operator=(const Map1_1& _Other) = delete;
	Map1_1& operator=(Map1_1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

