#pragma once

#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineContentsEnum.h"
#include "PlayerLink.h"
class GameEngineRenderer;
class GameEngineActor;
class GameEngineCollision;
// Ό³Έν :
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

	static void KnockBackMoveFunction(int _TimeScale, float _Speed, float4 _MoveDir, GameEngineCollision* _Collision, GameEngineActor* _Actor, 
		 GameEngineImage* _Imagefloat, float _x = 32.0f, float _y_1 = 32.0f, float _y_2 = 32.0f);
	static void PopoBlinkUpdate(int _TimeScale, bool& _IsBlink, bool& _IsAlphaOn,
		float _BlinkTime, float& _CurBlinkTime, float _BlinkFreq, float& _CurBlinkFreq,
		PopoState _PopoCurState, GameEngineRenderer* _Renderer);
	static void BlueStalfosBlinkUpdate(int _TimeScale, bool& _IsBlink, bool& _IsAlphaOn,
		float _BlinkTime, float& _CurBlinkTime, float _BlinkFreq, float& _CurBlinkFreq,
		BlueStalfosState _PopoCurState, GameEngineRenderer* _Renderer, GameEngineRenderer* _Renderer2);
	static void MoveDirBoolCheck(bool& _MoveRight, bool& _MoveLeft, bool& _MoveUp, bool& _MoveDown, float4 _MoveDir);
	static void Relocation(CameraState _PlayerRoom, int _MonsterRoom, bool& _IsRelocated, float4 _Pos, GameEngineActor* _Monster);

	static void ItemGenPot(int _ItemNum, GameEngineActor* _Actor);
	static void ItemGenMonster(int _ItemNum, GameEngineActor* _Actor);
	static void ItemRandomGenMonster(GameEngineActor* _Actor);
protected:

private:
};

