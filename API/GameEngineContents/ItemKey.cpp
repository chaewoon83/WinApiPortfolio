#include "ItemKey.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include "ItemGlobalFunction.h"


ItemKey::ItemKey()
	: ItemRenderer_(nullptr)
	, ShadowRenderer_(nullptr)
	, ItemCollision_(nullptr)
	, IsRendererSet_(false)
	, OriginalPos_(float4::ZERO)
	, RespawnPivot_(30.0f)
	, Speed_(0.0f)
	, LiveTime_(5.0f)
	, CurLiveTime_(0.0f)
	, BounceTime_(0.0f)
	, BounceSpeed_(50.0f)
	, TimeScale_(-1)
	//Blink
	, IsBlink_(false)
	, IsAlphaOn_(true)
	, CurBlinkTime_(0.0f)
	, CurBlinkFreq_(0.0f)
	, BlinkTime_(5.0f)
	, BlinkFreq_(0.05)

{
}


ItemKey::~ItemKey()
{
}

void ItemKey::Start()
{


}

void ItemKey::Update()
{
	if (false == IsRendererSet_)
	{
		IsRendererSet_ = true;
		ItemRenderer_ = CreateRenderer("ItemKey.bmp");
		ItemRenderer_->SetPivot({ 0 , -RespawnPivot_ });
		ShadowRenderer_ = CreateRenderer("ItemShadow.bmp");
		ShadowRenderer_->SetPivot({ 0, 30 });
		ItemCollision_ = CreateCollision("Key", { 32,56 }, { 0, RespawnPivot_ });
	}
	else
	{
		if (OriginalPos_.CompareInt2D(float4::ZERO))
		{
			MsgBoxAssert("Key를 설정하는데 오류가 발생했습니다");
			return;
		}
		CurLiveTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
		BounceTime_ += GameEngineTime::GetDeltaTime(TimeScale_);

		ItemRenderer_->SetPivot({ 0 , -ItemGlobalFunction::BounceUpdate(BounceTime_, Speed_, BounceSpeed_, RespawnPivot_) });
		ItemCollision_->SetPivot({ 0 , -ItemGlobalFunction::BounceUpdate(BounceTime_, Speed_, BounceSpeed_, RespawnPivot_) });



		if (3.0f < CurLiveTime_)
		{
			IsBlink_ = true;
		}

		ItemGlobalFunction::BlinkUpdate(IsBlink_, IsAlphaOn_, CurBlinkTime_, CurBlinkFreq_, BlinkTime_, BlinkFreq_, ItemRenderer_);

		if (LiveTime_ < CurLiveTime_)
		{
			Death();
		}
	}
}
void ItemKey::Render()
{

}


