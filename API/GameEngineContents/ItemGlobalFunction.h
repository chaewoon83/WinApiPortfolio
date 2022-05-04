#pragma once
#include <GameEngineBase/GameEngineMath.h>
class GameEngineActor;
class GameEngineRenderer;
// Ό³Έν :
class ItemGlobalFunction
{
public:
	// constrcuter destructer
	ItemGlobalFunction();
	~ItemGlobalFunction();

	// delete Function
	ItemGlobalFunction(const ItemGlobalFunction& _Other) = delete;
	ItemGlobalFunction(ItemGlobalFunction&& _Other) noexcept = delete;
	ItemGlobalFunction& operator=(const ItemGlobalFunction& _Other) = delete;
	ItemGlobalFunction& operator=(ItemGlobalFunction&& _Other) noexcept = delete;
	
	static float BounceUpdate(float& _Time, float& _Speed, float _BounceSpeed, float _PivotHeight);
	static void BlinkUpdate(bool& _IsBlink, bool& _IsAlphaOn, float& _CurBlinkTime, float& _CurBlinkFreq, float _BlinkTime, float _BlinkFreq, GameEngineRenderer* _Renderer);
protected:

private:

};

