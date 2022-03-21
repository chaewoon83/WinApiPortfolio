#pragma once
//이미지가 없으면 렌더링을 할 수 없다
#include "GameEngineImage.h"
#include "GameEngineEnum.h"

// 설명 :
class GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType = _Type;
	}

	void SetImage(const std::string& _Name);
	void Render();

protected:

private:
	GameEngineImage* Image_;
	RenderPivot PivotType;
};

