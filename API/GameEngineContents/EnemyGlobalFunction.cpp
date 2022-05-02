#include "EnemyGlobalFunction.h"
#include "PlayerLink.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include "GlobalRandom.h"
#include "ItemGreenRupee.h"
#include "ItemBlueRupee.h"

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
	if (0.1f <= _MoveDir.x)
	{
		_MoveRight = true;
	}

	if (-0.1f >= _MoveDir.x)
	{
		_MoveLeft = true;
	}

	if (0.1f <= _MoveDir.y)
	{
		_MoveDown = true;
	}

	if (-0.1f >= _MoveDir.y)
	{
		_MoveUp = true;
	}

}

void EnemyGlobalFunction::KnockBackMoveFunction(int _TimeScale, float _Speed, float4 _MoveDir, GameEngineCollision* _Collision, GameEngineActor* _Actor)
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
		float4 MyPosTopRight = MyPos + float4{ 32.0f, -32.0f };
		float4 MyPosTopLeft = MyPos + float4{ -32.0f, -32.0f };
		float4 MyPosBotRight = MyPos + float4{ 32.0f, 32.0f };
		float4 MyPosBotLeft = MyPos + float4{ -32.0f, 32.0f };
		float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f };
		float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
		float4 MyPosTop = MyPos + float4{ 0.0f, -32.0f };
		float4 MyPosBot = MyPos + float4{ 0.0f, 32.0f };
		float4 NextPos = MyPos + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
		float4 NextRealPos = _Actor->GetPosition() + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
		float4 CheckPosTopRight = NextPos + float4{ 32.0f, -32.0f };
		float4 CheckPosTopLeft = NextPos + float4{ -32.0f, -32.0f };
		float4 CheckPosBotRight = NextPos + float4{ 32.0f, 32.0f };
		float4 CheckPosBotLeft = NextPos + float4{ -32.0f, 32.0f };
		float4 CheckPosRight = NextPos + float4{ 32.0f, 0.0f };
		float4 CheckPosLeft = NextPos + float4{ -32.0f, 0.0f };
		float4 CheckPosTop = NextPos + float4{ 0.0f, -32.0f };
		float4 CheckPosBot = NextPos + float4{ 0.0f, 32.0f };

		int ColorNextTopRight = PlayerLink::MapColImage_->GetImagePixel(CheckPosTopRight);
		int ColorNextTopLeft = PlayerLink::MapColImage_->GetImagePixel(CheckPosTopLeft);
		int ColorNextBotRight = PlayerLink::MapColImage_->GetImagePixel(CheckPosBotRight);
		int ColorNextBotLeft = PlayerLink::MapColImage_->GetImagePixel(CheckPosBotLeft);
		int ColorNextRight = PlayerLink::MapColImage_->GetImagePixel(CheckPosRight);
		int ColorNextLeft = PlayerLink::MapColImage_->GetImagePixel(CheckPosLeft);
		int ColorNextTop = PlayerLink::MapColImage_->GetImagePixel(CheckPosTop);
		int ColorNextBot = PlayerLink::MapColImage_->GetImagePixel(CheckPosBot);


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
				if (Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosTopRight.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosTop.y }) &&
					Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosBotRight.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosBot.y }) &&
					Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosRight.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosRight.y }))
				{
					{
						_Actor->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}

				if (Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosLeft))
				{
					{
						if (false == MoveUp)
						{
							_Actor->SetMove(float4::UP * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
						}
					}

				}

				if (Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveDown)
					{
						_Actor->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
			}

			if (true == MoveLeft)
			{
				if (Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosTopLeft.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosTopLeft.y }) &&
					Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosBotLeft.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosBotLeft.y }) &&
					Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosLeft.x + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).x, MyPosLeft.y }))
				{
					_Actor->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
				}

				if (Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosLeft) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveUp)
					{
						_Actor->SetMove(float4::UP * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
				if (Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosLeft) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveDown)
					{
						_Actor->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
			}

			if (true == MoveUp)
			{
				if (Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosTopRight.x, MyPosTop.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }) &&
					Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosTopLeft.x, MyPosTop.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }) &&
					Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosTop.x, MyPosTop.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }))
				{
					_Actor->SetMove(float4::UP * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
				}

				if (Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTop) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveRight)
					{
						_Actor->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}

				if (Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTop) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveLeft)
					{
						_Actor->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}
			}

			if (true == MoveDown)
			{
				if (Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosBotRight.x, MyPosBot.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }) &&
					Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosBotLeft.x, MyPosBot.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }) &&
					Black != PlayerLink::MapColImage_->GetImagePixel({ MyPosBot.x, MyPosBot.y + (_MoveDir * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed).y }))
				{
					_Actor->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
				}

				if (Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBot) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveRight)
					{
						_Actor->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(_TimeScale) * _Speed);
					}
				}

				if (Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBot) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != PlayerLink::MapColImage_->GetImagePixel(CheckPosTopLeft))
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
