#include "EnemyAntiFairy.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImage.h>
#include "EnemyGlobalFunction.h"
#include "PlayerLink.h"
#include "GameEngineContentsEnum.h"

EnemyAntiFairy::EnemyAntiFairy()
	: Speed_(350.0f)
	 , Pos_({ 3072.0f, 3800.0f })
	//, Pos_({ 1371, 2967 })
	, Renderer_(nullptr)
	, Collision_(nullptr)
	//, TimeScale_ (9)
	, TimeScale_ (10)
	, MoveDir_({-1, -1})
	, IsRightBounce_(true)
	, IsTopBounce_(false)

{
}

EnemyAntiFairy::~EnemyAntiFairy()
{
}

void EnemyAntiFairy::Start()
{
	SetPosition(Pos_);
	Renderer_ = CreateRenderer();
	Renderer_->CreateAnimationTimeKey("EnemyAntiFairy.bmp", "Idle", TimeScale_, 0, 4, 0.1f, true);
	Renderer_->ChangeAnimation("Idle");
	Collision_ = CreateCollision("MonsterHitBox", { 48, 48 });
	MoveDir_.Normal2D();
}

void EnemyAntiFairy::Update()
{
	SetMove( MoveDir_ * Speed_ * GameEngineTime::GetDeltaTime(TimeScale_));
	MoveDirCheck();

}
void EnemyAntiFairy::Render()
{
	//DebugRectRender();

}


bool EnemyAntiFairy::MoveDirCheck()
{
	float4 CheckPos;
	//맵 이미지와 캐릭터의 이미지의 픽셀 위치를 동일하게 맞춰놔야한다
	bool MoveLeft = false;
	bool MoveRight = false;
	bool MoveUp = false;
	bool MoveDown = false;
	EnemyGlobalFunction::MoveDirBoolCheck(MoveRight, MoveLeft, MoveUp, MoveDown, MoveDir_);

	//SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
	{
		int Black = RGB(0, 0, 0);
		float4 MyPos = GetPosition();
		float4 Map1f_2_Scale = float4{ 0, -4128 };
		if (false == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetIsMap1F_2())
		{
			MyPos += Map1f_2_Scale;
		}
		float4 NextPos = MyPos + (MoveDir_ * GameEngineTime::GetDeltaTime(TimeScale_) * Speed_);
		float4 NextRealPos = MyPos + (MoveDir_ * GameEngineTime::GetDeltaTime(TimeScale_) * Speed_);
		float4 CheckPosTopRight = NextPos + float4{ 36.0f, -36.0f };
		float4 CheckPosTopLeft = NextPos + float4{ -36.0f, -36.0f };
		float4 CheckPosBotRight = NextPos + float4{ 36.0f, 36.0f };
		float4 CheckPosBotLeft = NextPos + float4{ -36.0f, 36.0f };
		float4 CheckPosRight = NextPos + float4{ 36.0f, 0.0f };
		float4 CheckPosLeft = NextPos + float4{ -36.0f, 0.0f };
		float4 CheckPosTop = NextPos + float4{ 0.0f, -36.0f };
		float4 CheckPosBot = NextPos + float4{ 0.0f, 36.0f };

		int ColorNextTopRight = PlayerLink::MapColImage_->GetImagePixel(CheckPosTopRight);
		int ColorNextTopLeft = PlayerLink::MapColImage_->GetImagePixel(CheckPosTopLeft);
		int ColorNextBotRight = PlayerLink::MapColImage_->GetImagePixel(CheckPosBotRight);
		int ColorNextBotLeft = PlayerLink::MapColImage_->GetImagePixel(CheckPosBotLeft);
		int ColorNextRight = PlayerLink::MapColImage_->GetImagePixel(CheckPosRight);
		int ColorNextLeft = PlayerLink::MapColImage_->GetImagePixel(CheckPosLeft);
		int ColorNextTop = PlayerLink::MapColImage_->GetImagePixel(CheckPosTop);
		int ColorNextBot = PlayerLink::MapColImage_->GetImagePixel(CheckPosBot);


		if (false == Collision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
		{
			if (true == PixelCollisionCheckY(CheckPosTopRight, CheckPosBotRight) && false == IsRightBounce_)
			{
				IsRightBounce_ = true;
				MoveDir_.x = -MoveDir_.x;
			}

			if (true == PixelCollisionCheckY(CheckPosTopLeft, CheckPosBotLeft) && true == IsRightBounce_)
			{
				IsRightBounce_ = false;
				MoveDir_.x = -MoveDir_.x;
			}

			if (true == PixelCollisionCheckX(CheckPosTopLeft, CheckPosTopRight) && false == IsTopBounce_)
			{
				IsTopBounce_ = true;
				MoveDir_.y = -MoveDir_.y;
			}

			if (true == PixelCollisionCheckX(CheckPosBotLeft, CheckPosBotRight) && true == IsTopBounce_)
			{
				IsTopBounce_ = false;
				MoveDir_.y = -MoveDir_.y;
			}
			return true;
		}
		else
		{
			if (true == MoveRight)
			{
				if (false == IsRightBounce_)
				{
					IsRightBounce_ = true;
					MoveDir_.x = -MoveDir_.x;
				}
			}

			if (true == MoveLeft)
			{
				if (true == IsRightBounce_)
				{
					IsRightBounce_ = false;
					MoveDir_.x = -MoveDir_.x;
				}
			}
			if (true == MoveUp)
			{
				if (false == IsTopBounce_)
				{
					IsTopBounce_ = true;
					MoveDir_.y = -MoveDir_.y;
				}

			}
			if (true == MoveDown)
			{
				if (true == IsTopBounce_)
				{
					IsTopBounce_ = false;
					MoveDir_.y = -MoveDir_.y;
				}

			}
			return true;
		}
		return false;
	}
}

bool EnemyAntiFairy::PixelCollisionCheckX(float4 _Min, float4 _Max)
{
	int Black = RGB(0, 0, 0);
	for (int j = _Min.ix() + 10 ; j < _Max.ix() - 10 ; j++)
	{
		if (Black == PlayerLink::MapCarryColImage_->GetImagePixel(float4{ static_cast<float>(j), _Min.y}))
		{
			return true;
		}
		return false;
	}
}

bool EnemyAntiFairy::PixelCollisionCheckY(float4 _Min, float4 _Max)
{
	int Black = RGB(0, 0, 0);
	for (int j = _Min.iy() + 10; j < _Max.iy() - 10 ; j++)
	{
		if (Black == PlayerLink::MapCarryColImage_->GetImagePixel(float4{ _Max.x, static_cast<float>(j) }))
		{
			return true;
		}
		return false;
	}
}


