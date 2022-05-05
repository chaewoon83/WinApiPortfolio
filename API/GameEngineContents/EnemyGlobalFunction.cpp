#include "EnemyGlobalFunction.h"
#include "PlayerLink.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GlobalRandom.h"
#include "ItemGreenRupee.h"
#include "ItemBlueRupee.h"
#include "ItemRedRupee.h"
#include "ItemRecoveryHeart.h"
#include "ItemKey.h"
#include "ItemBigKey.h"


EnemyGlobalFunction::EnemyGlobalFunction() 
{
}

EnemyGlobalFunction::~EnemyGlobalFunction() 
{
}

void EnemyGlobalFunction::PopoBlinkUpdate(int _TimeScale, bool& _IsBlink, bool& _IsAlphaOn,
	float _BlinkTime, float& _CurBlinkTime, float _BlinkFreq, float& _CurBlinkFreq,
	PopoState _PopoCurState, GameEngineRenderer* _Renderer)
{
	if (true == _IsBlink && PopoState::Death != _PopoCurState)
	{
		_CurBlinkTime += GameEngineTime::GetDeltaTime(_TimeScale);
		_CurBlinkFreq += GameEngineTime::GetDeltaTime(_TimeScale);
		if (_BlinkFreq < _CurBlinkFreq)
		{
			_CurBlinkFreq = 0.0f;
			if (false == _IsAlphaOn)
			{
				_Renderer->SetAlpha(255);
				_IsAlphaOn = true;
			}
			else
			{
				_Renderer->SetAlpha(0);
				_IsAlphaOn = false;
			}
		}

		if (_BlinkTime < _CurBlinkTime)
		{

			_IsBlink = false;
			_CurBlinkTime = 0.0f;
			_CurBlinkFreq = 0.0f;
			_IsAlphaOn = true;
			_Renderer->SetAlpha(255);
			return;
		}
	}
	else
	{
		if (_IsAlphaOn = false)
		{
			_Renderer->SetAlpha(255);
			_IsAlphaOn = true;
		}
	}
}

void EnemyGlobalFunction::BlueStalfosBlinkUpdate(int _TimeScale, bool& _IsBlink, bool& _IsAlphaOn,
	float _BlinkTime, float& _CurBlinkTime, float _BlinkFreq, float& _CurBlinkFreq,
	BlueStalfosState _BlueStalfosCurState, GameEngineRenderer* _Renderer, GameEngineRenderer* _Renderer2 )
{
	if (true == _IsBlink && BlueStalfosState::Death != _BlueStalfosCurState)
	{
		_CurBlinkTime += GameEngineTime::GetDeltaTime(_TimeScale);
		_CurBlinkFreq += GameEngineTime::GetDeltaTime(_TimeScale);
		if (_BlinkFreq < _CurBlinkFreq)
		{
			_CurBlinkFreq = 0.0f;
			if (false == _IsAlphaOn)
			{
				_Renderer->SetAlpha(255);
				if (nullptr != _Renderer2)
				{
					_Renderer2->SetAlpha(255);
				}
				_IsAlphaOn = true;
			}
			else
			{
				_Renderer->SetAlpha(0);
				if (nullptr != _Renderer2)
				{
					_Renderer2->SetAlpha(0);
				}
				_IsAlphaOn = false;
			}
		}

		if (_BlinkTime < _CurBlinkTime)
		{

			_IsBlink = false;
			_CurBlinkTime = 0.0f;
			_CurBlinkFreq = 0.0f;
			_IsAlphaOn = true;
			_Renderer->SetAlpha(255);
			if (nullptr != _Renderer2)
			{
				_Renderer2->SetAlpha(255);
			}
			return;
		}
	}
	else
	{
		if (_IsAlphaOn = false)
		{
			_Renderer->SetAlpha(255);
			if (nullptr != _Renderer2)
			{
				_Renderer2->SetAlpha(255);
			}
			_IsAlphaOn = true;
		}
	}
}
void EnemyGlobalFunction::MoveDirBoolCheck(bool& _MoveRight, bool& _MoveLeft, bool& _MoveUp, bool& _MoveDown, float4 _MoveDir)
{
	if (0.01f <= _MoveDir.x)
	{
		_MoveRight = true;
	}

	if (-0.01f >= _MoveDir.x)
	{
		_MoveLeft = true;
	}

	if (0.01f <= _MoveDir.y)
	{
		_MoveDown = true;
	}

	if (-0.01f >= _MoveDir.y)
	{
		_MoveUp = true;
	}

}

void EnemyGlobalFunction::Relocation(CameraState _PlayerRoom, int _MonsterRoom, bool& _IsRelocated, float4 _Pos, GameEngineActor* _Monster)
{
	if ((static_cast<int>(_PlayerRoom) + 2) != 2 * _MonsterRoom)
	{
		if (_IsRelocated == false)
		{
			_IsRelocated = true;
			_Monster->SetPosition(_Pos);
		}
	}
	if (GameEngineTime::GetInst()->GetTimeScale(_MonsterRoom) != 0.0f)
	{
		_IsRelocated = false;
	}
}

void EnemyGlobalFunction::ItemGenPot(int _ItemNum, GameEngineActor* _Actor)
{
	if (static_cast<int>(ItemIndex::Empty) == _ItemNum)
	{
		return;
	}
	if (static_cast<int>(ItemIndex::GreenRupee) == _ItemNum)
	{
		ItemGreenRupee* Ptr = _Actor->GetLevel()->CreateActor<ItemGreenRupee>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetGreenRupeePosition(_Actor->GetPosition() - float4{0, 20});
		return;
	}

	if (static_cast<int>(ItemIndex::BlueRupee) == _ItemNum)
	{
		ItemBlueRupee* Ptr = _Actor->GetLevel()->CreateActor<ItemBlueRupee>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetBlueRupeePosition(_Actor->GetPosition() - float4{ 0, 20 });
		return;
	}

	if (static_cast<int>(ItemIndex::RedRupee) == _ItemNum)
	{
		ItemRedRupee* Ptr = _Actor->GetLevel()->CreateActor<ItemRedRupee>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetRedRupeePosition(_Actor->GetPosition() - float4{ 0, 20 });
		return;
	}

	if (static_cast<int>(ItemIndex::RecoveryHeart) == _ItemNum)
	{
		ItemRecoveryHeart* Ptr = _Actor->GetLevel()->CreateActor<ItemRecoveryHeart>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetPosition(_Actor->GetPosition());
		return;
	}

	if (static_cast<int>(ItemIndex::Key) == _ItemNum)
	{
		ItemKey* Ptr = _Actor->GetLevel()->CreateActor<ItemKey>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetItemKeyPosition(_Actor->GetPosition() - float4{ 0, 20 });
		return;
	}

}

void EnemyGlobalFunction::ItemGenMonster(int _ItemNum, GameEngineActor* _Actor)
{
	if (static_cast<int>(ItemIndex::Empty) == _ItemNum)
	{
		return;
	}

	if (static_cast<int>(ItemIndex::GreenRupee) == _ItemNum)
	{
		ItemGreenRupee* Ptr = _Actor->GetLevel()->CreateActor<ItemGreenRupee>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetRespawnPivot(50.0f);
		Ptr->SetGreenRupeePosition(_Actor->GetPosition());
		return;
	}

	if (static_cast<int>(ItemIndex::BlueRupee) == _ItemNum)
	{
		ItemBlueRupee* Ptr = _Actor->GetLevel()->CreateActor<ItemBlueRupee>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetRespawnPivot(50.0f);
		Ptr->SetBlueRupeePosition(_Actor->GetPosition());
		return;
	}

	if (static_cast<int>(ItemIndex::RedRupee) == _ItemNum)
	{
		ItemRedRupee* Ptr = _Actor->GetLevel()->CreateActor<ItemRedRupee>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetRespawnPivot(50.0f);
		Ptr->SetRedRupeePosition(_Actor->GetPosition());
		return;
	}

	if (static_cast<int>(ItemIndex::RecoveryHeart) == _ItemNum)
	{
		ItemRecoveryHeart* Ptr = _Actor->GetLevel()->CreateActor<ItemRecoveryHeart>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetPosition(_Actor->GetPosition());
		return;
	}

	if (static_cast<int>(ItemIndex::Key) == _ItemNum)
	{
		ItemRecoveryHeart* Ptr = _Actor->GetLevel()->CreateActor<ItemRecoveryHeart>((int)PlayLevelOrder::BELOWPLAYER);
		Ptr->SetPosition(_Actor->GetPosition());
		return;
	}

}


void EnemyGlobalFunction::ItemRandomGenMonster(GameEngineActor* _Actor)
{
	GameEngineRandom Random;
	//Max 10
	int RandomInt = GlobalRandom::RandomIntGenerate(1, 20);
	if (4<= RandomInt && 15 >= RandomInt)
	{
		//GreenRupee
		ItemGenMonster(static_cast<int>(ItemIndex::GreenRupee), _Actor);
		return;
	}

	if (16 <= RandomInt && 18 >= RandomInt)
	{
		//BlueRupee
		ItemGenMonster(static_cast<int>(ItemIndex::BlueRupee), _Actor);
		return;

	}
	if (19 <= RandomInt && 20 >= RandomInt)
	{
		//RedRupee
		ItemGenMonster(static_cast<int>(ItemIndex::RedRupee), _Actor);
		return;
	}
	if (1 <= RandomInt && 3 >= RandomInt)
	{
		return;
	}
}


void EnemyGlobalFunction::KnockBackMoveFunction(int _TimeScale, float _Speed, float4 _MoveDir, GameEngineCollision* _Collision, GameEngineActor* _Actor, GameEngineImage* _Image,
	float _x /*= 32.0f*/, float _y_1 /*= 32.0f*/, float _y_2 /*= 32.0f*/)
{
	float4 CheckPos;
	//맵 이미지와 캐릭터의 이미지의 픽셀 위치를 동일하게 맞춰놔야한다
	bool MoveLeft = false;
	bool MoveRight = false;
	bool MoveUp = false;
	bool MoveDown = false;
	MoveDirBoolCheck(MoveRight, MoveLeft, MoveUp, MoveDown, _MoveDir);
	float4 Map1f_2_Scale = float4{ 0, -4128 };
	//SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
	{
		int Black = RGB(0, 0, 0);
		float4 MyPos = _Actor->GetPosition();
		if (false == PlayerLink::GetIsMap1F_2())
		{
			MyPos += Map1f_2_Scale;
		}
		float4 MyPosTopRight = MyPos + float4{ _x, -_y_1 };
		float4 MyPosTopLeft = MyPos + float4{ -_x, -_y_1 };
		float4 MyPosBotRight = MyPos + float4{ _x, _y_2 };
		float4 MyPosBotLeft = MyPos + float4{ -_x, _y_2 };
		float4 MyPosRight = MyPos + float4{ _x, 0.0f };
		float4 MyPosLeft = MyPos + float4{ -_x, 0.0f };
		float4 MyPosTop = MyPos + float4{ 0.0f, -_y_1 };
		float4 MyPosBot = MyPos + float4{ 0.0f, _y_2 };
		float4 NextPos = MyPos + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
		float4 NextRealPos = _Actor->GetPosition() + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
		float4 CheckPosTopRight = NextPos + float4{ _x, -_y_1 };
		float4 CheckPosTopLeft = NextPos + float4{ -_x, -_y_1 };
		float4 CheckPosBotRight = NextPos + float4{ _x, _y_2 };
		float4 CheckPosBotLeft = NextPos + float4{ -_x, _y_2 };
		float4 CheckPosRight = NextPos + float4{ _x, 0.0f };
		float4 CheckPosLeft = NextPos + float4{ -_x, 0.0f };
		float4 CheckPosTop = NextPos + float4{ 0.0f, -_y_1 };
		float4 CheckPosBot = NextPos + float4{ 0.0f, _y_1 };

		int ColorNextTopRight = _Image->GetImagePixel(CheckPosTopRight);
		int ColorNextTopLeft = _Image->GetImagePixel(CheckPosTopLeft);
		int ColorNextBotRight = _Image->GetImagePixel(CheckPosBotRight);
		int ColorNextBotLeft = _Image->GetImagePixel(CheckPosBotLeft);
		int ColorNextRight = _Image->GetImagePixel(CheckPosRight);
		int ColorNextLeft = _Image->GetImagePixel(CheckPosLeft);
		int ColorNextTop = _Image->GetImagePixel(CheckPosTop);
		int ColorNextBot = _Image->GetImagePixel(CheckPosBot);


		//int ColorNextTopRight = MapColImage_->GetImagePixel(CheckPosTopRight);
		//int ColorNextTopLeft = MapColImage_->GetImagePixel(CheckPosTopLeft);
		//int ColorNextBotRight = MapColImage_->GetImagePixel(CheckPosBotRight);
		//int ColorNextBotLeft = MapColImage_->GetImagePixel(CheckPosBotLeft);
		//int ColorNextRight = MapColImage_->GetImagePixel(CheckPosRight);
		//int ColorNextLeft = MapColImage_->GetImagePixel(CheckPosLeft);
		//int ColorNextTop = MapColImage_->GetImagePixel(CheckPosTop);
		//int ColorNextBot = MapColImage_->GetImagePixel(CheckPosBot);


		if (Black != ColorNextTopRight &&
			Black != ColorNextTopLeft &&
			Black != ColorNextBotRight &&
			Black != ColorNextBotLeft &&
			Black != ColorNextRight &&
			Black != ColorNextLeft &&
			Black != ColorNextTop &&
			Black != ColorNextBot)
		{
			if (false == _Collision->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
			{
				_Actor->SetMove(_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
			}
			else
			{
				if (true == MoveRight)
				{
					if (false == _Collision->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						_Actor->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}

				if (true == MoveLeft)
				{
					if (false == _Collision->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						_Actor->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
				if (true == MoveUp)
				{
					if (false == _Collision->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						_Actor->SetMove(float4::UP * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}

				}
				if (true == MoveDown)
				{
					if (false == _Collision->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						_Actor->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}

				}
			}
		}
		else
		{
			if (true == MoveRight)
			{
				if (Black != _Image->GetImagePixel({ MyPosTopRight.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosTop.y }) &&
					Black !=  _Image->GetImagePixel({ MyPosBotRight.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosBot.y }) &&
					Black !=  _Image->GetImagePixel({ MyPosRight.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosRight.y }))
				{
					{
						_Actor->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}

				if (Black !=  _Image->GetImagePixel(CheckPosRight) &&
					Black !=  _Image->GetImagePixel(CheckPosTopRight) &&
					Black !=  _Image->GetImagePixel(CheckPosTopLeft) &&
					Black !=  _Image->GetImagePixel(CheckPosLeft))
				{
					{
						if (false == MoveUp)
						{
							_Actor->SetMove(float4::UP * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
						}
					}

				}

				if (Black !=  _Image->GetImagePixel(CheckPosRight) &&
					Black !=  _Image->GetImagePixel(CheckPosBotRight) &&
					Black !=  _Image->GetImagePixel(CheckPosTopLeft) &&
					Black !=  _Image->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveDown)
					{
						_Actor->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
			}

			if (true == MoveLeft)
			{
				if (Black !=  _Image->GetImagePixel({ MyPosTopLeft.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosTopLeft.y }) &&
					Black !=  _Image->GetImagePixel({ MyPosBotLeft.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosBotLeft.y }) &&
					Black !=  _Image->GetImagePixel({ MyPosLeft.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosLeft.y }))
				{
					_Actor->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
				}

				if (Black !=  _Image->GetImagePixel(CheckPosLeft) &&
					Black !=  _Image->GetImagePixel(CheckPosTopLeft) &&
					Black !=  _Image->GetImagePixel(CheckPosTopRight) &&
					Black !=  _Image->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveUp)
					{
						_Actor->SetMove(float4::UP * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
				if (Black !=  _Image->GetImagePixel(CheckPosLeft) &&
					Black !=  _Image->GetImagePixel(CheckPosBotLeft) &&
					Black !=  _Image->GetImagePixel(CheckPosTopRight) &&
					Black !=  _Image->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveDown)
					{
						_Actor->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
			}

			if (true == MoveUp)
			{
				if (Black !=  _Image->GetImagePixel({ MyPosTopRight.x, MyPosTop.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }) &&
					Black !=  _Image->GetImagePixel({ MyPosTopLeft.x, MyPosTop.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }) &&
					Black !=  _Image->GetImagePixel({ MyPosTop.x, MyPosTop.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }))
				{
					_Actor->SetMove(float4::UP * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
				}

				if (Black !=  _Image->GetImagePixel(CheckPosTop) &&
					Black !=  _Image->GetImagePixel(CheckPosTopRight) &&
					Black !=  _Image->GetImagePixel(CheckPosBotRight) &&
					Black !=  _Image->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveRight)
					{
						_Actor->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}

				if (Black !=  _Image->GetImagePixel(CheckPosTop) &&
					Black !=  _Image->GetImagePixel(CheckPosTopLeft) &&
					Black !=  _Image->GetImagePixel(CheckPosBotRight) &&
					Black !=  _Image->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveLeft)
					{
						_Actor->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
			}

			if (true == MoveDown)
			{
				if (Black !=  _Image->GetImagePixel({ MyPosBotRight.x, MyPosBot.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }) &&
					Black !=  _Image->GetImagePixel({ MyPosBotLeft.x, MyPosBot.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }) &&
					Black !=  _Image->GetImagePixel({ MyPosBot.x, MyPosBot.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }))
				{
					_Actor->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
				}

				if (Black !=  _Image->GetImagePixel(CheckPosBot) &&
					Black !=  _Image->GetImagePixel(CheckPosBotRight) &&
					Black !=  _Image->GetImagePixel(CheckPosTopRight) &&
					Black !=  _Image->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveRight)
					{
						_Actor->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}

				if (Black !=  _Image->GetImagePixel(CheckPosBot) &&
					Black !=  _Image->GetImagePixel(CheckPosBotLeft) &&
					Black !=  _Image->GetImagePixel(CheckPosTopRight) &&
					Black !=  _Image->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveLeft)
					{
						_Actor->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
			}
		}
	}
}
