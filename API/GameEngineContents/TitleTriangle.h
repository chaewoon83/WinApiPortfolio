#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
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
	bool IsTriangleExist_;
	bool IsTriangleDeath_;

	GameEngineRenderer* TopTriangle;
	GameEngineRenderer* BotRightTriangle;
	GameEngineRenderer* BotLeftTriangle;

private:
	float4 SetRenderMove(float4& _Pos, const float4& _Value)
	{
		_Pos += _Value;
		return _Pos;
	}
};


