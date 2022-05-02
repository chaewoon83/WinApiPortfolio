#pragma once

#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineContentsEnum.h"
class GameEngineRenderer;
class GameEngineActor;
class GameEngineCollision;
// ���� :
class EnemyGlobalFunction
{
public:
	// constrcuter destructer
	EnemyGlobalFunction();
	~EnemyGlobalFunction();

	// delete Function
	EnemyGlobalFunction(const EnemyGlobalFunction& _Other) = delete;
	EnemyGlobalFunction(EnemyGlobalFunction&& _Other) noexcept = delete;
	EnemyGlobalFunction& operator=(const EnemyGlobalFunction& _Other) = delete;
	EnemyGlobalFunction& operator=(EnemyGlobalFunction&& _Other) noexcept = delete;

	static void KnockBackMoveFunction(int _TimeScale, float _Speed, float4 _MoveDir, GameEngineCollision* _Collision, GameEngineActor* _Actor);
	static void PopoBlinkUpdate(int _TimeScale, bool& _IsBlink, bool& _IsAlphaOn,
		float _BlinkTime, float& _CurBlinkTime, float _BlinkFreq, float& _CurBlinkFreq,
		PopoState _PopoCurState, GameEngineRenderer* _Renderer);
	static void BlueStalfosBlinkUpdate(int _TimeScale, bool& _IsBlink, bool& _IsAlphaOn,
		float _BlinkTime, float& _CurBlinkTime, float _BlinkFreq, float& _CurBlinkFreq,
		BlueStalfosState _PopoCurState, GameEngineRenderer* _Renderer, GameEngineRenderer* _Renderer2);
	static void MoveDirBoolCheck(bool& _MoveRight, bool& _MoveLeft, bool& _MoveUp, bool& _MoveDown, float4 _MoveDir);
protected:

private:
};

