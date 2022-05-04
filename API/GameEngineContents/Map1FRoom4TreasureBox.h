#pragma once
#include <GameEngine/GameEngineActor.h>
class GameEngineRenderer;
// Ό³Έν :
class Map1FRoom4TreasureBox : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom4TreasureBox();
	~Map1FRoom4TreasureBox();

	// delete Function
	Map1FRoom4TreasureBox(const Map1FRoom4TreasureBox& _Other) = delete;
	Map1FRoom4TreasureBox(Map1FRoom4TreasureBox&& _Other) noexcept = delete;
	Map1FRoom4TreasureBox& operator=(const Map1FRoom4TreasureBox& _Other) = delete;
	Map1FRoom4TreasureBox& operator=(Map1FRoom4TreasureBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TreasureBoxRenderer_;
};

