#pragma once
#include <GameEngine/GameEngineActor.h>
class GameEngineRenderer;
// Ό³Έν :
class Map1FRoom3TreasureBox : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom3TreasureBox();
	~Map1FRoom3TreasureBox();

	// delete Function
	Map1FRoom3TreasureBox(const Map1FRoom3TreasureBox& _Other) = delete;
	Map1FRoom3TreasureBox(Map1FRoom3TreasureBox&& _Other) noexcept = delete;
	Map1FRoom3TreasureBox& operator=(const Map1FRoom3TreasureBox& _Other) = delete;
	Map1FRoom3TreasureBox& operator=(Map1FRoom3TreasureBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TreasureBoxRenderer_;
};

