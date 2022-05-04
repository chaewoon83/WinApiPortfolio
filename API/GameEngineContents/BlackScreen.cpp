#include "BlackScreen.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


BlackScreen::BlackScreen() 
{
}

BlackScreen::~BlackScreen() 
{
}
GameEngineRenderer* BlackScreen::Renderer_ = nullptr;

void BlackScreen::Start()
{
	Renderer_ = CreateRenderer("BlackBackground.bmp");
	SetPosition(Renderer_->GetImageScale().Half());
	Renderer_->Off();
	Renderer_->CameraEffectOff();
}
 
void BlackScreen::Update()
{

}
void BlackScreen::Render()
{
	//DebugRectRender();

}
