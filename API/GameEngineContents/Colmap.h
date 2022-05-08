#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
// Ό³Έν :
class Colmap : public GameEngineActor
{
public:
	// constrcuter destructer
	Colmap();
	~Colmap();

	// delete Function
	Colmap(const Colmap& _Other) = delete;
	Colmap(Colmap&& _Other) noexcept = delete;
	Colmap& operator=(const Colmap& _Other) = delete;
	Colmap& operator=(Colmap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* Map1F_1_Renderer_;
	GameEngineRenderer* Map1F_2_Renderer_;

	bool IsDeugModeOn_;
	bool IsIn1F_;
};

