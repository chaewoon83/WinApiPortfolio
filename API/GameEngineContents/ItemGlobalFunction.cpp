#include "ItemGlobalFunction.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

ItemGlobalFunction::ItemGlobalFunction() 
{
}

ItemGlobalFunction::~ItemGlobalFunction() 
{
}

float ItemGlobalFunction::BounceUpdate(float& _Time, float& _Speed, float _BounceSpeed, float _PivotHeight)
{
	float ItemHeight = 0.0f;
	if (0 == _Speed)
	{
		ItemHeight = _PivotHeight - 400.0f * 0.5f * static_cast<float>(pow(_Time, 2));
	}
	else
	{
		ItemHeight =  _Speed * _Time - 400.0f * 0.5f * static_cast<float>(pow(_Time, 2));
	}


	if (0 > ItemHeight)
	{
		_Time = 0.0f;
		if (0 == _Speed)
		{
			_Speed = _BounceSpeed;
			return ItemHeight;
		}
		else if (0.001 >= _Speed)
		{

			return 0.0f;
		}
		_Speed *= 0.5f;
	}
	return ItemHeight;
}

void ItemGlobalFunction::BlinkUpdate(bool& _IsBlink, bool& _IsAlphaOn, float& _CurBlinkTime, float& _CurBlinkFreq, float _BlinkTime, float _BlinkFreq, GameEngineRenderer* _Renderer)
{

	if (true == _IsBlink)
	{
		_CurBlinkTime += GameEngineTime::GetDeltaTime(-1);
		_CurBlinkFreq += GameEngineTime::GetDeltaTime(-1);
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
		}
	}
}
