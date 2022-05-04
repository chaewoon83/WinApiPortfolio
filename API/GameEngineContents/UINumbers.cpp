#include "UINumbers.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

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
	int a = 0;
}
 
void UINumbers::Update()
{

}
void UINumbers::Render()
{
	//DebugRectRender();

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
	_Renderer->ChangeAnimation("0");
}
