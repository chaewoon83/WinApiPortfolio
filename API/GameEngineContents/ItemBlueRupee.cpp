#include "ItemBlueRupee.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include "ItemGlobalFunction.h"


ItemBlueRupee::ItemBlueRupee()
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


ItemBlueRupee::~ItemBlueRupee()
{
}

void ItemBlueRupee::Start()
{


}

void ItemBlueRupee::Update()
{
	if (false == IsRendererSet_)
	{
		IsRendererSet_ = true;
		ItemRenderer_ = CreateRenderer();
		ItemRenderer_->CreateAnimationTimeKey("ItemBlueRupee.bmp", "Idle", TimeScale_, 0, 2, 0.3f, true);
		ItemRenderer_->ChangeAnimation("Idle");
		ItemRenderer_->SetPivot({ 0 , -RespawnPivot_ });
		ShadowRenderer_ = CreateRenderer("ItemShadow.bmp");
		ShadowRenderer_->SetPivot({ 0, 30 });
		ItemCollision_ = CreateCollision("BlueRupee", { 32,56 }, { 0, RespawnPivot_ });
	}
	else
	{
		if (OriginalPos_.CompareInt2D(float4::ZERO))
		{
			MsgBoxAssert("BlueRupee를 설정하는데 오류가 발생했습니다");
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
void ItemBlueRupee::Render()
{

}


