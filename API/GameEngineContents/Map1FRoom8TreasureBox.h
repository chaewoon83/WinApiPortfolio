#pragma once
#include <GameEngine/GameEngineActor.h>
class GameEngineRenderer;
// Ό³Έν :
class Map1FRoom8TreasureBox : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom8TreasureBox();
	~Map1FRoom8TreasureBox();

	// delete Function
	Map1FRoom8TreasureBox(const Map1FRoom8TreasureBox& _Other) = delete;
	Map1FRoom8TreasureBox(Map1FRoom8TreasureBox&& _Other) noexcept = delete;
	Map1FRoom8TreasureBox& operator=(const Map1FRoom8TreasureBox& _Other) = delete;
	Map1FRoom8TreasureBox& operator=(Map1FRoom8TreasureBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TreasureBoxRenderer_;
};

