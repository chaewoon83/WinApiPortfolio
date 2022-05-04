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
	ItemRenderer_ = CreateRenderer("ItemRecoveryHeart.bmp");
	ItemRenderer_->ChangeAnimation("Idle");
	ShadowRenderer_ = CreateRenderer("ItemShadow.bmp");
	ShadowRenderer_->SetPivot({ 0, 30 });
	ItemCollision_ = CreateCollision("RecoveryHeart", { 32,28 });
}

void ItemRecoveryHeart::Start()
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
 
void ItemRecoveryHeart::Update()
{

}
void ItemRecoveryHeart::Render()
{
	DebugRectRender();

}
