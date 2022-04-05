#include "UIHeart.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

UIHeart::UIHeart() 
{
}

UIHeart::~UIHeart() 
{
}


//UIHeart
//1. coordinate(644, 96) size(28 28)
//1. 658, 110
//2. + 4, +size
//2~10
void UIHeart::Start()
{
	float4 Padding = {32, 0};
	SetPosition({ 658, 110 });
	for (int i = 0; i < 10; i++)
	{
		AllHearts.push_back(CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * static_cast<float>(i)));
	}

	std::list<GameEngineRenderer*>::iterator Iter = AllHearts.begin();
	for (; Iter != AllHearts.end(); ++Iter)
	{
		(*Iter)->CameraEffectOff();
	}

}
 
void UIHeart::Update()
{

}
void UIHeart::Render()
{
	//DebugRectRender();

}
