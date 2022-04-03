#include "GameEngineCollision.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineTime.h>

#pragma comment(lib, "msimg32.lib")

bool (*CollisionCheckArray[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision*, GameEngineCollision*);

bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return true;
}

GameEngineCollision::GameEngineCollision()
	: Pivot_(float4::ZERO)
	, Scale_(float4::ZERO)


{
	CollisionCheckArray[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)] = RectToRect;
}

GameEngineCollision::~GameEngineCollision() 
{
}

bool GameEngineCollision::CollisionCheck(const std::string& _TargetGroup,
	CollisionType _This /*= CollisionType::Circle*/,
	CollisionType _Target /*= CollisionType::Circle*/)
{
	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);
	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려고 했습니다");
	}
	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		//나와 상대의 콜리전 타입을 비교한다
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			return true;
		}
	}
	return false;
}