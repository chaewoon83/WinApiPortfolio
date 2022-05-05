#pragma once
#include <GameEngine/GameEngineActor.h>
class GameEngineRenderer;
// Ό³Έν :
class Map1FRoom3EmptyTreasureBox : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom3EmptyTreasureBox();
	~Map1FRoom3EmptyTreasureBox();

	// delete Function
	Map1FRoom3EmptyTreasureBox(const Map1FRoom3EmptyTreasureBox& _Other) = delete;
	Map1FRoom3EmptyTreasureBox(Map1FRoom3EmptyTreasureBox&& _Other) noexcept = delete;
	Map1FRoom3EmptyTreasureBox& operator=(const Map1FRoom3EmptyTreasureBox& _Other) = delete;
	Map1FRoom3EmptyTreasureBox& operator=(Map1FRoom3EmptyTreasureBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TreasureBoxRenderer_;
};

