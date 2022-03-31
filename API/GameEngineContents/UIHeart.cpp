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
	GameEngineRenderer* FullHeart_1 = CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 0);
	GameEngineRenderer* FullHeart_2 = CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 1);
	GameEngineRenderer* FullHeart_3 = CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 2);
	GameEngineRenderer* FullHeart_4 = CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 3);
	GameEngineRenderer* FullHeart_5 = CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 4);
	GameEngineRenderer* FullHeart_6 = CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 5);
	GameEngineRenderer* FullHeart_7 = CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 6);
	GameEngineRenderer* FullHeart_8 = CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 7);
	GameEngineRenderer* FullHeart_9 = CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 8);
	GameEngineRenderer* FullHeart_10 =  CreateRenderer("UIFullHeart.bmp", RenderPivot::CENTER, Padding * 9);
}
 
void UIHeart::Update()
{

}
void UIHeart::Render()
{
	//DebugRectRender();

}
