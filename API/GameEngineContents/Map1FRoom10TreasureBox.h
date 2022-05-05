#pragma once
#include <GameEngine/GameEngineActor.h>
class GameEngineRenderer;
// Ό³Έν :
class Map1FRoom10TreasureBox : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom10TreasureBox();
	~Map1FRoom10TreasureBox();

	// delete Function
	Map1FRoom10TreasureBox(const Map1FRoom10TreasureBox& _Other) = delete;
	Map1FRoom10TreasureBox(Map1FRoom10TreasureBox&& _Other) noexcept = delete;
	Map1FRoom10TreasureBox& operator=(const Map1FRoom10TreasureBox& _Other) = delete;
	Map1FRoom10TreasureBox& operator=(Map1FRoom10TreasureBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TreasureBoxRenderer_;
};

