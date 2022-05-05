#include "ItemRecoveryHeart.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include "ItemGlobalFunction.h"



ItemRecoveryHeart::ItemRecoveryHeart() 
	: ItemRenderer_(nullptr)
	, ShadowRenderer_(nullptr)
	, ItemCollision_(nullptr)
	, LiveTime_(5.0f)
	, CurLiveTime_(0.0f)
	//Blink
	, IsBlink_(false)
	, IsAlphaOn_(true)
	, CurBlinkTime_(0.0f)
	, CurBlinkFreq_(0.0f)
	, BlinkTime_(5.0f)
	, BlinkFreq_(0.05)
{
}

ItemRecoveryHeart::~ItemRecoveryHeart() 
{

}

void ItemRecoveryHeart::Start()
{
	//ShadowRenderer_ = CreateRenderer("ItemShadow.bmp");
	ItemRenderer_ = CreateRenderer("ItemRecoveryHeart.bmp");
	//ShadowRenderer_->SetPivot({ 0, 5 });
	ItemCollision_ = CreateCollision("RecoveryHeart", { 32,28 });

}
 
void ItemRecoveryHeart::Update()
{
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
void ItemRecoveryHeart::Render()
{
	DebugRectRender();

}
