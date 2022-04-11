#include "TitleTripleTrigangle.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "TitleTimeObject.h"

TitleTripleTrigangle::TitleTripleTrigangle() 
	:isTripleTriangleExist_(false)
{
}

TitleTripleTrigangle::~TitleTripleTrigangle() 
{
}

void TitleTripleTrigangle::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
}
 
void TitleTripleTrigangle::Update()
{
	if (12.5f < TitleTimeObject::TimeLine_)
	{
		if (false == isTripleTriangleExist_)
		{
			TripleTriangle_ = CreateRenderer("TitleTripleTriangle.bmp");
			isTripleTriangleExist_ = true;
		}

	}
}
void TitleTripleTrigangle::Render()
{

}
