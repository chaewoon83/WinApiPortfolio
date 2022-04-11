#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class TitleTriangle : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleTriangle();
	~TitleTriangle();

	// delete Function
	TitleTriangle(const TitleTriangle& _Other) = delete;
	TitleTriangle(TitleTriangle&& _Other) noexcept = delete;
	TitleTriangle& operator=(const TitleTriangle& _Other) = delete;
	TitleTriangle& operator=(TitleTriangle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	float4 TopTrianglePos_;
	float4 BotRightTrianglePos_;
	float4 BotLeftTrianglePos_;
};

