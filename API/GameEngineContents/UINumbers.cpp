#include "UINumbers.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <string>
#include "PlayerLink.h"

//UIRupee Numbers
//1. coordinate(260, 96) size(28 28)
//1. 274, 110
//2. + 4, +size
//3. + 4, +size
//
//UIBomb Numbers
//1. coordinate(388, 96) size(28 28)
//1. 402, 110
//2. + 4, +size
//3. + 4, +size
//
//UIArrow Numbers
//1. coordinate(484, 96) size(28 28)
//1. 498, 110
//2. + 4, +size
//3. + 4, +size
//
//UIKey Numbers
//1. coordinate(580, 96) size(28 28)
//1. 594, 110
//2. + 4, +size
//3. + 4, +size
UINumbers::UINumbers() 
	: UIRupee0_(nullptr)
	, UIRupee1_(nullptr)
	, UIRupee2_(nullptr)
	, UIBomb0_(nullptr)
	, UIBomb1_(nullptr)
	, UIArrow0_(nullptr)
	, UIArrow1_(nullptr)
	, UIKey_(nullptr)
	, Padding_({ 28+4, 0})
{
}

UINumbers::~UINumbers() 
{
}

void UINumbers::Start()
{
	CreateAnimationNumer(UIRupee0_);
	UIRupee0_->SetPivot({ 260 + 14, 96 + 14});
	CreateAnimationNumer(UIRupee1_);
	UIRupee1_->SetPivot(float4{ 260 + 14, 96 +14} + Padding_);
	CreateAnimationNumer(UIRupee2_);
	UIRupee2_->SetPivot(float4{ 260 + 14, 96 + 14 } + (Padding_ * 2.0f));

	CreateAnimationNumer(UIBomb0_);
	UIBomb0_->SetPivot({ 388 + 14, 96 + 14 });
	CreateAnimationNumer(UIBomb1_);
	UIBomb1_->SetPivot(float4{ 388 + 14, 96 + 14 } + Padding_);

	CreateAnimationNumer(UIArrow0_);
	UIArrow0_->SetPivot({ 484 + 14, 96 + 14 });
	CreateAnimationNumer(UIArrow1_);
	UIArrow1_->SetPivot(float4{ 484 + 14, 96 + 14 } + Padding_);

	CreateAnimationNumer(UIKey_);
	UIKey_->SetPivot({ 580 + 14, 96 + 14 });


}
 
void UINumbers::Update()
{
	UpdateRupeeNumber();
}
void UINumbers::Render()
{
	
}

void UINumbers::CreateAnimationNumer(GameEngineRenderer*& _Renderer)
{
	_Renderer = CreateRenderer();
	_Renderer->CreateAnimation("UI0.bmp", "0", 0, 0, 1.0f, false);
	_Renderer->CreateAnimation("UI1.bmp", "1", 0, 0, 1.0f, false);
	_Renderer->CreateAnimation("UI2.bmp", "2", 0, 0, 1.0f, false);
	_Renderer->CreateAnimation("UI3.bmp", "3", 0, 0, 1.0f, false);
	_Renderer->CreateAnimation("UI4.bmp", "4", 0, 0, 1.0f, false);
	_Renderer->CreateAnimation("UI5.bmp", "5", 0, 0, 1.0f, false);
	_Renderer->CreateAnimation("UI6.bmp", "6", 0, 0, 1.0f, false);
	_Renderer->CreateAnimation("UI7.bmp", "7", 0, 0, 1.0f, false);
	_Renderer->CreateAnimation("UI8.bmp", "8", 0, 0, 1.0f, false);
	_Renderer->CreateAnimation("UI9.bmp", "9", 0, 0, 1.0f, false);
	_Renderer->CameraEffectOff();
	_Renderer->ChangeAnimation("0");
}

void UINumbers::UpdateRupeeNumber()
{
	int PlayerRupee = PlayerLink::GetPlayerRupee();
	int PlayerRupee0 = PlayerRupee / 100;
	int PlayerRupee1 = PlayerRupee / 10 - 10 * PlayerRupee0;
	int PlayerRupee2 = PlayerRupee - 100 * PlayerRupee0 - 10 * PlayerRupee1;

	UIRupee0_->ChangeAnimation(std::to_string(PlayerRupee0));
	UIRupee1_->ChangeAnimation(std::to_string(PlayerRupee1));
	UIRupee2_->ChangeAnimation(std::to_string(PlayerRupee2));
}

void UINumbers::UpdateArrowNumber()
{
	int PlayerArrow = PlayerLink::GetPlayerArrow();
	int PlayerArrow0 = PlayerArrow / 10;
	int PlayerArrow1 = PlayerArrow / 10 - 10 * PlayerArrow0;

	UIArrow0_->ChangeAnimation(std::to_string(PlayerArrow0));
	UIArrow1_->ChangeAnimation(std::to_string(PlayerArrow1));
}

void UINumbers::UpdateKeyNumber()
{
	int PlayerKey0 = PlayerLink::GetPlayerKey();

	UIKey_->ChangeAnimation(std::to_string(PlayerKey0));
}